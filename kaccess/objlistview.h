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
// objlistview.h: contains the objListView class and friends

#ifndef objlistview_h
#define objlistview_h

#include <qlistview.h>
#include <qpixmap.h>
#include <vector>

class QAction;
class objListViewItem;

// graphics defines
#define GFX_REMOVE_TABLE	0

// list view class for displaying tables, reports, etc.
// TODO: finish up the implementations of this class!!
class objListView: public QListView {
    Q_OBJECT
    public:
	objListView(QWidget *parent=0, const char *name=0);
	
	// methods
	void sortByPriority();
	
    private slots:
	void confirmRemoveTable();
	
	void openContextMenu(QListViewItem*, const QPoint&, int);
	
    signals:
	void sigRemoveTable(QString);
	
    private:
	QAction *removeTableAct;
	
	void makePixmaps();
	void makeActions(); // make QActions
	
	std::vector<QPixmap> gfx; // graphics
};

// item class used in the list view
class objListViewItem: public QListViewItem {
    public:
	objListViewItem(bool actItem, objListView *parent=0, QString label=QString::null);
	objListViewItem(bool actItem, objListViewItem *parent, QString label=QString::null);
	
	bool isActionItem() const {return isAction;}
	
    private:
	bool isAction;
};
    
#endif
