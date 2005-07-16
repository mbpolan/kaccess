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
// triplelist.h: the TripletList template container

#ifndef TRIPLELIST_H
#define TRIPLELIST_H

#include "triplet.h"

/** An STL-like container that holds three different types.
  * The TripleList template class is able to contain three different
  * types of objects and works almost like an STL container. 
  * 
  * Items can be added by calling append(). The erase() function will 
  * remove the requested objects based on the specified position. It will
  * also take care of reorganizing the internal arrays automatically. If you
  * need to know the position of an object in the list, a call to getPosition()
  * will do just that.
  * 
  * Replacing objects, however, is slightly different. The replace_x_() set of six functions 
  * is responsible for the task. The first set of three will ask for an object and the other
  * three will ask for an integral position. Both sets produce the same result and require a new object 
  * as a parameter that will take the place of the old one. The new object must coincide with
  * the proper array, whether it is the first, second, or third. You can use your template declaration 
  * to determine which of the arrays corresponds to what object.
*/
template <typename X, typename Y, typename Z>
class TripleList {
	public:
		/** Constructor
		  * \param length The size of the container
		*/
		TripleList(int length=256);
		
		/// Destructor
		virtual ~TripleList();
		
		/** Append data to the container
		  * \param data1 The first type of data to add
		  * \param data2 The second type of data to add
		  * \param data3 The third type of data to add
		*/
		void append(const X &data1, const Y &data2, const Z &data3);
		
		/** Erase data at a certain position
		  * \param pos The position of the data set
		  * \return true if the data was erased, false otherwise
		*/
		bool erase(int pos);
		
		/** Replace the first object based on position
		  * \param pos The position of the object
		  * \param obj The new replacement object
		  * \return true if the object was replaced, false otherwise
		*/
		bool replace1st(int pos, const X &obj);
		
		/** Replace the second object based on position
		  * \param pos The position of the object
		  * \param obj The new replacement object
		  * \return true if the object was replaced, false otherwise
		*/
		bool replace2nd(int pos, const Y &obj);
		
		/** Replace the third object based on position
		  * \param pos The position of the object
		  * \param obj The new replacement object
		  * \return true if the object was replaced, false otherwise
		*/
		bool replace3rd(int pos, const Z &obj);
		
		/** Replace the first object based on previous object
		  * \param pos The position of the object
		  * \param obj The new replacement object
		  * \return true if the object was replaced, false otherwise
		*/
		bool replace1st(const X &original, const X &obj);
		
		/** Replace the second object based on previous object
		  * \param pos The position of the object
		  * \param obj The new replacement object
		  * \return true if the object was replaced, false otherwise
		*/
		bool replace2nd(const Y &original, const Y &obj);
		
		/** Replace the third object based on previous object
		  * \param pos The position of the object
		  * \param obj The new replacement object
		  * \return true if the object was replaced, false otherwise
		*/
		bool replace3rd(const Z &original, const Z &obj);
		
		/** Get the position of the specified object
		  * \param obj The requested object
		  * \return The position of that object (-1 if not possible)
		*/
		int getPosition(const X &obj);
		
		/** Get the position of the specified object
		  * \param obj The requested object
		  * \return The position of that object (-1 if not possible)
		*/
		int getPosition(const Y &obj);
		
		/** Get the position of the specified object
		  * \param obj The requested object
		  * \return The position of that object (-1 if not possible)
		*/
		int getPosition(const Z &obj);
		
		/** Return an object in the first array
		  * \return The object requested
		*/
		X get1st(int pos) const { return (pos<=lsize ? xArray[pos] : NULL); };
		
		/** Return an object in the second array
		  * \return The object requested
		*/
		Y get2nd(int pos) const { return (pos<=lsize ? yArray[pos] : NULL); };
		
		/** Return an object in the third array
		  * \return The object requested
		*/
		Z get3rd(int pos) const { return (pos<=lsize ? zArray[pos] : NULL); };
		
		/** Get all the items in a certain position
		  * \param pos The position
		  * \return A Triplet containing the three objects
		*/
		Triplet<X, Y, Z> getItems(int pos);
		
		/** Overloaded operator [] for retrieving items
		  * The container will try to locate the object specified and,
		  * if possible, will return a Triplet containing the objects
		  * that have to same position as the specified one
		  *
		  * \param obj One of the objects
		  * \return A Triplet containing objects with the same position as the specified one
		*/
		Triplet<X, Y, Z> operator[](const X &obj);
		
		/** Overloaded operator [] for retrieving items
		  * The container will try to locate the object specified and,
		  * if possible, will return a Triplet containing the objects
		  * that have to same position as the specified one
		  *
		  * \param obj One of the objects
		  * \return A Triplet containing objects with the same position as the specified one
		*/
		Triplet<X, Y, Z> operator[](const Y &obj);
		
		/** Overloaded operator [] for retrieving items
		  * The container will try to locate the object specified and,
		  * if possible, will return a Triplet containing the objects
		  * that have to same position as the specified one
		  *
		  * \param obj One of the objects
		  * \return A Triplet containing objects with the same position as the specified one
		*/
		Triplet<X, Y, Z> operator[](const Z &obj);
		
		/// Get the size of the container
		int size() const { return lsize; };
		
	protected:
		// type arrays
		X *xArray;
		Y *yArray;
		Z *zArray;
		
		// the size of the container
		int lsize;
		
		// position of last added item
		int itPos;
};

/******************************************************************************
 * Implementations of TripleList template class...
 *****************************************************************************/

// constructor
template <typename X, typename Y, typename Z>
TripleList<X, Y, Z>::TripleList(int length): lsize(length), itPos(0) {
	xArray=new X[lsize];
	yArray=new Y[lsize];
	zArray=new Z[lsize];
};

// destructor
template <typename X, typename Y, typename Z>
TripleList<X, Y, Z>::~TripleList() {
	delete [] xArray;
	delete [] yArray;
	delete [] zArray;
};

// member function add
template <typename X, typename Y, typename Z>
void TripleList<X, Y, Z>::append(const X &data1, const Y &data2, const Z &data3) {
	// add the items
	xArray[itPos+1]=data1;
	yArray[itPos+1]=data2;
	zArray[itPos+1]=data3;
	
	// update variables
	lsize+=1;
	itPos+=1;
};

// member function remove
template <typename X, typename Y, typename Z>
bool TripleList<X, Y, Z>::erase(int pos) {
	bool yes=false;
	
	// remove from arrays
	for (int i=0; i<lsize; i++) {
		if (i==pos) {
			xArray[i]=0;
			yArray[i]=0;
			zArray[i]=0;
			
			// modify variables
			lsize-=1;
			itPos-=1;
			yes=true;
			
			break;
		}
	}
	
	// check if any changes to the arrays are necessary
	if (yes) {
		// rebuild the arrays to avoid the empty positions
		X *xTempArray=new X[lsize];
		Y *yTempArray=new Y[lsize];
		Z *zTempArray=new Z[lsize];
		
		// copy each valid member
		for (int i=0; i<lsize; i++) {
			xTempArray[i]=xArray[i];
			yTempArray[i]=yArray[i];
			zTempArray[i]=zArray[i];
		}
		
		// delete the previous arrays
		delete [] xArray;
		delete [] yArray;
		delete [] zArray;
		
		// reassign arrays
		xArray=xTempArray;
		yArray=yTempArray;
		zArray=zTempArray;
	}
	
	// return the result
	return yes;
};

// replace an object from the 1st array
template <typename X, typename Y, typename Z>
bool TripleList<X, Y, Z>::replace1st(int pos, const X &obj) {
	// the position needs to be less than or equal to the size 
	// of the container
	if (pos<=lsize) {
		xArray[pos]=obj;
		return true;
	}
	
	else
		return false;
};

// replace an object from the 2nd array
template <typename X, typename Y, typename Z>
bool TripleList<X, Y, Z>::replace2nd(int pos, const Y &obj) {
	// the position needs to be less than or equal to the size 
	// of the container
	if (pos<=lsize) {
		yArray[pos]=obj;
		return true;
	}
	
	else
		return false;
};

// replace an object from the 3rd array
template <typename X, typename Y, typename Z>
bool TripleList<X, Y, Z>::replace3rd(int pos, const Z &obj) {
	// the position needs to be less than or equal to the size 
	// of the container
	if (pos<=lsize) {
		zArray[pos]=obj;
		return true;
	}
	
	else
		return false;
};

// replace an object from the 1st array by original object
template <typename X, typename Y, typename Z>
bool TripleList<X, Y, Z>::replace1st(const X &original, const X &obj) {
	int pos=getPosition(original);
	
	// make sure the position is valid
	if (pos!=-1) {
		xArray[pos]=obj;
		return true;
	}
	
	else
		return false;
};

// replace an object from the 2nd array by original object
template <typename X, typename Y, typename Z>
bool TripleList<X, Y, Z>::replace2nd(const Y &original, const Y &obj) {
	int pos=getPosition(original);
	
	// make sure the position is valid
	if (pos!=-1) {
		yArray[pos]=obj;
		return true;
	}
	
	else
		return false;
};

// replace an object from the 3rd array by original object
template <typename X, typename Y, typename Z>
bool TripleList<X, Y, Z>::replace3rd(const Z &original, const Z &obj) {
	int pos=getPosition(original);
	
	// make sure the position is valid
	if (pos!=-1) {
		zArray[pos]=obj;
		return true;
	}
	
	else
		return false;
};

// get the position of an object in the arrays, if possible
template <typename X, typename Y, typename Z>
int TripleList<X, Y, Z>::getPosition(const X &obj) {
	int c=-1;
	
	// find the position
	for (int i=0; i<lsize; i++) {
		if (xArray[i]==obj) {
			c=i;
			break;
		}
	}
	
	// return the position
	return c;
};

// get the position of an object in the arrays, if possible
template <typename X, typename Y, typename Z>
int TripleList<X, Y, Z>::getPosition(const Y &obj) {
	int c=-1;
	
	// find the position
	for (int i=0; i<lsize; i++) {
		if (yArray[i]==obj) {
			c=i;
			break;
		}
	}
	
	// return the position
	return c;
};

// get the position of an object in the arrays, if possible
template <typename X, typename Y, typename Z>
int TripleList<X, Y, Z>::getPosition(const Z &obj) {
	int c=-1;
	
	// find the position
	for (int i=0; i<lsize; i++) {
		if (zArray[i]==obj) {
			c=i;
			break;
		}
	}
	
	// return the position
	return c;
};

// member function getItems
template <typename X, typename Y, typename Z>
Triplet<X, Y, Z> TripleList<X, Y, Z>::getItems(int pos) {
	// the working triplet
	Triplet<X, Y, Z> t;
	
	// get objects from lists
	for (int i=0; i<lsize; i++) {
		if (i==pos) {
			t.first=xArray[i];
			t.second=yArray[i];
			t.third=zArray[i];
			break;
		}
	}
	
	// return the triplet
	return t;
};

// overloaded member operator[]
template <typename X, typename Y, typename Z>
Triplet<X, Y, Z> TripleList<X, Y, Z>::operator[](const X &objX) {
	return getItems(getPosition(objX));
};

// overloaded member operator[]
template <typename X, typename Y, typename Z>
Triplet<X, Y, Z> TripleList<X, Y, Z>::operator[](const Y &objY) {
	return getItems(getPosition(objY));
};

// overloaded member operator[]
template <typename X, typename Y, typename Z>
Triplet<X, Y, Z> TripleList<X, Y, Z>::operator[](const Z &objZ) {
	return getItems(getPosition(objZ));
};

#endif
 
