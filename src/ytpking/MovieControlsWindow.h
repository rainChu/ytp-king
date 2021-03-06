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
#ifndef __YTPKING_MovieControlsWindow_h
#define __YTPKING_MovieControlsWindow_h

#include <wx/window.h>
#include <wx/timer.h>

#include "gst/PipelineUser.h"


class wxSlider;
class wxTimer;


	namespace ytpking
	{


class MovieControlsWindow :
	public wxWindow,
	public gst::PipelineUser
{
public:

	explicit MovieControlsWindow( wxWindow *parent );
	~MovieControlsWindow( void );
private:
	explicit MovieControlsWindow( MovieControlsWindow & );
	void operator=( MovieControlsWindow & );


	wxSlider *m_seekSlider;
	wxTimer  *m_timer;

	void
		onSeekSlider( wxScrollEvent &event );
	void
		onSeekTimer( wxTimerEvent &event );

	void
		onPipelineStateChange( PipelineState oldState, PipelineState newState );


	wxDECLARE_EVENT_TABLE();

};


	}

#endif