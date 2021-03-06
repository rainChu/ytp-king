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
#include "VideoTapeComposition.h"

#include <gst/gst.h>

#include "gst/Pipeline.h"


	namespace ytpking
	{
	namespace gst
	{
	namespace gnl
	{


VideoTapeComposition::VideoTapeComposition( void ) :
	m_sinkElement ( gst_element_factory_make( "autovideosink", NULL ) )
{
	g_signal_connect( m_selfElement, "pad-added", G_CALLBACK( onPadAdded ), m_sinkElement );
	
	g_object_set( m_selfElement, "caps", gst_caps_from_string( "video/x-raw-yuv;video/x-raw-rgb" ), NULL ); 
}


void
VideoTapeComposition::addTo( Pipeline &pipeline )
{
	gst_bin_add_many( GST_BIN( *pipeline ), m_selfElement, m_sinkElement, NULL );
}


	} } }