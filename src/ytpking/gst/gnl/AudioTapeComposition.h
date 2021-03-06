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
#ifndef __YTPKING_GST_GNL_AudioTapeComposition_h
#define __YTPKING_GST_GNL_AudioTapeComposition_h

#include "TapeComposition.h"


	namespace ytpking
	{
	namespace gst
	{
	namespace gnl
	{

class FileSource;

class AudioTapeComposition : 
	public TapeComposition
{
public:

	AudioTapeComposition( void );

public:

	void
		addTo( Pipeline &pipeline )
		override;

private:

	// TODO add some necessary basic processing like audioconvert and audioresample
	//      so it doesn't sound like crud for no reason.
	//GstElement *m_convertElement;
	//GstElement *m_resampleElement;
	//GstElement *m_queueElement;
	GstElement *m_sinkElement;

};

	} } }

#endif
