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
// tableviewer.h: the TableViewer class

#ifndef TABLEVIEWER_H
#define TABLEVIEWER_H

#include <gtkmm/actiongroup.h>
#include <gtkmm/box.h>
#include <gtkmm/liststore.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/tooltips.h>
#include <gtkmm/treeview.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/window.h>
#include <vector>
#include "tablemodel.h" 

class TableViewer: public Gtk::Window {
	public:
		TableViewer(TableModel *tmodel);
		virtual ~TableViewer() {};
		
		void setModel(TableModel *tmodel) { model=tmodel; };
		TableModel* getModel() const { return model; };
		void clear();
		
	protected:
		// signal handlers
		void addRecords();
		void onStringCellEdited(const Glib::ustring &path, const Glib::ustring &path, int col);
		
		// widgets
		Gtk::VBox *vbox;
		Gtk::Statusbar *statsbar;
		Gtk::Toolbar *toolbar;
		
		// this class's column record
		class ColumnRecord: public Gtk::TreeModel::ColumnRecord {
			public:
				ColumnRecord() {
				};
				
				std::vector<Gtk::TreeModelColumn<Glib::ustring> > stringVec;
				std::vector<Gtk::TreeModelColumn<bool> > boolVec;
		};
		
		TableModel *model;
		
		// tree view related
		Gtk::TreeView *tview;
		Glib::RefPtr<Gtk::ListStore> lstore;
		
		// action group and ui manager
		Glib::RefPtr<Gtk::ActionGroup> actionGroup;
		Glib::RefPtr<Gtk::UIManager> uiManager;
	
	public:
		ColumnRecord colRec;
};

#endif
