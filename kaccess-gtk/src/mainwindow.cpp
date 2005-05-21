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
// mainwindow.cpp: implementations of MainWindow class

#include <gtkmm/menubar.h>
#include <gtkmm/stock.h>
#include <gtkmm/toolbar.h>
#include "mainwindow.h"

// MainWindow class default constructor
MainWindow::MainWindow(std::string path): Gtk::Window() { 
	set_title("KAccess");
	set_default_size(365, 155);
	
	// set up the menu bar first
	actionGroup=Gtk::ActionGroup::create();
	
	// add menu actions
	actionGroup->add(Gtk::Action::create("FileNewDB", Gtk::Stock::NEW, "_New Database", "Create a new database"),
			 sigc::mem_fun(*this, &MainWindow::createNewDB));
	
	actionGroup->add(Gtk::Action::create("FileOpenDB", Gtk::Stock::OPEN, "_Open Database", "Open a database"),
			 sigc::mem_fun(*this, &MainWindow::openDB));
			
	actionGroup->add(Gtk::Action::create("FileSaveDB", Gtk::Stock::SAVE, "_Save Database", "Save this database"),
			 sigc::mem_fun(*this, &MainWindow::saveDB));
			
	actionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT, "_Quit", "Close KAccess"),
			 sigc::mem_fun(*this, &MainWindow::hide));
			 
	// add menus
	actionGroup->add(Gtk::Action::create("FileMenu", "File"));
	actionGroup->add(Gtk::Action::create("HelpMenu", "Help"));
	
	// create the UI manager
	uiManager=Gtk::UIManager::create();
	uiManager->insert_action_group(actionGroup);
	
	// layout the menu bar
	try {
		Glib::ustring buffer=
			"<ui>"
			"	<menubar name='MainMenuBar'>"
			"		<menu action='FileMenu'>"
			"			<menuitem action='FileNewDB'/>"
			"			<menuitem action='FileOpenDB'/>"
			"			<menuitem action='FileSaveDB'/>"
			"			<menuitem action='FileQuit'/>"
			"		</menu>"
			"	</menubar>"
			"	<toolbar name='MainToolBar'>"
			"		<toolitem action='FileNewDB'/>"
			"		<toolitem action='FileOpenDB'/>"
			"		<toolitem action='FileSaveDB'/>"
			"	</toolbar>"
			"</ui>";
	
		// add this layout to the ui manager
		uiManager->add_ui_from_string(buffer);
	}
	
	// catch any exceptions
	catch(const Glib::Error &e) {
		std::cerr << "Unable to build menus: " << e.what() << "\n";
	}
	
	// pack the menu bars
	topVB=new Gtk::VBox;
	Gtk::Widget *menuBar=uiManager->get_widget("/MainMenuBar");
	if (menuBar)
		topVB->pack_start(*menuBar, Gtk::PACK_SHRINK);
	
	Gtk::Widget *toolBar=uiManager->get_widget("/MainToolBar");
	if (toolBar) {
		((Gtk::Toolbar*) toolBar)->set_toolbar_style(Gtk::TOOLBAR_ICONS);
		topVB->pack_start(*toolBar, Gtk::PACK_SHRINK);
	}
		
	// create the main table
	table=new Gtk::Table(3, 1, false);
		
	// add the vbox to the table
	table->attach(*topVB, 0, 1, 0, 1);
	
	// overview label
	mLabel=new Gtk::Label("Welcome to KAccess. All of your databases will be listed below. \nRight click any of the"
			      "databases for a menu of options.");
			      
	// add labels to table
	table->attach(*mLabel, 0, 1, 1, 2);
			      
	// now we make the treeview and its componenets
	tstore=Gtk::TreeStore::create(colRecord);
	tview=new Gtk::TreeView(tstore);
	tview->set_size_request(364, 100);
	
	// set up columns
	tview->append_column("Database Name", colRecord.dbName);
	
	// add the treeview to the scrolled window
	sWindow=new Gtk::ScrolledWindow;
	sWindow->add(*tview);
	
	// attach the window
	table->attach(*sWindow, 0, 1, 2, 3);
	
	// add the table to the main container
	add(*table);
	
	// show the widgets
	table->show();
	table->show_all_children();
	topVB->show_all_children();

};

MainWindow::~MainWindow() {
};
