/*  YTP King - Easy to use sentence mixer
 *  Copyright (C) 2013  Alex "rainChu" Haddad
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
#include "ytpking/SourcesNotebook.h"

#include "ytpking/SourcesPage.h"


	namespace ytpking
	{


SourcesNotebook::SourcesNotebook( wxWindow *parent ) :
	wxNotebook( parent, -1, wxDefaultPosition, wxDefaultSize, wxNB_LEFT )
{
	m_sourcesPage = new SourcesPage( this );
	AddPage( m_sourcesPage, "Sources" );

	Layout();
}



	}