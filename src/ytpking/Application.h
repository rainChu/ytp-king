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
#include <wx/wx.h>


	namespace ytpking
	{


class SamplesDataFile;
class TapesDataFile;


/** The YTP King app itself.

This is instantiated by wxWidgets, in the automatically generated main()
*/
class Application :
	public ::wxApp
{
public:

	Application( void );
	~Application( void );

private:

	virtual bool OnInit( void )
		override;

	/** Holds the cwd.
	This will never be undefined after the ctor.
	If there was an error initializing it, this is a 0 length c string. */
	char m_currentDirectory[MAX_PATH];

	SamplesDataFile *m_samplesDataFile;
	TapesDataFile   *m_tapesDataFile;

	wxLog *m_logger;

};


	}