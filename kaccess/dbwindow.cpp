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
// dbwindow.cpp: implementations of dbWindow class

#include <qgroupbox.h>
#include <qlistview.h>
#include <qaction.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qdockwindow.h>
#include <iostream>
#include <qtoolbar.h>
#include <qtable.h>

#include "dialogs.h"
#include "widgets.h"
#include "dbwindow.h"
#include "objlistview.h"
#include "tabledesigner.h"

// the database overview window inside the workspace
dbWindow::dbWindow(const char *dbName, QWidget *parent, const char *name): QMainWindow(parent, name, WDestructiveClose) {
    setCaption("Database"); // TODO: database names
    setMinimumSize(400, 300);
    openObject=0;
    
    makeActions();
    
    // create the side panel
    sidePanel=new QDockWindow(this);
    sidePanel->setMovingEnabled(false);
    
    objButtons=new objButtonList(sidePanel);
    connect(objButtons, SIGNAL(buttonClicked(int)), this, SLOT(viewObject(int)));
    sidePanel->setWidget(objButtons);
    
    // main listview of contents (tables, forms, etc.)
    for (int i=0; i < 3; i++) {
	objLists.push_back(new objListView(this));
	if (i==0) 
	    continue;
	else
	    objLists[i]->hide();
    }
    
    this->addPreOps();
    
    setCentralWidget(objLists[0]);
    
    moveDockWindow(sidePanel, Qt::Left);
    
    newTableDesigner=new tableDesigner(this);
    connect(newTableDesigner, SIGNAL(tdSaveButtonClicked(QString)), SLOT(saveTable(QString)));
};

// create the various actions
void dbWindow::makeActions() {
    openThingAct=new QAction(tr("Open"), tr(""), this);
    connect(openThingAct, SIGNAL(activated()), this, SLOT(openSelected()));
    
    designThingAct=new QAction(tr("Design"), tr(""), this);
    connect(designThingAct, SIGNAL(activated()), this, SLOT(designSelected()));
    
    newThingAct=new QAction(tr("New"), tr(""), this);
    connect(newThingAct, SIGNAL(activated()), this, SLOT(newSelected()));
};

// create toolbars
void dbWindow::makeToolbars() {
    mainTb=new QToolBar(this, "database");
    openThingAct->addTo(mainTb);
    designThingAct->addTo(mainTb);
    newThingAct->addTo(mainTb);
};

// set up the list views and add in some predefined options
void dbWindow::addPreOps() {
    objLists[0]->addColumn("Tables");
    objLists[0]->insertItem(new objListViewItem(true, objLists[0], "Create a table in design view"));
    connect(objLists[0], SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(parseTableItem(QListViewItem*)));
    
    objLists[1]->addColumn("Forms");
    objLists[1]->insertItem(new objListViewItem(true, objLists[1], "Create a form in design view"));
    connect(objLists[1], SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(parseFormItem(QListViewItem*)));
    
    objLists[2]->addColumn("Reports");
    objLists[2]->insertItem(new objListViewItem(true, objLists[2], "Create a report in design view"));
    connect(objLists[2], SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(parseReportItem(QListViewItem*)));
};

void dbWindow::openTableDesigner() {
    newTableDesigner->show();
    newTableDesigner->raise();
    newTableDesigner->setActiveWindow();
    
    if (newTableDesigner->exec()) {
    }
    return;
};

void dbWindow::openFormDesigner() {
    return;
};

void dbWindow::openReportWizard() {
    return;
};

// function to open a table
void dbWindow::openTable(QListViewItem *item) {
    QTable *t=tables[(dynamic_cast<objListViewItem*> (item))->itemPos()];
    return;
};

void dbWindow::openForm(QListViewItem *item) {
    return;
}

void dbWindow::openReport(QListViewItem *item) {
}

// slot for making a new object
void dbWindow::newSelected() {
    return;
};

// slot for designing a new object
void dbWindow::designSelected() {
    return;
};

// slot for opening the selected thing
void dbWindow::openSelected() {
    return;
};

// slot to parse a button's id
void dbWindow::viewObject(int id) {
    objLists[openObject]->hide();

    switch(id) {
                 default: break;
	 case 1: viewTables(); break;
	 case 2: viewForms(); break;
	 case 3: viewReports(); break;
    }
    openObject=id-1;
    
    return;
};

void dbWindow::parseTableItem(QListViewItem *item) {
// option to create a new table in design view
    if (objLists[0]->firstChild()==item)
	openTableDesigner();

    else
	openTable(item);
};

void dbWindow::parseFormItem(QListViewItem *item) {
    if (objLists[1]->firstChild()==item)
	openFormDesigner();
    
    else
	openForm(item);
};

void dbWindow::parseReportItem(QListViewItem *item) {
    if (objLists[2]->firstChild()==item)
	openReportWizard();
  
    else
	openReport(item);
};

// slot to change the view to tables
void dbWindow::viewTables() {
    setCentralWidget(objLists[0]);
    objLists[0]->show();
    return;
};

// slot to change the view to forms
void dbWindow::viewForms() {
    setCentralWidget(objLists[1]);
    objLists[1]->show();
    return;
};

// slot to change the view to reports
void dbWindow::viewReports() {
    setCentralWidget(objLists[2]);
    objLists[2]->show();
    return;
};

// save the table stored in the designer
void dbWindow::saveTable(QString tableName) {
    QTable *t=newTableDesigner->getTable();
    QTable *nt=new QTable();
    std::vector<int> activeRows;
    
    // get a count of rows that have data in them
    for (int i=0; i < t->numRows(); i++) {
	// we always check the cells in first column because if there's text there, then
	// the row is considered to be a new entry
	if (t->item(i, 0) && t->item(i, 0)->text()!=QString::null) {
	    activeRows.push_back(i);
	}
    }
    
    // set columns for new table
    nt->setNumCols(activeRows.size());
    
    // set column headings
    QHeader *h=nt->verticalHeader();
    for (int i=0; i < activeRows.size(); i++) {
	//h->setLabel(i, t->item(activeRows[i], 2)->text());
    }
    
    // add this table to the list
    tables.push_back(nt);
    
    // and add it to the list
    objListViewItem *item=new objListViewItem(false, (objListViewItem*) objLists[0]->firstChild(), tableName);
    objLists[0]->ensureItemVisible(item);
};
