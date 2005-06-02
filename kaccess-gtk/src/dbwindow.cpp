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
// dbwindow.cpp: implementations of DBWindow class

#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/buttonbox.h>
#include "dbwindow.h"

// constructor for DBWindow
DBWindow::DBWindow(std::string title): Gtk::Window(), currentView(0) {
	set_title(title);
	set_border_width(4);
	
	// set up the main table first
	table=manage(new Gtk::Table(5, 5, false));
	table->set_spacings(3);
	
	// create the action group and actions
	actionGroup=Gtk::ActionGroup::create();
	
	actionGroup->add(Gtk::Action::create("ToolbarDesignSelected", "Design", "Design a new item"),
			 sigc::mem_fun(*this, &DBWindow::designNew));
			
	/*actionGroup->add(Gtk::Action::create("ToolbarDeleteSelected", "Delete", "Delete the selected item"),
			 sigc::mem_fun(*this, &DBWindow::deleteSelected));*/
			 
	// make the ui manager
	uiManager=Gtk::UIManager::create();
	uiManager->insert_action_group(actionGroup);
	
	// make a ui string
	try {
		Glib::ustring buffer=
		"<ui>"
		"	<toolbar name='Toolbar'>"
		"		<toolitem action='ToolbarDesignSelected'/>"
		"	</toolbar>"
		"</ui>";
	
		// add the ui string to the ui manager
		uiManager->add_ui_from_string(buffer);
	}
	
	catch(const Glib::Error &e) {
		std::cout << "Unable to create toolbars: " << e.what() << std::endl;
	}
	
	// create the toolbar
	Gtk::VBox *tvb=manage(new Gtk::VBox);
	Gtk::Widget *toolbar=uiManager->get_widget("/Toolbar");
	if (toolbar)
		tvb->pack_start(*toolbar, Gtk::PACK_SHRINK);
	
	// create some containers
	vb=manage(new Gtk::VBox);
	hb=manage(new Gtk::HBox);
	
	// create the buttons on the left
	tablesButton=manage(new Gtk::Button("Tables"));
	formsButton=manage(new Gtk::Button("Forms"));
	reportsButton=manage(new Gtk::Button("Reports"));
	
	// pack the buttons into a vbox
	vb->pack_start(*tablesButton);
	vb->pack_start(*formsButton);
	vb->pack_start(*reportsButton);
	hb->pack_start(*vb, Gtk::PACK_SHRINK);
	
	// create the tree views in the middle of the window
	for (int i=0; i<3; i++) {
		views.push_back(manage(new DBTreeView));
		views[i]->set_size_request(240, 140);
	}
	
	// add some columns
	views[0]->append_column("Tables", views[0]->colRec.item);
	views[1]->append_column("Forms", views[1]->colRec.item);
	views[2]->append_column("Reports", views[2]->colRec.item);
	
	// now make the scrolled window for the tree view
	sWindow=manage(new Gtk::ScrolledWindow);
	sWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	sWindow->add(*views[0]);
	hb->pack_start(*sWindow, Gtk::PACK_SHRINK);
	
	// create the frame
	frame=manage(new Gtk::Frame);
	
	// add the button group and tree view to the box
	frame->add(*hb);
	
	// finally pack the layout managers into the table
	table->attach(*tvb, 0, 1, 0, 1);
	table->attach(*frame, 0, 1, 1, 2);
	
	// finish stuff up
	add(*table);
	show_all_children();
};

// destructor
DBWindow::~ DBWindow() {
};

// function to open a target on the list
void DBWindow::openTarget() {
};
