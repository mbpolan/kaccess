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

#include <gtkmm/menu.h>
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
		
		/// Destructor
		virtual ~DBTreeView();
		
		// signals
		/// Signal emitted when an item is double clicked
		sigc::signal<void> itemDoubleClicked;
		
		/// Signal emitted when an item is requested to be edited
		sigc::signal<void, Gtk::TreeModel::iterator> itemRequestEdit;
		
		/// Derived class containing the column record
		class DBColumnRecord: public Gtk::TreeModel::ColumnRecord {
			public:
				DBColumnRecord() {
					add(item);
				}
				
				// columns
				Gtk::TreeModelColumn<Glib::ustring> item;
		};
		
		/// Column records for the view
		DBColumnRecord colRec;
		
		/// Get the TreeStore for this view
		Glib::RefPtr<Gtk::TreeStore> getTreeModel() const { return tstore; }
		
	private:
		// overloaded functions
		virtual bool on_button_press_event(GdkEventButton*);
		
		// signal handlers
		void onEditMenuPopup();
		
		// tree store
		Glib::RefPtr<Gtk::TreeStore> tstore;
		
		// menu
		Gtk::Menu *cMenu;
};

#endif
