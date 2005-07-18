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
// cellrendererdatetime.h: the CellRendererDateTime class

#ifndef CELLRENDERERDATETIME_H
#define CELLRENDERERDATETIME_H

#include "cellrenderertable.h"
#include "utilities.h"
using namespace Utilities;

// the different ways to display a date
enum RENDERER_DATE_FORMAT {
	RENDERER_DATE_MMDDYYYY	= 0x00,
	RENDERER_DATE_DDMMYYYY	= 0x01,
	RENDERER_DATE_YYYYMMDD	= 0x02,
	RENDERER_DATE_YYYYDDMM	= 0x03
};

/** Derived renderer for date and time input.
  * This renderer validates text to make sure that it abides to
  * the specified date and time format.
*/
class CellRendererDateTime: public CellRendererTable {
	public:
		/// Constructor
		CellRendererDateTime(int col): CellRendererTable(col), DATE_FORMAT(RENDERER_DATE_MMDDYYYY) {};
		
		/// Destructor
		virtual ~CellRendererDateTime() {};
		
		/** Set the date format
		  * \param _FORMAT The date format
		*/
		void setDateFormat(RENDERER_DATE_FORMAT _FORMAT) { DATE_FORMAT=_FORMAT; };
		
		/** Get the renderer's date format
		  * \return The renderer's assigned date format
		*/
		RENDERER_DATE_FORMAT getDateFormat() const { return DATE_FORMAT; };
		
	protected:
		// the date format
		RENDERER_DATE_FORMAT DATE_FORMAT;
		
		/// Validates text for proper date/time format
		virtual Glib::ustring validate(Glib::ustring &text) {
			// parse the format
			switch (DATE_FORMAT) {
				case RENDERER_DATE_DDMMYYYY:
				case RENDERER_DATE_MMDDYYYY: {
					// format is: 01/01/2005 (example)
					// the first 2 bytes need to be followed by a forward slash. the same applies for the next 3.
					// the last 4 bytes need to be integers.
					if ((isInt(text[0]) && isInt(text[1]) && text[2]=='/') && 
					    (isInt(text[3]) && isInt(text[4]) && text[5]=='/') && 
					    (isInt(text[6]) && isInt(text[7]) && isInt(text[8]) && isInt(text[9])))
					    	return text;
					
					// the format is not valid
					else
						return (Glib::ustring) RENDERER_TEXT_ERROR_BAD_DATE;
				};
				break;
				
				case RENDERER_DATE_YYYYDDMM:
				case RENDERER_DATE_YYYYMMDD: {
					// format is: 2005/01/01 (example)
					// reverse of the previous case. the first 4 bytes must be integers followed by a forward slash.
					// the next 3 must be integers followed by another forward slash. the last 2 must be integers
					if ((isInt(text[0]) && isInt(text[1]) && isInt(text[2]) && isInt(text[3]) && text[4]=='/') &&
					    (isInt(text[5]) && isInt(text[6]) && text[7]=='/') &&
					    (isInt(text[8]) && isInt(text[9])))
					    	return text;
					
					// invalid format
					else
						return (Glib::ustring) RENDERER_TEXT_ERROR_BAD_DATE;
				};
				break;
			}
		};
		
		// overloaded on_edited() function
		virtual void on_edited(const Glib::ustring &path, const Glib::ustring &text) {
			// validate text
			Glib::ustring newText=text;
			newText=validate(newText);
			
			// continue on to the parent function
			CellRendererTable::on_edited(path, newText);
		};
};

#endif
