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
#ifndef __YTPKING_SMP_TapeUser_h
#define __YTPKING_SMP_TapeUser_h


	namespace ytpking
	{
	namespace smp
	{


class SampleInstance;
class Tape;
class TapeManager;


/** Base class for classes which are affected when a Sample is added or removed. */
class TapeUser
{
friend class TapeManager;

public:
	explicit TapeUser( TapeManager &manager );
	virtual ~TapeUser( void );
private:
	explicit TapeUser( TapeUser & );
	void operator=( TapeUser & );
protected:

	/** A new Tape has been added to TapeManager object.
	\param addedTape The newly added Tape. */
	virtual void
		onAddTape( Tape &addedTape );

	/** Called when a Tape is selected.
	\param selectedTape The newly selected Tape. If the Tape is deselected, NULL. */
	virtual void
		onSelectTape( Tape *selectedTape );

	/** Called when a Tape is about to be deleted.
	If a pointer matching deletedTape is held, it should be set to NULL or otherwise
	set to no longer match the sample, as that data is soon to be destroyed.
	\param deletedTape The Tape which will soon be destroyed by TapeManager */
	virtual void
		onDeleteTape( Tape &deletedTape );

	/** Called when a Tape has been renamed.
	\param newTapeName The new name of the Tape
	\param tape        A pointer to the Tape being renamed. */
	virtual void
		onRenameTape( Tape &tape );

	/** Called when all the tapes should be (re)loaded from the beginning. */
	virtual void
		onLoadAllTapes( void );


	virtual void
		onTapeAddInstance( Tape &tape, SampleInstance &sampleInstance );

	virtual void
		onTapeDeleteInstance( Tape &tape, SampleInstance &sampleInstance );


private:

	TapeManager *m_manager;

};


	} }


#endif
