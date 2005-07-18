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
// cellrenderertable.h: the base CellRendererTable class

#ifndef CELLRENDERERTABLE_H
#define CELLRENDERERTABLE_H

#include <gtkmm/cellrenderertext.h>

// types of errors during text validation
#define RENDERER_TEXT_ERROR_NOT_INT		"!CHAR#"
#define RENDERER_TEXT_ERROR_NOT_STR		"!INT#"
#define RENDERER_TEXT_ERROR_BAD_DATE		"!DATE#"

/** Base CellRenderer for Table cells.
  * This derived CellRenderer class inherits from Gtk::CellRendererText. It
  * serves as a base for all derived renderers that are used in the various
  * tables found in KAccess.
  *
  * These renderers, however, are able to validate text via their protected
  * member function, validate(). If you are planning on making your own
  * renderer that derives from this class, then you should overload that
  * function so it suits your needs. Also, make sure to overload the default
  * on_edited() function so that it calls the validation and parent on_edited()
  * functions.
*/
class CellRendererTable: public Gtk::CellRendererText {
	public:
		/** Constructor
		  * \param col The column this renderer is assigned to
		*/
		CellRendererTable(int col): Gtk::CellRendererText(), column(col) {};
		
		/// Destructor
		virtual ~CellRendererTable() {};
		
		/** Set the renderer's column
		  * \param col The column to render to
		*/
		void setColumn(int col) { column=col; };
		
		/** Get the column for this renderer
		  * \return The column this renderer renders to
		*/
		int getColumn() const { return column; }
		
		/// typedef'd edited signal
		typedef sigc::signal<void, const Glib::ustring&, const Glib::ustring&, int> editedSig;
		
		/// Signal emitted when the renderer was edited
		editedSig sigEdited() const { return signalEdited; };
		
	protected:
		// the column that this renderer renders to
		int column;
		
		/** Validate the text and return it
		  * Overload this function if you are making a derived renderer
		*/
		virtual Glib::ustring validate(Glib::ustring &text) {
			return text;
		};
		
		/// Overloaded on_edited function
		virtual void on_edited(const Glib::ustring &path, const Glib::ustring &text) {
			// validate the text
			Glib::ustring newText=text;
			newText=validate(newText);
			
			// parent functions
			Gtk::CellRendererText::on_edited(path, newText);
			
			// emit the edited signal
			sigEdited().emit(path, newText, column);
		};
		
		// signal instances
		sigc::signal<void, const Glib::ustring&, const Glib::ustring&, int> signalEdited;
};

#endif
