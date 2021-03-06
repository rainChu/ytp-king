/*  YTP King - Easy to use sentence mixer
 *  Copyright (C) 2013  Alex "rainChu" Haddad et al.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ytpking/SamplesDataFile.h"

#include <wx/log.h>

#include "ytpking/Guid.h"

#include "gst/gnl/TapeComposition.h"
#include "gst/gnl/FileSource.h"

#include "smp/SampleManager.h"
#include "smp/Sample.h"


#define MAX_START_FRAME_SIZE 16u
#define MAX_END_FRAME_SIZE   16u


using namespace rapidxml;


	namespace ytpking
	{

		using smp::SampleManager;


SamplesDataFile::
NodeReference::NodeReference( void ) :
	m_speaker( NULL ),
	m_speech( NULL ),
	m_startString( NULL ),
	m_endString( NULL )
{
}


SamplesDataFile::SamplesDataFile( void ) :
	SampleUser( *smp::sampleManager ),
	DataFile( "/samples.xml" ),
	m_isLocked( false )
{
	xml_node<> *rootNode = m_xmlDocument.first_node();

	if ( rootNode == NULL )
	{
		rootNode = m_xmlDocument.allocate_node( node_element, "ytpking" );
		m_xmlDocument.append_node( rootNode );

		xml_node<> *samplesNode = m_xmlDocument.allocate_node( node_element, "samples" );
		rootNode->append_node( samplesNode );
	}
	else
	{
		bool shownMessage;
		if ( strcmp( rootNode->name(), "ytpking" ) != 0 )
		{
			wxSafeShowMessage( "Error", "Samples file is corrupt. Please make a backup of it, then delete it." );
			shownMessage = true;
		}
		else
			shownMessage = false;

		if ( rootNode->first_node( "samples" ) == NULL )
		{
			if ( !shownMessage )
				wxSafeShowMessage( "Error", "Samples file is corrupt. Please make a backup of it, then delete it." );

			xml_node<> *samplesNode = m_xmlDocument.allocate_node( node_element, "samples" );
			rootNode->append_node( samplesNode );
		}
	}
}


xml_node<>
*SamplesDataFile::getOrMakeSpeakerNode( const char *speakerName )
{
	if ( m_isLocked )
		return NULL;

	// Get the XML name and compare
	xml_node<> *samplesNode = m_xmlDocument.first_node()->first_node( "samples" );

	xml_node<> *speakerNode = samplesNode->first_node( "speaker" );

	while ( speakerNode != NULL )
	{
		xml_attribute<> *nameAttr = speakerNode->first_attribute( "name" );

		if ( nameAttr && (strcmp( nameAttr->value(), speakerName ) == 0) )
			break;

		speakerNode = speakerNode->next_sibling( "speaker" );
	}

	if ( speakerNode == NULL )
	{
		speakerNode = m_xmlDocument.allocate_node( node_element, "speaker" );
		speakerName = m_xmlDocument.allocate_string( speakerName );
		xml_attribute<> *nameAttr = m_xmlDocument.allocate_attribute( "name", speakerName );

		speakerNode->append_attribute( nameAttr );

		samplesNode->append_node( speakerNode );
	}

	return speakerNode;
}


void
SamplesDataFile::onAddSample( char const *sampleName, char const *speakerName, smp::Sample *addedSample )
{
	if ( m_isLocked )
		return;

	NodeReference *nodeReference = &addedSample->getNodeReference();

	nodeReference->m_speaker = getOrMakeSpeakerNode( speakerName );
	nodeReference->m_speech  = m_xmlDocument.allocate_node( node_element, "speech" );

	appendStringAttribute( nodeReference->m_speech, "name", sampleName );
	appendStringAttribute( nodeReference->m_speech, "guid", addedSample->getGuid() );

	nodeReference->m_speaker->append_node( nodeReference->m_speech );

	saveToFile();
}


void
SamplesDataFile::onDeleteSample( smp::Sample *deletedSample )
{
	// TODO
}


void
SamplesDataFile::onRenameSample( char const *newSampleName, smp::Sample *sample )
{
	xml_attribute<> *nameAttr = sample->getNodeReference().m_speech->first_attribute( "name" );

	newSampleName = m_xmlDocument.allocate_string( newSampleName );
	nameAttr->value( newSampleName );

	saveToFile();
}


void
SamplesDataFile::onChangeSampleSpeaker( char const *speakerName, smp::Sample *sample )
{
	NodeReference *nodeReference = &sample->getNodeReference();

	nodeReference->m_speaker->remove_node( nodeReference->m_speech );

	if ( nodeReference->m_speaker->first_node() == NULL )
	{
		xml_node<> *samplesNode = m_xmlDocument.first_node()->first_node( "samples" );
		samplesNode->remove_node( nodeReference->m_speaker );
	}

	xml_node<> *speakerNode = getOrMakeSpeakerNode( speakerName );
	if ( speakerNode )
	{
		nodeReference->m_speaker = speakerNode;
		nodeReference->m_speaker->append_node( nodeReference->m_speech );

		saveToFile();
	}
}


void
SamplesDataFile::onLoadAllSamples( void )
{
m_isLocked = true;

	using gst::gnl::FileSource;

	xml_node<> *samplesNode = m_xmlDocument.first_node()->first_node( "samples" );

	xml_node<> *speakerNode = samplesNode->first_node( "speaker" );

	while ( speakerNode != NULL )
	{
		xml_attribute<> *speakerNameAttr = speakerNode->first_attribute( "name" );
		if ( speakerNameAttr == NULL )
		{
			speakerNode = speakerNode->next_sibling( "speaker" );
			continue;
		}
		const char *speakerName = speakerNameAttr->value();

		xml_node<> *speechNode = speakerNode->first_node( "speech" );

		while ( speechNode != NULL )
		{
			xml_attribute<> *speechNameAttr = speechNode->first_attribute( "name" );
			if ( speechNameAttr == NULL )
			{
				speechNode = speechNode->next_sibling( "speech" );
				continue;
			}
			const char *speechName = speechNameAttr->value();

			NodeReference nodeReference;
			nodeReference.m_speaker = speakerNode;
			nodeReference.m_speech  = speechNode;

			// get guid
			std::string guidString;
			const char *guidCString;
			if ( getStringAttribute( speechNode, "guid", guidString ) )
				guidCString = guidString.c_str();
			else
				guidCString = NULL;

			// Make the sample
			smp::Sample *sample = smp::sampleManager->addSample( "file:///C:/zelda.mp4", speechName, speakerName, guidCString, &nodeReference );


			// if there wasn't a guid, then append one
			if ( guidCString == NULL )
				appendStringAttribute( speechNode, "guid", sample->getGuid() );


			// get start and end
			int start, end;
			start = getIntAttribute( speechNode, "start", 0 );
			end   = getIntAttribute( speechNode, "end", 5 );


			if ( start < 0 )
				start = 0;
				// guard against invalid duration
			if ( end <= start )
				end = start + 5;

			// Then set it
			smp::sampleManager->setSampleRange( sample, start, end );

			speechNode = speechNode->next_sibling( "speech" );
		}

		speakerNode = speakerNode->next_sibling( "speaker" );
	}


	m_isLocked = false;
}


void
SamplesDataFile::onChangeSampleRange( smp::Sample *sample )
{
	if ( m_isLocked )
		return;

	NodeReference *nodeReference = &sample->getNodeReference();

	if ( !setOrMakeNumberAttribute( sample->getStart(), nodeReference->m_speech, nodeReference->m_startString, "start", MAX_START_FRAME_SIZE ) )
		wxLogError( "Start time can't be more than %d digits long.", MAX_START_FRAME_SIZE - 1 );

	if ( !setOrMakeNumberAttribute( sample->getEnd(), nodeReference->m_speech, nodeReference->m_endString,  "end", MAX_END_FRAME_SIZE ) )
		wxLogError( "End time can't be more than %d digits long.", MAX_END_FRAME_SIZE - 1 );

	saveToFile();
}


	}