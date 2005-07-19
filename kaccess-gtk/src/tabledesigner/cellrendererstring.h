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
// cellrendererstring.h: the CellRendererString class

#ifndef CELLRENDERERSTRING_H
#define CELLRENDERERSTRING_H

#include "cellrenderertable.h"

/** Derived renderer for string text.
  * This renderer validates plain strings for various requirements, such
  * as length, case, etc.
*/
class CellRendererString: public CellRendererTable {
	public:
		/// Constructor
		CellRendererString(int col): CellRendererTable(col) {};
		
		/// Destructor
		virtual ~CellRendererString() {};
		
	protected:
		/// Validates strings
		virtual Glib::ustring validate(Glib::ustring &text) {
			Glib::ustring newText=CellRendererTable::validate(text);
			return newText;
		}
		
		// overloaded on_edited() function
		virtual void on_edited(const Glib::ustring &path, const Glib::ustring &text) {
			Glib::ustring newText=validate(const_cast<Glib::ustring&> (text));
			CellRendererTable::on_edited(path, newText);
		};
};

#endif
