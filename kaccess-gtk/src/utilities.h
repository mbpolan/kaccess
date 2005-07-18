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
// utilities.h: the Utilities namespace and functions

#ifndef UTILITIES_H
#define UTILITIES_H

namespace Utilities {
	/** Convert a char to an int
	  * \param ch The char to convert
	  * \return The converted int, 0 if unsuccessful
	*/
	int ctoi(char ch);
	
	/** Check if a char can be converted to an int
	  * \param ch The char to inspect
	  * \return true if the char is an int, false otherwise
	*/
	bool isInt(char ch);
};

#endif
