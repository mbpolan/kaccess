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
#include <sstream>
#include "tabledesigner.h"

// constructor
TableDesigner::TableDesigner(): Gtk::Window(), originalSave(true) {
	// format the title
	tname="New Table";
	std::stringstream ss;
	ss << "TableDesigner: " << tname << std::endl;
	
	// set the title
	set_title(ss.str());
	
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
	msgLabel=manage(new Gtk::Label());
	msgLabel->set_markup("<span foreground='blue'>Using the TableDesigner you can easily create your own tables.</span>");
	
	// pack the scrolled window and label into the HBox
	hb->pack_start(*editorWindow);
	hb->pack_start(*msgLabel);
	
	// add the HBox to the frame container
	frame->add(*hb);
	
	// create the push buttons and pack them into an HButtonBox
	hbb=manage(new Gtk::HButtonBox);
	
	okButton=manage(new Gtk::Button("OK"));
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

// set the model to edit the table
void TableDesigner::setModel(TableModel *tmodel) {
	TableModel::Row row;
	Gtk::TreeModel::Row trow;
	originalSave=false;
	
	// set the name
	tname=tmodel->getName();
	
	// set the title
	std::stringstream ss;
	ss << "TableDesigner: " << tname;
	set_title(ss.str());
	
	// remove all rows first
	dtview->tstore->clear();
	
	// each designer has 50 rows by default, so find out how much need
	// to be added after the model's data is added
	int rows=(tmodel->size()<50 ? 50-tmodel->size() : 0);
	
	// load each row
	for (int i=0; i<tmodel->size(); i++) {
		row=tmodel->getRow(i);
		
		// append a row for this field
		std::string name=row.getName();
		std::string type=parseRowTypeByEnum(row.getData()->getRowType());
		std::string desc=row.getDescription();
		
		// modify this row
		trow=*(dtview->tstore->append());
		trow[dtview->colRec.fieldName]=name;
		trow[dtview->colRec.fieldType]=type;
		trow[dtview->colRec.fieldDescription]=desc;
		
		// check for primary key
		if (tmodel->getPKeyRow()==i)
			dtview->setPKeyRow(i);
	}
	
	// add remaining rows
	for (int i=0; i<rows; i++)
		dtview->tstore->append();
};

// save table handler
void TableDesigner::onSaveTable() {
	// check if this table is valid
	if (!dtview->tableValid())
		return;
	
	// continue saving...
	// check if we are overwriting or editing
	int id;
	std::string name=tname;
	if (originalSave) {
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
		id=d.run();
		
		// check the id
		if (id==0x00) {
			// get the name
			name=entry->get_text();
		}
		
		else
			return;
	}
	
	// create a table model
	TableModel *tmodel=new TableModel;
	tmodel->setName(name);
	
	// add each row
	int c=0;
	for (Gtk::TreeModel::iterator it=dtview->tstore->children().begin(); it!=dtview->tstore->children().end(); ++it) {
		if ((*it) && !(((Glib::ustring) (*it)[dtview->colRec.fieldName]).empty())) {
			Glib::ustring rName=(*it)[dtview->colRec.fieldName];
			Glib::ustring rType=(*it)[dtview->colRec.fieldType];
			Glib::ustring rDesc=(*it)[dtview->colRec.fieldDescription];
			
			// field attributes
			TableDataModel *tdmodel=new TableDataModel;
			
			// check the row type
			tdmodel->setRowType(parseRowTypeByString(rType));
			
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
	sigSaveTable().emit(p, originalSave);
	
	this->hide();
};

// function to update the description label
void TableDesigner::updateDescriptions(int id) {
	// change the description label
	switch(id) {
		case 0x00: msgLabel->set_markup("<span foreground='blue'>"
						"This is the name of the field that will appear as a new column in your table."
						"</span>"); break;
		
		case 0x01: msgLabel->set_markup("<span foreground='blue'>"
						"What kind of data should this field store is set here."
						"</span>"); break;
		
		case 0x02: msgLabel->set_markup("<span foreground='blue'>"
						"Enter a description of this field to help you remember its " 
						"purpose later."
						"</span>"); break;
	}
};

// parse the type of row
ROW_TYPE TableDesigner::parseRowTypeByString(std::string type) {
	// check the string and return the row type
	ROW_TYPE _TYPE;
	
	// text row
	if (type=="Text")
		_TYPE=ROW_TEXT;
	
	// number row
	else if (type=="Number")
		_TYPE=ROW_NUMBER;
	
	// date/time row
	else if (type=="Date/Time")
		_TYPE=ROW_DATE_TIME;
	
	// memo row
	else if (type=="Memo")
		_TYPE=ROW_MEMO;
	
	// yes/no row
	else if (type=="Yes/No")
		_TYPE=ROW_YES_NO;
	
	// return the row
	return _TYPE;
};

// parse the row type by enum
std::string TableDesigner::parseRowTypeByEnum(ROW_TYPE _TYPE) {
	// check the type and return a string
	switch(_TYPE) {
		case ROW_TEXT: return std::string("Text");
		case ROW_NUMBER: return std::string("Number");
		case ROW_DATE_TIME: return std::string("Date/Time");
		case ROW_MEMO: return std::string("Memo");
		case ROW_YES_NO: return std::string("Yes/No");
	}
};
