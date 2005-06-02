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
// dbwindow.h: DBWindow class 

#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <iostream>
#include <gtkmm/actiongroup.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/table.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>
#include <vector>

#include "dbtreeview.h"

/** The window that is used for each database for control.
  * This is the window that control all aspects of database management. Everytime
  * a new database is made, it is assigned an instance of this window so the user
  * can control it.
*/

// the dbwindow class
class DBWindow: public Gtk::Window {
	public:
		/// Default constructor
		/** Constructs a new DBWindow
		  * \param title The name of this database
		*/
		DBWindow(std::string title="Database");
		
		/// Destructor
		~DBWindow();
		
		/// Method to set the title of this database
		/** \param title The name of the database
		*/
		void setTitle(std::string title) { this->set_title(title); }
		
		/// Method to get the title of this database
		/** \return The name of this database
		*/
		std::string getTitle() const { return this->get_title(); }
		
	private:
		// handlers
		void openTarget();
		void designNew() {};
		
		// containers
		Gtk::Frame *frame;
		Gtk::Table *table;
		Gtk::ScrolledWindow *sWindow;
		
		Gtk::VBox *vb; // button box
		Gtk::HBox *hb; // hbox containing tview and vbuttonbox
		
		// buttons
		Gtk::Button *tablesButton;
		Gtk::Button *formsButton;
		Gtk::Button *reportsButton;
		
		// toolbar
		Glib::RefPtr<Gtk::ActionGroup> actionGroup;
		Glib::RefPtr<Gtk::UIManager> uiManager;
		
		// vector of tree views
		std::vector<DBTreeView*> views;
		
		// other vars
		int currentView;
};

#endif
