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

#include <list>
#include <qgroupbox.h>
#include <qlistview.h>
#include <qaction.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qdockwindow.h>
#include <iostream>
#include <qmessagebox.h>
#include <qtoolbar.h>
#include <qtable.h>
#include <qworkspace.h>

#include "dialogs.h"
#include "widgets.h"
#include "dbwindow.h"
#include "objlistview.h"
#include "tabledesigner.h"
#include "tableeditor.h"
#include "tablemodel.h"

// graphics
#include "icons/design_form.xpm"
#include "icons/design_report.xpm"
#include "icons/design_table.xpm"
#include "icons/new_form.xpm"
#include "icons/new_report.xpm"
#include "icons/new_table.xpm"
#include "icons/open_generic.xpm"

// the database overview window inside the workspace
dbWindow::dbWindow(const char *dbName, QWidget *parent, const char *name): QMainWindow(parent, name, WDestructiveClose) {
    // set the title 
    QString dbTitle="Database: ";
    dbTitle+=dbName;
    setCaption(dbTitle);
    
    setMinimumSize(400, 300);
    openObject=0;
    
    makePixmaps();
    makeActions();
    makeToolbars();
    
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
    
    // connections
    connect(objLists[0], SIGNAL(sigRemoveTable(QString)), SLOT(removeTable(QString)));
    
    // add some options
    this->addPreOps();
    
    setCentralWidget(objLists[0]);
    
    moveDockWindow(mainTb, Qt::Top);
    moveDockWindow(sidePanel, Qt::Left);
    
    newTableDesigner=new tableDesigner(this);
    connect(newTableDesigner, SIGNAL(tdSaveButtonClicked(QString)), SLOT(saveTable(QString)));
};

// create pixmaps
void dbWindow::makePixmaps() {
    // generate pixmaps
    QPixmap gfx_design_form=QPixmap((const char**) design_form_xpm);
    QPixmap gfx_design_report=QPixmap((const char**) design_report_xpm);
    QPixmap gfx_design_table=QPixmap((const char**) design_table_xpm);
    QPixmap gfx_new_form=QPixmap((const char**) new_form_xpm);
    QPixmap gfx_new_report=QPixmap((const char**) new_report_xpm);
    QPixmap gfx_new_table=QPixmap((const char**) new_table_xpm);
    QPixmap gfx_open_generic=QPixmap((const char**) open_generic_xpm);
    
    // and add them to th vector
    gfx.push_back(gfx_design_form);
    gfx.push_back(gfx_design_report);
    gfx.push_back(gfx_design_table);
    gfx.push_back(gfx_new_form);
    gfx.push_back(gfx_new_report);
    gfx.push_back(gfx_new_table);
    gfx.push_back(gfx_open_generic);
};

// create the various actions
void dbWindow::makeActions() {
    openThingAct=new QAction(tr("Open"), tr(""), this);
    openThingAct->setIconSet(gfx[GFX_OPEN_GENERIC]);
    connect(openThingAct, SIGNAL(activated()), this, SLOT(openSelected()));
    
    designThingAct=new QAction(tr("Design"), tr(""), this);
    designThingAct->setIconSet(gfx[GFX_DESIGN_TABLE]);
    connect(designThingAct, SIGNAL(activated()), this, SLOT(designSelected()));
    
    newThingAct=new QAction(tr("New"), tr(""), this);
    newThingAct->setIconSet(gfx[GFX_NEW_TABLE]); // tables are displayed by default
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

// return a pointer to a QTable in the table list
QTable* dbWindow::table(int pos) {
    int counter=0;
    for (tableIterator it=tables.begin(); it != tables.end(); ++it) {
	if (counter==pos && (*it).first && (*it).second)
	    return (*it).second->getTable();
	else
	    ++counter;
    }
    
    // table not found
    return NULL;
};

// method to get a name of a table
QString dbWindow::tableName(int pos) {
    int counter=0;
    for (tableIterator it=tables.begin(); it != tables.end(); ++it) {
	if (counter==pos && (*it).first && (*it).second)
	    return (*it).second->getName();
	else
	    ++counter;
    }
    
    // table not found
    return QString::null;
};

// slot to open the table designer
void dbWindow::openTableDesigner() {
    newTableDesigner->show();
    newTableDesigner->raise();
    newTableDesigner->setActiveWindow();
    
    return;
};

// slot to open the form designer
void dbWindow::openFormDesigner() {
    return;
};

// slot to open the report wizard
void dbWindow::openReportWizard() {
    return;
};

// function to open a table
void dbWindow::openTable(QListViewItem *item) {
    tableEditor *te;
    for (tableIterator it=tables.begin(); it != tables.end(); ++it) {
	// found the correct tables
	if (((*it).first && (*it).second) && (*it).first->name==item->text(0)) {
	    te=(*it).second;
	    break;
	}
    }
    
    // found the table
    if (te)
	te->show();
    
    return;
};

void dbWindow::openForm(QListViewItem *item) {
    return;
}

void dbWindow::openReport(QListViewItem *item) {
}

// method to add an object to the lists
void dbWindow::addTableObj(tableModel *tm, tableEditor *te) {
    QString name=tm->name;
    std::pair<tableModel*, tableEditor*> p(tm, te);
    tables.push_back(p);
    
    // now add it to the list view
    objListViewItem *objItem=new objListViewItem(false, dynamic_cast<objListViewItem*> (objLists[OBJLIST_TABLE]->firstChild()), name);
};

// slot for making a new object
void dbWindow::newSelected() {
    switch(openObject) {
                    case 0: openTableDesigner(); break;
	    case 1: openFormDesigner(); break;
	    case 2: openReportWizard(); break;
    }
    
    return;
};

// slot for designing a new object
void dbWindow::designSelected() {
    switch(openObject) {
	    case 0: openTableDesigner(); break;
	    case 1: openFormDesigner(); break;
	    //case 2: openReportDesigner(); break; // TODO: report designer
    }
    
    return;
};

// slot for opening the selected thing
void dbWindow::openSelected() {
    objListViewItem *item=dynamic_cast<objListViewItem*> (objLists[openObject]->selectedItem());
    if (!item)
	return;
    
    switch(openObject) {
	    case 0: {
		    if (item->isActionItem())
			openTableDesigner();
		    else
			openTable((QListViewItem*) item);
	    }
	    break;
		    
	    case 1: {
		    if (item->isActionItem())
			openFormDesigner();
			
		    else
			openForm((QListViewItem*) item);
	    }
	    break;
	    
	    case 2: {
		    if (item->isActionItem())
			openReportWizard();
			
		    else
			openReport((QListViewItem*) item); break;
	    }
	    break;
    }
		    
    return;
};

// slot to parse a button's id
void dbWindow::viewObject(int id) {
    objLists[openObject]->hide();

    // switch the list view first
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
    
    // change toolbar graphics
    newThingAct->setIconSet(gfx[GFX_NEW_TABLE]);
    designThingAct->setIconSet(gfx[GFX_DESIGN_TABLE]);
    
    return;
};

// slot to change the view to forms
void dbWindow::viewForms() {
    setCentralWidget(objLists[1]);
    objLists[1]->show();
    
    // change toolbar graphics
    newThingAct->setIconSet(gfx[GFX_NEW_FORM]);
    designThingAct->setIconSet(gfx[GFX_DESIGN_FORM]);
    
    return;
};

// slot to change the view to reports
void dbWindow::viewReports() {
    setCentralWidget(objLists[2]);
    objLists[2]->show();
    
    // change toolbar graphics
    newThingAct->setIconSet(gfx[GFX_NEW_REPORT]);
    designThingAct->setIconSet(gfx[GFX_DESIGN_REPORT]);
    
    return;
};

// save the table stored in the designer
void dbWindow::saveTable(QString tableName) {
    QTable *t=newTableDesigner->getTable();
    tableModel *tm=new tableModel;
    std::vector<int> activeRows;
    
    // get a count of rows that have data in them
    for (int i=0; i < t->numRows(); i++) {
	// we always check the cells in first column because if there's text there, then
	// the row is considered to be a new entry
	if (t->item(i, 0) && t->item(i, 0)->text()!=QString::null) {
	    activeRows.push_back(i);
	}
    }
    
    // set the columns
    tm->setCols(activeRows.size());
    
    // save the columns
   QTableItem *item;
    for (int i=0; i<activeRows.size(); i++) {
	item=t->item(activeRows[i], 0); // column name
	QString name=item->text();
	
	QComboTableItem *c_item=dynamic_cast<QComboTableItem*> (t->item(activeRows[i], 1)); // data type
	int type=c_item->currentItem();
	
	// FIXME: this causes a segfault for some reason
/*	item=t->item(activeRows[i], 2); // description
	QString description=item->text();*/
	QString description="...";
	
	tm->addColumn(name, type, description);
    }
    tm->name=tableName;
    
    // add it to the list
    objListViewItem *objItem=new objListViewItem(false, dynamic_cast<objListViewItem*> (objLists[0]->firstChild()), tableName);
    objLists[0]->ensureItemVisible(objItem);
    
    // assign an editor to this table
    tableEditor *ed=new tableEditor(tm, this);
    ed->hide();
    
    // and to the vector of tables
    std::pair<tableModel*, tableEditor*> p(tm, ed);
    tables.push_back(p);

};

// slot to remove a table from the vector
void dbWindow::removeTable(QString name) {
    tableIterator it=tables.begin();
    while(it != tables.end()) {
	// found table
	if (((*it).first && (*it).second) && (*it).first->name==name) {
	    it=tables.erase(it);
	    break;
	}
	
	else
	    ++it;
    }
};
