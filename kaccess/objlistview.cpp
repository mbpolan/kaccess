/***************************************************************************
 *   Copyright (C) 2005 by the KAccess Team                                       *
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
// objlistview.cpp: implementations of objListView class and others
#include <iostream>
#include "objlistview.h"

// objListView constructor: takes 2 parameters.
objListView::objListView(QWidget *parent, const char *name): QListView(parent, name) {
};

// method to sort the items in the list making sure actions are listed first. 
void objListView::sortByPriority() {
};

/****************************************************************************
  * End of objListView implementations; start objListViewItem implementations...
  ***************************************************************************/

objListViewItem::objListViewItem(bool actItem, objListView *parent, QString label): 
	QListViewItem(parent, label, QString::null, QString::null, QString::null, QString::null, QString::null,
		    QString::null, QString::null) {
    
    isAction=actItem;
};

// objListView constructor: takes 1 parameter
objListViewItem::objListViewItem(bool actItem, objListViewItem *parent, QString label): 
	QListViewItem(parent, label) {
    isAction=actItem;
};