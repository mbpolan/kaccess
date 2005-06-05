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
 
#include "designertreeview.h"

// constructor
DesignerTreeView::DesignerTreeView(bool makeDefaults): Gtk::TreeView() {
	// create the model
	tstore=Glib::RefPtr<Gtk::TreeStore>::RefPtr(Gtk::TreeStore::create(colRec));
	set_model(tstore);
	
	// should we make some initial columns?
	if (makeDefaults) {
		append_column("", colRec.generic);
		append_column_editable("Name", colRec.fieldName);
		append_column("Type", colRec.fieldType);
		append_column_editable("Description", colRec.fieldDescription);
		
		// enable the headers to be clicked
		set_headers_clickable(true);
		
		// set the columns to be resizable by the end user
		get_column(1)->set_resizable();
		get_column(2)->set_resizable();
		get_column(3)->set_resizable();
		
		// other attributes
		get_column(0)->set_clickable(false);
		get_column(0)->set_fixed_width(20);
		get_column(0)->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
		
		// add 50 rows
		for (int i=0; i<50; i++)
			tstore->append();
	}
};

// destructor
DesignerTreeView::~DesignerTreeView() {
};
