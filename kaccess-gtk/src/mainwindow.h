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
// mainwindow.h: MainWindow class

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <gtkmm/actiongroup.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/table.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>

/** The main window used as a base for all new windows.
  * This is the main window that is the first to be drawn on the screen. If you plan
  * on making customized windows that should appear after this window is constructed,
  * then make sure to set a MainWindow as the parent for that window. This will ensure
  * that any windows opened will be properly disposed of once the application is closed.
*/

// the main window class
class MainWindow: public Gtk::Window {
	public:
		/// Default constructor 
		/** Constructs a default main window.
		  * \param path Path to a database file to open
		*/
		MainWindow(std::string path="NULL");
		
		/// Destructor
		virtual ~MainWindow();
		
	protected:
		// signal handlers
		void createNewDB() {};
		void openDB() {};
		void saveDB() {};
		
		// layout managers
		Gtk::ScrolledWindow *sWindow;
		Gtk::Table *table;
		Gtk::VBox *topVB;
		
		// labels
		Gtk::Label *mLabel;
		
		// tree view stuff
		Gtk::TreeView *tview;
		Glib::RefPtr<Gtk::TreeStore> tstore;
		
		// columns
		class ModelColumnRecord: public Gtk::TreeModel::ColumnRecord {
			public:
				ModelColumnRecord() {
					add(dbName);
				}
				
				// columns
				Gtk::TreeModelColumn<Glib::ustring> dbName;
		};
		
		// our model column record
		ModelColumnRecord colRecord;
		
		// menus and related things
		Glib::RefPtr<Gtk::UIManager> uiManager;
		Glib::RefPtr<Gtk::ActionGroup> actionGroup;
};

#endif
