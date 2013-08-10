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
#ifndef __YTPKING_LNB_LibraryNotebook_h
#define __YTPKING_LNB_LibraryNotebook_h


#include <wx/notebook.h>


	namespace ytpking
	{
	namespace lnb
	{


class SamplesPage;

class LibraryNotebook :
	public ::wxNotebook
{
public:

	LibraryNotebook( wxWindow *parent, int samplesId );

	wxNotebookPage *m_sourcesPage;
	SamplesPage    *m_samplesPage;
	wxNotebookPage *m_tapesPage;

};


	} }


#endif