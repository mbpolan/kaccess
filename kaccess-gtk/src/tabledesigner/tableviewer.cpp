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
// tableviewer.cpp: implementations of TableViewer class

#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/stock.h>
#include "cellrendererdatetime.h"
#include "cellrenderernumeric.h"
#include "tableviewer.h"

// constructor
TableViewer::TableViewer(TableModel *tmodel): Gtk::Window(), model(tmodel) {
	std::string title="Viewing Table: ";
	title+=tmodel->getName();
	
	// set the title
	set_title(title);
	set_size_request(365, 290);
	
	// set up action group and ui manager
	actionGroup=Gtk::ActionGroup::create();
	
	// add actions
	actionGroup->add(Gtk::Action::create("ToolInsert", Gtk::Stock::ADD, "Add Records", "Added more records"),
			sigc::mem_fun(*this, &TableViewer::addRecords));
		
	// create the ui manager
	uiManager=Gtk::UIManager::create();
	uiManager->insert_action_group(actionGroup);
	
	try {
		// create a ui from a string
		Glib::ustring buffer=
		"<ui>"
		"	<toolbar name='MainToolbar'>"
		"		<toolitem action='ToolInsert'/>"
		"	</toolbar>"
		"</ui>";
		
		uiManager->add_ui_from_string(buffer);
	}
	
	// catch exceptions
	catch (const Glib::Error &e) {
		std::cout << "Unable to make menus: " << e.what() << std::endl;
	}
	
	// add the column models
	for (int i=0; i<model->size(); i++) {
		// add the appropriate column type
		ROW_TYPE _TYPE=model->getRow(i).getData()->getRowType();
		
		// check the type
		switch(_TYPE) {
			default:
			case ROW_TEXT: {
				Gtk::TreeModelColumn<Glib::ustring> col;
				colRec.add(col);
				colRec.stringVec.push_back(col);
			};
			break;
			
			case ROW_YES_NO: {
				Gtk::TreeModelColumn<bool> col;
				colRec.add(col);
				colRec.boolVec.push_back(col);
			};
			break;
		}
	}
	
	// create the liststore
	lstore=Gtk::ListStore::create(colRec);
	
	// create the tree view
	tview=new Gtk::TreeView(lstore);
	
	// create the table based on the model
	TableModel::Row row;
	int b=0, s=0;
	for (int i=0; i<model->size(); i++) {
		row=model->getRow(i);
		
		// get the header
		std::string header=row.getName();
		
		// get the type
		ROW_TYPE _TYPE=row.getData()->getRowType();
		
		// append the proper column
		int cols;
		switch(_TYPE) {
			// all others
			default:
			
			// text
			case ROW_TEXT: {
				cols=tview->append_column_editable(header, colRec.stringVec[s]); 
				s+=1;
			};
			break;
			
			// number
			case ROW_NUMBER: {
				CellRendererNumeric *renderer=new CellRendererNumeric(s);
				renderer->property_editable()=true;
				
				// append a new column
				cols=tview->append_column(header, *manage(renderer));
				Gtk::TreeViewColumn *pCol=tview->get_column(cols-1);
				
				if (pCol) {
					pCol->add_attribute(renderer->property_text(), colRec.stringVec[s]);
					renderer->sigEdited().connect(sigc::mem_fun(*this, &TableViewer::onStringCellEdited));
				}
				
				s+=1;
			};
			break;
			
			// date/time
			case ROW_DATE_TIME: {
				CellRendererDateTime *renderer=new CellRendererDateTime(s);
				renderer->property_editable()=true;
				
				// append a new column
				cols=tview->append_column(header, *manage(renderer));
				Gtk::TreeViewColumn *pCol=tview->get_column(cols-1);
				
				if (pCol) {
					pCol->add_attribute(renderer->property_text(), colRec.stringVec[s]);
					renderer->sigEdited().connect(sigc::mem_fun(*this, &TableViewer::onStringCellEdited));
				}
				
				s+=1;
			};
			break;
			
			// yes/no row
			case ROW_YES_NO: {
				cols=tview->append_column_editable(header, colRec.boolVec[b]);
				b+=1;
			};
			break;
		}
		
		// check if this row is the primary key
		int pkey=model->getPKeyRow();
		if (pkey==i) {
			// make the renderer color the background light blue for this column
			Gtk::CellRenderer *renderer=tview->get_column_cell_renderer(cols-1);
			if (renderer)
				renderer->property_cell_background()="LightBlue";
		}
		
		// TODO: apply the description
		//descriptions.push_back(row.getDescription());
	}
	
	// build the interface
	vbox=new Gtk::VBox;
	vbox->set_spacing(3);
	
	// toolbar
	Gtk::Widget *tbar=uiManager->get_widget("/MainToolbar");
	
	// status bar
	statsbar=new Gtk::Statusbar;
	statsbar->push("Viewing table");
	
	// pack the widgets
	if (tbar)
		vbox->pack_start(*manage(tbar), Gtk::PACK_SHRINK);
	vbox->pack_start(*manage(tview));
	vbox->pack_start(*manage(statsbar), Gtk::PACK_SHRINK);
	
	add(*manage(vbox));
	show_all_children();
};

// signal handler to add records
void TableViewer::addRecords() {
	Gtk::Dialog d("Add Records", *this, true, true);
	
	// format the dialog
	Gtk::VBox *vb=d.get_vbox();
	
	// spin button
	Gtk::SpinButton *sb=new Gtk::SpinButton;
	Gtk::Adjustment adj(1, 1, 50);
	sb->configure(adj, 1, 0);
	
	// pack widgets
	vb->pack_start(*manage(new Gtk::Label("Enter the amount of records to add.")), Gtk::PACK_SHRINK);
	vb->pack_start(*manage(sb), Gtk::PACK_SHRINK);
	
	// add buttons
	d.add_button("OK", 0x00);
	d.add_button("Cancel", 0x01);
	
	// run the dialog
	d.show_all_children();
	
	if (d.run()==0x00) {
		double value=sb->get_value();
		
		// add the requested amount of rows
		for (int i=0; i<value; i++)
			lstore->append();
	}
	
	return;
};

// signal handler to place text in a cell
void TableViewer::onStringCellEdited(const Glib::ustring &path, const Glib::ustring &text, int col) {
	Gtk::TreeModel::Row row=*(lstore->get_iter(Gtk::TreeModel::Path(path)));
	
	// set the text
	row[colRec.stringVec[col]]=text;
};
