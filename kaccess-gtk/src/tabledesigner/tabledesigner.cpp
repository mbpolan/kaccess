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
 
#include "tabledesigner.h"

// constructor
TableDesigner::TableDesigner(): Gtk::Window() {
	set_title("Table Designer: New Table"); // TODO: table naming
	
	// create the box containers
	vb=manage(new Gtk::VBox);
	vb->set_spacing(3);
	
	hb=manage(new Gtk::HBox);
	hb->set_spacing(5);
	
	// create the tree view inside a scrolled window
	treeViewWindow=manage(new Gtk::ScrolledWindow);
	dtview=manage(new DesignerTreeView);
	dtview->set_size_request(450, 250);
	treeViewWindow->add(*dtview);
	
	// now create the lower portion of the designer
	// frame comes first
	frame=manage(new Gtk::Frame);
	frame->set_size_request(450, 100);
	
	// scrolled window for field editors
	editorWindow=manage(new Gtk::ScrolledWindow);
	editorWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	
	// field description label
	msgLabel=manage(new Gtk::Label("msg label")); // TODO: descriptions for fields
	
	// pack the scrolled window and label into the HBox
	hb->pack_start(*editorWindow);
	hb->pack_start(*msgLabel);
	
	// add the HBox to the frame container
	frame->add(*hb);
	
	// create the push buttons and pack them into an HButtonBox
	hbb=manage(new Gtk::HButtonBox);
	
	okButton=manage(new Gtk::Button("Save"));
	cancelButton=manage(new Gtk::Button("Cancel"));
	
	// pack the buttons
	hbb->pack_start(*okButton);
	hbb->pack_start(*cancelButton);
	
	// pack the widgets into the main VBox
	vb->pack_start(*treeViewWindow);
	vb->pack_start(*frame);
	vb->pack_start(*hbb);
	
	// add the parentHB into the main container
	add(*vb);
	
	// show widgets
	show_all_children();
};

// destructor
TableDesigner::~TableDesigner() {
};
