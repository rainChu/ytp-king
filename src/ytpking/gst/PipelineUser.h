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
#ifndef __YTPKING_GST_MainWindow_h
#define __YTPKING_GST_MainWindow_h


	namespace ytpking
	{
	namespace gst
	{


class Pipeline;


class PipelineUser
{
	friend class Pipeline;

public:
	explicit PipelineUser( Pipeline &pipeline );
	~PipelineUser( void );
private:
	explicit PipelineUser( PipelineUser & );
	void operator=( Pipeline & );

protected:

	enum PipelineState
	{
		Stopped,
		Paused,
		Playing
	};

	/** The pipeline state has changed. */
	virtual void
		onPipelineStateChange( PipelineState oldState, PipelineState newState ) = 0;

private:

	Pipeline *m_pipeline;

};


	} }

#endif