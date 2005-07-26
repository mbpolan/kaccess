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
// dbtreeview.cpp: implementations of DBTreeView class

#include "dbtreeview.h"

// constructor
DBTreeView::DBTreeView(): Gtk::TreeView() {
	tstore=Gtk::TreeStore::create(colRec);
	set_model(tstore);
	
	// creat the context menu
	cMenu=new Gtk::Menu;
	Gtk::Menu::MenuList &items=cMenu->items();
		
	// set up the menu
	items.push_back(Gtk::Menu_Helpers::MenuElem("_Edit Name", sigc::mem_fun(*this, &DBTreeView::onEditMenuPopup)));
	items.push_back(Gtk::Menu_Helpers::MenuElem("_Modify", sigc::mem_fun(*this, &DBTreeView::onModifyMenuPopup)));
	
	cMenu->accelerate(*this);
};

// destructor
DBTreeView::~ DBTreeView() {
	delete cMenu;
};

// overloaded button event function for checking for double clicks on the list
bool DBTreeView::on_button_press_event(GdkEventButton *e) {
	// call the parent event handler for normal function
	Gtk::TreeView::on_button_press_event(e);
	
	// double click with first mouse button event
	if (e && e->type==GDK_2BUTTON_PRESS && e->button==1) {
		// emit the double clicked signal
		this->sigItemDoubleClicked().emit();
	}
	
	// single click with right mouse button event
	else if (e && e->type==GDK_BUTTON_PRESS && e->button==3) {
		cMenu->popup(e->button, e->time);
	}
	
	return true;
};

// check if a name already exists
bool DBTreeView::exists(const Glib::ustring &name) {
	bool exists=false;
	for (Gtk::TreeModel::iterator it=tstore->children().begin(); it!=tstore->children().end(); ++it) {
		if ((*it) && (*it)[colRec.item]==name) {
			exists=true;
			break;
		}
	}
	
	return exists;
};

// signal handler for context menu
void DBTreeView::onEditMenuPopup() {
	Glib::RefPtr<Gtk::TreeView::Selection> sel=get_selection();
	if (sel) {
		Gtk::TreeModel::iterator it=sel->get_selected();
		
		if (it && (*it))
			this->sigItemRequestNameEdit().emit(it);
	}
};

// signal handler for context menu
void DBTreeView::onModifyMenuPopup() {
	Glib::RefPtr<Gtk::TreeView::Selection> sel=get_selection();
	if (sel) {
		Gtk::TreeModel::iterator it=sel->get_selected();
		
		if (it && (*it))
			this->sigItemRequestEdit().emit(it);
	}
};
