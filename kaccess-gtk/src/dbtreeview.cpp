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
	tstore=/*Glib::RefPtr<Gtk::TreeStore>::RefPtr(tst*/Gtk::TreeStore::create(colRec);
	set_model(tstore);
};

// overloaded button event function for checking for double clicks on the list
bool DBTreeView::on_button_press_event(GdkEventButton *e) {
	if (e && e->type==GDK_2BUTTON_PRESS) {
		// emit the double clicked signal
		this->itemDoubleClicked();
	}
};
