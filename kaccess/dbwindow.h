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
#include <vector>

class tableDesigner;
class objButtonList;
class objListView;
class QGroupBox;
class QAction;
class QPushButton;
class QToolbar;
class QDockWindow;
class QTable;
class QListViewItem;

class dbWindow: public QMainWindow {
    Q_OBJECT
    
    public:
	dbWindow(const char *dbName, QWidget *parent=0, const char *name=0);
	
	void makeActions();
	void makeButtons();
	void makeToolbars();
	void makeObjList();
	
	void addPreOps();
	
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
	
    private:
	QDockWindow *sidePanel;
	
	QAction *openThingAct;
	QAction *newThingAct;
	QAction *designThingAct;
	
	objButtonList  *objButtons;
	std::vector<objListView*> objLists;
	
	QToolBar *mainTb;
	
	int openObject;
	std::vector<std::pair<QString, QTable*> > tables; // tables
	
	tableDesigner *newTableDesigner;
};

#endif
