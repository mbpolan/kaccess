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
// dbtreeview.h: DBTreeView class

#ifndef DBTREEVIEW_H
#define DBTREEVIEW_H

#include <gtkmm/treeview.h>
#include <gtkmm/treestore.h>

/** A TreeView variant used in the DBWindow class.
  * DBTreeView is a derived class used in the DBWindow class. It contains
  * specific implementations that are necessary for DBWindow to function
  * correctly. Unless you are making your own DBWindow class, then you
  * shouldn't use this class directly.
*/

// the dbtreeview class
class DBTreeView: public Gtk::TreeView {
	public:
		/// Default constructor
		DBTreeView();
		
		// signals
		/// Signal emitted when an item is double clicked
		sigc::signal<void> itemDoubleClicked;
		
		// model columns
		class DBColumnRecord: public Gtk::TreeModel::ColumnRecord {
			public:
				DBColumnRecord() {
					add(item);
				}
				
				// columns
				Gtk::TreeModelColumn<Glib::ustring> item;
		};
		
		// column records
		DBColumnRecord colRec;
		
	private:
		// overloaded functions
		virtual bool on_button_press_event(GdkEventButton*);
		
		// tree store
		Glib::RefPtr<Gtk::TreeStore> tstore;
};

#endif
