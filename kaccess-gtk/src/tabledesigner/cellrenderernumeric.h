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
// cellrenderernumeric.h: the CellRendererNumeric class

#ifndef CELLRENDERERNUMERIC_H
#define CELLRENDERERNUMERIC_H
#include <iostream>
#include "cellrenderertable.h"

/** Derived renderer for numeric input.
  * This renderer does the job of validating text to make sure that
  * it only contains numeric characters.
*/
class CellRendererNumeric: public CellRendererTable {
	public:
		/// Constructor
		CellRendererNumeric(int col): CellRendererTable(col) {};
		
		/// Destructor
		virtual ~CellRendererNumeric() {};
		
	protected:
		/// Validates text for numeric input
		virtual Glib::ustring validate(Glib::ustring &text) {
			if (!(atof(text.c_str()) && text!="0") && !(atof(text.c_str())==0 && text=="0"))
				text=RENDERER_TEXT_ERROR_NOT_INT;
			
			// progress through to the parent
			return (CellRendererTable::validate(text));
		};
		
		// overloaded on_edited function
		virtual void on_edited(const Glib::ustring &path, const Glib::ustring &text) {
			// validate the text
			Glib::ustring newText=text;
			newText=validate(newText);
			
			// continue on to the parent function
			CellRendererTable::on_edited(path, newText);
		};
		
};

#endif
