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
 
#ifndef DESIGNERTREEVIEW_H
#define DESIGNERTREEVIEW_H

#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>

/** The TableDesigner's derived tree view.
  * DesignerTreeView is a derived class from Gtk::TreeView with three initial columns.
  * This class is used as a member of the TableDesigner class to provide better 
  * functionality than that of the Gtk::TreeView.
*/
class DesignerTreeView: public Gtk::TreeView {
	public:
		/// Constructor
		/** Creates an empty instance of DesignerTreeView
		  * \param makeDefaults Controls whether or not to make the three initial columns
		*/
		DesignerTreeView(bool makeDefaults=true);
		
		/// Destructor
		virtual ~DesignerTreeView();
		
		/// The model used for this view
		Glib::RefPtr<Gtk::TreeStore> tstore;
		
	private:
		/// The column record containing three columns appropriate for this class
		class DesignerTreeViewColumnRecord: public Gtk::TreeModel::ColumnRecord {
			public:
				DesignerTreeViewColumnRecord() {
					add(generic);
					add(fieldName);
					add(fieldType);
					add(fieldDescription);
				};
				
				// columns
				Gtk::TreeModelColumn<Glib::ustring> generic;
				Gtk::TreeModelColumn<Glib::ustring> fieldName;
				Gtk::TreeModelColumn<Glib::ustring> fieldType;
				Gtk::TreeModelColumn<Glib::ustring> fieldDescription;
		};
		
		// signal handlers
		void onCellEdited(const Glib::ustring &path, const Glib::ustring &text);
		
	public:
		/// The column record for this tree view
		DesignerTreeViewColumnRecord colRec;
};

#endif
