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
#include <gtkmm/image.h>
#include <gtkmm/frame.h>
#include <gtkmm/buttonbox.h>

#include "dbwindow.h"
#include "tabledesigner/tabledesigner.h"

// icons
#include "icons/design_table.xpm"
#include "icons/design_form.xpm"
#include "icons/design_report.xpm"
#include "icons/new_table.xpm"
#include "icons/new_form.xpm"
#include "icons/new_report.xpm"
#include "icons/open_generic.xpm"

// constructor for DBWindow
DBWindow::DBWindow(std::string title): Gtk::Window(), currentView(0) {
	set_title(title);
	set_border_width(4);
	
	// set up the main table first
	table=manage(new Gtk::Table(5, 5, false));
	table->set_spacings(3);
	
	// create the row of boxes on the top of the window
	hbb=manage(new Gtk::HButtonBox);
	
	// buttons with images; start with table images
	openSelectedButton=manage(new Gtk::Button);
	openSelectedButton->add(*(manage(new Gtk::Image(Gdk::Pixbuf::create_from_xpm_data(open_generic_xpm)))));
	openSelectedButton->signal_clicked().connect(sigc::mem_fun(*this, &DBWindow::openSelectedItem));
	
	designSelectedButton=manage(new Gtk::Button);
	designSelectedButton->add(*(manage(new Gtk::Image(Gdk::Pixbuf::create_from_xpm_data(design_table_xpm)))));
	designSelectedButton->signal_clicked().connect(sigc::mem_fun(*this, &DBWindow::designSelectedItem));
	
	newSelectedButton=manage(new Gtk::Button);
	newSelectedButton->add(*(manage(new Gtk::Image(Gdk::Pixbuf::create_from_xpm_data(new_table_xpm)))));
	newSelectedButton->signal_clicked().connect(sigc::mem_fun(*this, &DBWindow::newSelectedItem));
	
	// pack the buttons
	hbb->pack_start(*openSelectedButton);
	hbb->pack_start(*designSelectedButton);
	hbb->pack_start(*newSelectedButton);
	
	// create some containers
	vb=manage(new Gtk::VBox);
	hb=manage(new Gtk::HBox);
	
	// create the buttons on the left
	tablesButton=manage(new IDButton("Tables", 0x00));
	tablesButton->signal_clicked_with_id.connect(sigc::mem_fun(*this, &DBWindow::changeView));
	
	formsButton=manage(new IDButton("Forms", 0x01));
	formsButton->signal_clicked_with_id.connect(sigc::mem_fun(*this, &DBWindow::changeView));
	
	reportsButton=manage(new IDButton("Reports", 0x02));
	reportsButton->signal_clicked_with_id.connect(sigc::mem_fun(*this, &DBWindow::changeView));
	
	// pack the buttons into a vbox
	vb->pack_start(*tablesButton);
	vb->pack_start(*formsButton);
	vb->pack_start(*reportsButton);
	hb->pack_start(*vb, Gtk::PACK_SHRINK);
	
	// create the tree views in the middle of the window
	for (int i=0; i<3; i++) {
		views.push_back(manage(new DBTreeView));
		views[i]->set_size_request(240, 140);
		
		// connect signals
		views[i]->itemDoubleClicked.connect(sigc::mem_fun(*this, &DBWindow::openTarget));
		views[i]->itemRequestEdit.connect(sigc::mem_fun(*this, &DBWindow::editItem));
	}
	
	// add some columns
	views[0]->append_column("Tables", views[0]->colRec.item);
	views[1]->append_column("Forms", views[1]->colRec.item);
	views[2]->append_column("Reports", views[2]->colRec.item);
	
	// make some rows containign options
	Gtk::TreeModel::Row row=*(views[0]->getTreeModel()->append());
	row[views[0]->colRec.item]="Create a table in design view";
	
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
	table->attach(*hbb, 0, 1, 0, 1);
	table->attach(*frame, 0, 1, 1, 2);
	
	// finish stuff up
	add(*table);
	show_all_children();
};

// destructor
DBWindow::~ DBWindow() {
	// clean the queue
	for(std::list<Gtk::Widget*>::iterator it=destroyQueue.begin(); it!=destroyQueue.end(); ++it) {
		if ((*it)) {
			delete (*it);
			it=destroyQueue.erase(it);
		}
	}
};

// function that changes the TreeView displayed
void DBWindow::changeView(int view_id) {
	if (currentView==view_id)
		return;
	
	// remove the previous view from the scrolled window
	sWindow->remove();
	sWindow->add(*views[view_id]);
	
	Gtk::Image *dImage=dynamic_cast<Gtk::Image*> (designSelectedButton->get_child());
	Gtk::Image *nImage=dynamic_cast<Gtk::Image*> (newSelectedButton->get_child());
	
	// change the button images
	switch(view_id) {
		case 0x00: {
			dImage->set(Gdk::Pixbuf::create_from_xpm_data(design_table_xpm));
			nImage->set(Gdk::Pixbuf::create_from_xpm_data(new_table_xpm));
		};
		break;
		
		case 0x01: {
			dImage->set(Gdk::Pixbuf::create_from_xpm_data(design_form_xpm));
			nImage->set(Gdk::Pixbuf::create_from_xpm_data(new_form_xpm));
		};
		break;
		
		case 0x02: {
			dImage->set(Gdk::Pixbuf::create_from_xpm_data(design_report_xpm));
			nImage->set(Gdk::Pixbuf::create_from_xpm_data(new_report_xpm));
		};
		break;
	}
	
	// change the id
	currentView=view_id;
	
	show_all_children();
};

// function to open a target on the list
void DBWindow::openTarget() {
	Glib::RefPtr<Gtk::TreeView::Selection> sel=views[currentView]->get_selection();
	if (sel) {
		Gtk::TreeModel::iterator it=sel->get_selected();
		
		#ifdef DEBUG
			std::cout << "File: " << __FILE__ << " at line: " << __LINE__ << ": Should open target: "
				  << (*it)[views[currentView]->colRec.item] << "\n";
		#endif
		
	}
};

// function to edit an item's name
void DBWindow::editItem(Gtk::TreeModel::iterator it) {
	// name of the item
	Glib::ustring name=(*it)[views[currentView]->colRec.item];
	
	#ifdef DEBUG
		std::cout << "File: " << __FILE__ << " at line: " << __LINE__ << ": Item to edit: " << name << std::endl;
	#endif
};

// function to design a new instance of the current item
void DBWindow::designSelectedItem() {
	// check which view we are in now
	switch(currentView) {
		case 0x00: {
			TableDesigner *tb=new TableDesigner;
			tb->present();
			
			destroyQueue.push_back(tb);
		};
		break;
		
		case 0x01: break;
		
		case 0x02: break;
	}
};
