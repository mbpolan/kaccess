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
#include <qaction.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>

#include "objlistview.h"

// graphics
#include "icons/remove_table.xpm"

// objListView constructor: takes 2 parameters.
objListView::objListView(QWidget *parent, const char *name): QListView(parent, name) {
    connect(this, SIGNAL(contextMenuRequested(QListViewItem*, const QPoint&, int)), 
	    SLOT(openContextMenu(QListViewItem*, const QPoint&, int)));
    
    setRootIsDecorated(true);
    makePixmaps();
    makeActions();
};

// generate the pixmaps
void objListView::makePixmaps() {
    QPixmap remove_table=QPixmap((const char**) remove_table_xpm);
    gfx.push_back(remove_table);
};

// method to make actions
void objListView::makeActions() {
    removeTableAct=new QAction(tr("Remove Table"), QString::null, this);
    removeTableAct->setIconSet(gfx[GFX_REMOVE_TABLE]);
    connect(removeTableAct, SIGNAL(activated()), SLOT(confirmRemoveTable()));
};

// method to sort the items in the list making sure actions are listed first. 
void objListView::sortByPriority() {
};

// method to check if the user really wants to remove a table
void objListView::confirmRemoveTable() {
    // confirm removal
    if (QMessageBox::question(this, "Remove", "Are you sure you want to remove this table?", 
				 tr("&Yes"), tr("&No"), QString::null, 0, 1))
	return;
    
    // seems the table needs to be removed :(
    objListViewItem *sItem=(objListViewItem*) this->selectedItem();
    emit sigRemoveTable(sItem->text(0)); // tell the parent of the change
    
    // remove the item
    delete sItem;
};

// open a context menu
void objListView::openContextMenu(QListViewItem *item, const QPoint &pos, int col) {
    QPopupMenu context(this);
    removeTableAct->addTo(&context);
    removeTableAct->setEnabled(false);
    
    // see if we can enable the remove table action. this can only be enabled if there is a objListViewItem that
    // isn't an action item, under the mouse pointer.
    if (item) {
	objListViewItem *Item=dynamic_cast<objListViewItem*> (item);
	if (Item && !Item->isActionItem())
	    removeTableAct->setEnabled(true);
    }
	
    context.exec(pos);
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
