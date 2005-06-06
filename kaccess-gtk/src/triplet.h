/***************************************************************************
 *   Copyright (C) 2005 by the KAccess Team                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/ 
// triplet.h: template class holding three different types of data 

#ifndef TRIPLET_H
#define TRIPLET_H

/** A template class that holds three different types of data.
  * This is a simple template class that can hold three different kinds
  * of data.
*/
template <class TX, class TY, class TZ>
class Triplet {
	public:
		/// Default constructor
		/** Creates a triple with the following data provided.
		  * \param dataA The first data
		  * \param dataB The second data
		  * \param dataC The third data
		*/
		Triplet(TX dataA, TY dataB, TZ dataC): first(dataA), second(dataB), third(dataC) {};
		
		/// Destructor
		virtual ~Triplet() {};
		
		/// First data variable
		TX first;
		
		/// Second data variable
		TY second;
		
		/// Third data variable
		TZ third;
};

#endif
