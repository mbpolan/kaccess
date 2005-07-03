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
 
#include <gtkmm/dialog.h> 
#include <gtkmm/entry.h>
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
	
	// connect treeview signals
	dtview->sigColumnClicked().connect(sigc::mem_fun(*this, &TableDesigner::updateDescriptions));
	
	treeViewWindow->add(*dtview);
	
	// now create the lower portion of the designer
	// frame comes first
	frame=manage(new Gtk::Frame);
	frame->set_size_request(450, 100);
	
	// scrolled window for field editors
	editorWindow=manage(new Gtk::ScrolledWindow);
	editorWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	
	// field description label
	msgLabel=manage(new Gtk::Label("Using the TableDesigner you can easily create your own tables."));
	
	// pack the scrolled window and label into the HBox
	hb->pack_start(*editorWindow);
	hb->pack_start(*msgLabel);
	
	// add the HBox to the frame container
	frame->add(*hb);
	
	// create the push buttons and pack them into an HButtonBox
	hbb=manage(new Gtk::HButtonBox);
	
	okButton=manage(new Gtk::Button("Save"));
	cancelButton=manage(new Gtk::Button("Cancel"));
	
	// connect button signals
	okButton->signal_clicked().connect(sigc::mem_fun(*this, &TableDesigner::onSaveTable));
	cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &TableDesigner::hide));
	
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

// save table handler
void TableDesigner::onSaveTable() {
	// check if this table is valid
	if (!dtview->tableValid())
		return;
	
	// continue saving...
	Gtk::Dialog d("Save Table", *this, true, true);
	
	// format the dialog
	Gtk::VBox *vb=d.get_vbox();
	Gtk::Label *lab=new Gtk::Label("Enter a name for this table");
	Gtk::Entry *entry=new Gtk::Entry;
	vb->pack_start(*manage(lab));
	vb->pack_start(*manage(entry));
	
	// add buttons
	d.add_button("OK", 0x00);
	d.add_button("Cancel", 0x01);
	
	// run the dialog
	d.show_all_children();
	if (d.run()==0x00) {
		std::string name=entry->get_text();
		
		// create a table model
		TableModel *tmodel=new TableModel;
		tmodel->setName(name);
		
		// add each row
		int c=0;
		for (Gtk::TreeModel::iterator it=dtview->tstore->children().begin(); it!=dtview->tstore->children().end(); ++it) {
			if ((*it) && !(((Glib::ustring) (*it)[dtview->colRec.fieldName]).empty())) {
				Glib::ustring rName=(*it)[dtview->colRec.fieldName];
				Glib::ustring rDesc=(*it)[dtview->colRec.fieldDescription];
				// TODO: field attributes
				TableDataModel *tdmodel=new TableDataModel;
				
				// primary key?
				if ((*it)[dtview->colRec.generic]=="P")
					tmodel->setPKeyRow(c);
				
				// add this row
				tmodel->addRow(TableModel::Row(rName, tdmodel, rDesc));
				c+=1;
			}
		}
		std::pair<std::string, TableModel*> p(name, tmodel);
		
		// emit the save signal
		sigSaveTable().emit(p);
	}
	
	this->hide();
};

// function to update the description label
void TableDesigner::updateDescriptions(int id) {
	// change the description label
	switch(id) {
		case 0x00: msgLabel->set_text("This is the name of the field that will appear as a new column in your table."); break;
		case 0x01: msgLabel->set_text("What kind of data should this field store is set here."); break;
		case 0x02: msgLabel->set_text("Enter a description of this field to help you remember its " 
						"purpose later."); break;
	}
};
