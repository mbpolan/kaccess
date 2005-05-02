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
// triplet.h: template class that stores 3 different data

// template class that stores 3 classes of data
template <class T, class T2, class T3>
class triplet {
    public:
	triplet(T data1, T2 data2, T3 data3);
	
	// member functions
	void clear();
	
	// data
	T first;
	T2 second;
	T3 third;
};

/***************************************************************************
  * Start template class triplet implementations
  ***************************************************************************/

// main constructor
template <class T, class T2, class T3>
triplet<T, T2, T3>::triplet(T data1, T2 data2, T3 data3) {
    first=data1;
    second=data2;
    third=data3;
};

// member function clear: reset the triplet
template <class T, class T2, class T3>
void triplet<T, T2, T3>::clear() {
    first=NULL;
    second=NULL;
    third=NULL;
};
