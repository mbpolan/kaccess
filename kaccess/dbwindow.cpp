/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
 *   kanadakid@gmail.com                                                   *
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

#include <qgroupbox.h>
#include <qlistview.h>
#include <qaction.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qdockwindow.h>
#include <qtoolbar.h>

#include "widgets.h"
#include "dbwindow.h"

// the database overview window inside the workspace
dbWindow::dbWindow(const char *dbName, QWidget *parent, const char *name): QMainWindow(parent, name, WDestructiveClose) {
    setCaption("Database"); // TODO: database names
    setMinimumSize(400, 300);
    
    makeActions();
    
    // create the side panel
    sidePanel=new QDockWindow(this);
    sidePanel->setMovingEnabled(false);
    
    objButtons=new objButtonList(sidePanel);
    connect(objButtons->tableViewButton, SIGNAL(clicked()), this, SLOT(viewTables()));
    connect(objButtons->formViewButton, SIGNAL(clicked()), this, SLOT(viewForms()));
    connect(objButtons->reportViewButton, SIGNAL(clicked()), this, SLOT(viewReports()));
    sidePanel->setWidget(objButtons);
    
    // main listview of contents (tables, forms, etc.)
    objList=new QListView(this);
    setCentralWidget(objList);
    
    moveDockWindow(sidePanel, Qt::Left);
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
