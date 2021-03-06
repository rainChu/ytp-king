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
#define YTPKING_SMP_TapeManager_cpp
#include "TapeManager.h"

#include "Tape.h"
#include "TapeUser.h"


	namespace ytpking
	{
	namespace smp
	{



TapeManager::TapeManager( void ) :
	m_selectedTape( NULL )
{
}


TapeManager::~TapeManager( void )
{
	for ( TapeSet::const_iterator it = m_tapes.begin(); it != m_tapes.end(); ++it )
		delete *it;
}

void
TapeManager::loadAll( void )
{
	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onLoadAllTapes();
}


void
TapeManager::registerTapeUser( TapeUser *tapeUser )
{
	m_tapeUsers.insert( tapeUser );
}


void
TapeManager::unregisterTapeUser( TapeUser *tapeUser )
{
	m_tapeUsers.erase( tapeUser );
}


Tape
*TapeManager::getSelectedTape( void ) const
{
	return m_selectedTape;
}


void
TapeManager::selectTape( Tape *tape )
{
	m_selectedTape = tape;

	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onSelectTape( tape );

	m_selectedTape->connectToPreview();
}


Tape
*TapeManager::addTape( const char *name, TapesDataFile::TapeNodeReference *existingNodeReference )
{
	TapesDataFile::TapeNodeReference nodeReference;
	
	if ( existingNodeReference != NULL )
		nodeReference = *existingNodeReference;

	Tape *tape = new Tape( name, nodeReference );

	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onAddTape( *tape );

	return tape;
}


void
TapeManager::deleteTape( Tape *tape )
{
	TapeSet::const_iterator tapeIt = m_tapes.find( tape );

	if ( tapeIt != m_tapes.end() )
	{
		for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
			(*it)->onDeleteTape( *tape );

		delete tape;
		m_tapes.erase( *tapeIt );
	}
}


void
TapeManager::renameTape( Tape *tape, const char *name )
{
	tape->m_name = name;

	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onRenameTape( *tape );
}


SampleInstance
*TapeManager::appendInstance( Tape *tape, const Sample &sample, TapesDataFile::InstanceNodeReference *existingNodeReference )
{
	TapesDataFile::InstanceNodeReference nodeReference;
	if ( existingNodeReference != NULL )
		nodeReference = *existingNodeReference;

	SampleInstance *sampleInstance = tape->appendInstance( sample, nodeReference );

	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onTapeAddInstance( *tape, *sampleInstance );

	return sampleInstance;
}


void
TapeManager::deleteInstance( Tape *tape, SampleInstance &sampleInstance )
{
	for ( TapeUserSet::const_iterator it = m_tapeUsers.begin(); it != m_tapeUsers.end(); ++it )
		(*it)->onTapeDeleteInstance( *tape, sampleInstance );

	tape->deleteInstance( sampleInstance );
}


	} }