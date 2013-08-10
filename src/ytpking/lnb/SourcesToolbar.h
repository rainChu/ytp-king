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
//#include <wx/ribbon/toolbar.h>
#ifndef __YTPKING_LNB_SourcesToolbar_h
#define __YTPKING_LNB_SourcesToolbar_h

#include <wx/sizer.h>


	namespace ytpking
	{
	namespace lnb
	{


// TODO Collapse into SamplesPage
//      Also, change EventId to not be global. Only the page accesses it now.
class SourcesToolbar :
	public wxBoxSizer
{
public:

	SourcesToolbar( wxWindow *parent );

};


	} }


#endif