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
 
#ifndef BUTTONS_H
#define BUTTONS_H

#include <gtkmm/button.h>

/** Button containing an integral ID.
  * IDButton functions practically just like a normal Gtk::Button with the
  * the exception that it can hold an ID number. Also, another signal, 
  * signal_clicked_with_id, is emitted when this button is clicked. It contains
  * the ID of this button. You can set the ID by calling setID() and get the ID
  * by calling getID().
  */
 
// IDButton class  
class IDButton: public Gtk::Button {
	public:
		/// Default constructor
		/** Constructs a button with a label and ID.
		  * \param label The label this button should contain
		  * \param button_id The ID of this button
		*/
		IDButton(std::string label, int button_id=-1): Gtk::Button(label) {
			id=button_id;
			
			this->signal_clicked().connect(sigc::mem_fun(*this, &IDButton::parseClick));
		};
		
		/// Destructor
		virtual ~IDButton() {};
		
		/// Sets the ID of this button to button_id.
		/** \param button_id The new ID to assign to this button
		*/
		void setID(int button_id) {id=button_id;}
		
		/// Get the ID of this button.
		/** \return The integral ID of this button
		*/
		int getID() const {return id;}
		
		/// Another signal emitted when this button is clicked.
		sigc::signal<void, int> signal_clicked_with_id;
		
	private:
		// signal handlers
		// function that emits another signal when this button is clicked
		void parseClick() {
			signal_clicked_with_id(id);
		}
	
		int id;
};

#endif
