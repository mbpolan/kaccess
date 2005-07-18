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
 
#include <gtkmm/messagedialog.h> 
#include "cellrendererlist.h"
#include "designertreeview.h"

// constructor
DesignerTreeView::DesignerTreeView(bool makeDefaults): Gtk::TreeView(), pkeySet(false) {
	// create the model
	tstore=Glib::RefPtr<Gtk::TreeStore>::RefPtr(Gtk::TreeStore::create(colRec));
	set_model(tstore);
	
	// populate the context menu
	Gtk::Menu::MenuList mList=contextMenu.items();
	mList.push_back(Gtk::Menu_Helpers::MenuElem("_Set Primary Key",
			sigc::mem_fun(*this, &DesignerTreeView::setPrimaryKey)));
	
	mList.push_back(Gtk::Menu_Helpers::MenuElem("_Unset Primary Key",
			sigc::mem_fun(*this, &DesignerTreeView::unsetPrimaryKey)));
	
	// should we make some initial columns?
	if (makeDefaults) {
		append_column("", colRec.generic);
		append_column_editable("Name", colRec.fieldName);
		
		// type column
		CellRendererList *renderer=new CellRendererList();
		Gtk::TreeViewColumn *column=new Gtk::TreeViewColumn("Type", *Gtk::manage(renderer));
 		
		// apend it
		append_column(*Gtk::manage(column));
		
		// add an attribute for column record
		column->add_attribute(renderer->property_text(), colRec.fieldType);

		renderer->append_list_item("Text");
		renderer->append_list_item("Number");
		renderer->append_list_item("Date/Time");
		renderer->append_list_item("Memo");
		renderer->append_list_item("Yes/No");
		
		renderer->property_editable()=true;
		renderer->signal_edited().connect(sigc::mem_fun(*this, &DesignerTreeView::onCellEdited));
		
		append_column_editable("Description", colRec.fieldDescription);
		
		// enable the headers to be clicked
		set_headers_clickable(true);
		
		// set the columns to be resizable by the end user
		get_column(1)->set_resizable();
		get_column(2)->set_resizable();
		get_column(3)->set_resizable();
		
		// other attributes
		get_column(0)->set_clickable(false);
		
		// add 50 rows
		for (int i=0; i<50; i++)
			tstore->append();
			
		// connect column signals
		get_column(1)->signal_clicked().connect(sigc::mem_fun(*this, &DesignerTreeView::onNameColumnClicked));
		get_column(2)->signal_clicked().connect(sigc::mem_fun(*this, &DesignerTreeView::onTypeColumnClicked));
		get_column(3)->signal_clicked().connect(sigc::mem_fun(*this, &DesignerTreeView::onDescColumnClicked));
	}
};

// destructor
DesignerTreeView::~DesignerTreeView() {
};

// set the primary key for a row
void DesignerTreeView::setPKeyRow(int row) {
	this->pkeySet=true;
	
	// clear the generic column first
	for (Gtk::TreeModel::iterator it=tstore->children().begin(); it!=tstore->children().end(); ++it) {
		if ((*it))
			(*it)[colRec.generic]="";
	}
	
	// set the row
	int c=0;
	for (Gtk::TreeModel::iterator it=tstore->children().begin(); it!=tstore->children().end(); ++it) {
		if ((*it) && c==row) {
			(*it)[colRec.generic]="P";
			break;
		}
		c+=1;
	}
};

// check if this table is valid
bool DesignerTreeView::tableValid() {
	// check if at least the first row of the table is filled
	if (!isFirstRowValid()) {
		Gtk::MessageDialog md("The first row of the TableDesigner must be valid!", false, Gtk::MESSAGE_ERROR,
					Gtk::BUTTONS_OK, true);
		md.run();
		return false;
	}
	
	// check if a primary key is set
	if (!isPKeySet()) {
		Gtk::MessageDialog md("A primary key is not set. Should KAccess set a primary key for you?", false, Gtk::MESSAGE_QUESTION,
					Gtk::BUTTONS_YES_NO, true);
		
		// see if the user wants to auto set a primary key
		if (md.run()==(-8))
			return setAutoPrimaryKey();
		
		else
			return false;
	}
	
	else
		return true;
};

// check if the first row is valid
bool DesignerTreeView::isFirstRowValid() {
	Gtk::TreeModel::iterator it=tstore->children().begin();
	if ((*it)) {
		Glib::ustring value=(*it)[colRec.fieldName];
		return (value.size()>0);
	}
	
	else
		return false;
};

// automatically set a primary key
bool DesignerTreeView::setAutoPrimaryKey() {
	if (isFirstRowValid()) {
		Gtk::TreeModel::iterator it=tstore->children().begin();
		if (it)
			(*it)[colRec.generic]="P";
	}
};

// update the modified cell
void DesignerTreeView::onCellEdited(const Glib::ustring &path, const Glib::ustring &text) {
	Gtk::TreeModel::Row row=*(tstore->get_iter(Gtk::TreeModel::Path(path)));
	
	// validate the user's input
	if (text!="Text" && text!="Number" && text!="Date/Time" && text!="Memo" && text!="Yes/No")
		row[colRec.fieldType]="Text";
	
	else
		row[colRec.fieldType]=text;
};

// overloaded virtual key press event function
bool DesignerTreeView::on_button_press_event(GdkEventButton *b) {
	bool ret=Gtk::TreeView::on_button_press_event(b);
	
	if (b->type==GDK_BUTTON_PRESS && b->button==3)
		contextMenu.popup(b->button, b->time);
	
	return ret;
};

// function to set a row as a primary key
void DesignerTreeView::setPrimaryKey() {
	Glib::RefPtr<Gtk::TreeView::Selection> sel=get_selection();
	if (sel) {
		Gtk::TreeModel::iterator it=sel->get_selected();
		if ((*it)) {
			// reset other rows
			for (Gtk::TreeModel::iterator _it=tstore->children().begin(); _it!=tstore->children().end(); ++_it) {
				if ((*_it) && (*_it)[colRec.generic]=="P")
					(*_it)[colRec.generic]="";
			}
			
			// set the new primary key
			(*it)[colRec.generic]="P";
			pkeySet=true;
		}
	}
};

// function to remove a primary key
void DesignerTreeView::unsetPrimaryKey() {
	Glib::RefPtr<Gtk::TreeView::Selection> sel=get_selection();
	if (sel) {
		Gtk::TreeModel::iterator it=sel->get_selected();
		if (it) {
			(*it)[colRec.generic]="";
			pkeySet=false;
		}
	}
};
