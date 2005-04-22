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
// dbwindow.h: contains dbWindow classes and friends

#ifndef dbwindow_h
#define dbwindow_h
 
#include <qmainwindow.h>
#include <qpixmap.h>
#include <vector>
#include <list>

#include "tableeditor.h"

class tableDesigner;
class tableModel;
class objButtonList;
class objListView;
class QGroupBox;
class QAction;
class QPushButton;
class QToolbar;
class QDockWindow;
class QTable;
class QListViewItem;

// typedef for tables list
typedef std::list<std::pair<tableModel*, tableEditor*> >::iterator tableIterator;

// graphic defines
#define GFX_DESIGN_FORM	0
#define GFX_DESIGN_REPORT	1
#define GFX_DESIGN_TABLE	2
#define GFX_NEW_FORM 		3
#define GFX_NEW_REPORT 	4
#define GFX_NEW_TABLE 		5
#define GFX_OPEN_GENERIC 	6

class dbWindow: public QMainWindow {
    Q_OBJECT
    
    public:
	dbWindow(const char *dbName, QWidget *parent=0, const char *name=0);
	
	void makePixmaps();
	void makeActions();
	void makeButtons();
	void makeToolbars();
	void makeObjList();
	
	void addPreOps();
	
	// table related stuff
	int tableCount() const {return tables.size();}
	QTable* table(int pos);
	
	// i/o methods for the database
	void openTableDesigner();
	void openFormDesigner();
	void openReportWizard();
	void openTable(QListViewItem*);
	void openForm(QListViewItem*);
	void openReport(QListViewItem*);
	
    public slots:
	void newSelected();
	void openSelected();
	void designSelected();
	
	void parseTableItem(QListViewItem*);
	void parseFormItem(QListViewItem*);
	void parseReportItem(QListViewItem*);
	
	void viewObject(int);
	void viewTables();
	void viewForms();
	void viewReports();
	
	void saveTable(QString);
	void removeTable(QString);
	
    private:
	QDockWindow *sidePanel;
	
	QAction *openThingAct;
	QAction *newThingAct;
	QAction *designThingAct;
	
	objButtonList  *objButtons;
	std::vector<objListView*> objLists;
	
	QToolBar *mainTb;
	
	int openObject;
	std::list<std::pair<tableModel*, tableEditor*> > tables; // tables
	
	// table designer
	tableDesigner *newTableDesigner;
	
	// graphics vector
	std::vector<QPixmap> gfx;
};

#endif
