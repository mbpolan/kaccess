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

#include <gtkmm/menu.h>
#include <gtkmm/liststore.h>
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
		Glib::RefPtr<Gtk::ListStore> lstore;
		
		/// typedef'd column clicked signal
		typedef sigc::signal<void, int> colClickedSig;
		
		/// Signal emited when a column is clicked
		colClickedSig sigColumnClicked() const { return signalColumnClicked; };
		
		/// Check if the primary key is set
		bool isPKeySet() const { return pkeySet; };
		
		/// Set the row containing the primary key
		void setPKeyRow(int row);
		
		/// Check if the table is valid
		bool tableValid();
		
		/// Check if the first row is valid
		bool isFirstRowValid();
		
		/// Automatically set a primary key
		bool setAutoPrimaryKey();
		
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
		
		// overloaded virtual functions
		virtual bool on_button_press_event(GdkEventButton*);
		
		// signal handlers
		void onNameCellEdited(const Glib::ustring &path, const Glib::ustring &text);
		void onTypeCellEdited(const Glib::ustring &path, const Glib::ustring &text);
		void onDescCellEdited(const Glib::ustring &path, const Glib::ustring &text);
		
		void onNameColumnClicked() { sigColumnClicked().emit(0x0); };
		void onTypeColumnClicked() { sigColumnClicked().emit(0x1); };
		void onDescColumnClicked() { sigColumnClicked().emit(0x2); };
		void setPrimaryKey();
		void unsetPrimaryKey();
		void insertField();
		void removeField();
		
		// signal instances
		colClickedSig signalColumnClicked;
		
		// context menu
		Gtk::Menu contextMenu;
		
		// primary key boolean
		bool pkeySet;
		
	public:
		/// The column record for this tree view
		DesignerTreeViewColumnRecord colRec;
};

#endif
