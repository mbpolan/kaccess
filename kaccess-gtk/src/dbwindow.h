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
#include <gtkmm/buttonbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/table.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>
#include <list>
#include <map>
#include <vector>

#include "buttons.h"
#include "dbtreeview.h"
#include "tabledesigner/tablemodel.h"
#include "tabledesigner/tableviewer.h"
#include "triplelist.h"

#define DBWIN_VIEW_TABLES	0
#define DBWIN_VIEW_FORMS	1
#define DBWIN_VIEW_REPORTS	2

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
		void changeView(int view_id);
		
		void openTarget();
		void editItem(Gtk::TreeModel::iterator it);
		
		void openSelectedItem() { };
		void designSelectedItem();
		void newSelectedItem() { };
		
		void saveTable(std::pair<std::string, TableModel*>, bool);
		
		// containers
		Gtk::Frame *frame;
		Gtk::Table *table;
		Gtk::ScrolledWindow *sWindow;
		
		Gtk::VBox *vb; // button box
		Gtk::HBox *hb; // hbox containing tview and vbuttonbox
		Gtk::HButtonBox *hbb; // "toolbar" box
		
		// buttons
		IDButton *tablesButton;
		IDButton *formsButton;
		IDButton *reportsButton;
		Gtk::Button *openSelectedButton;
		Gtk::Button *designSelectedButton;
		Gtk::Button *newSelectedButton;
		
		// vector of tree views
		std::vector<DBTreeView*> views;
		
		// list of tables
		TripleList<std::string, TableModel*, TableViewer*> tables;
		
		// other vars
		int currentView;
		
		// destroy queue
		std::list<Gtk::Widget*> destroyQueue;
};

#endif
