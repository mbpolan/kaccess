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
// mainwindow.cpp: implementations of mainWindow class

#include <qaction.h>
#include <qapplication.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qworkspace.h>
#include <qfiledialog.h>
#include <qmessagebox.h>

#include "dbwindow.h"
#include "dialogs.h"
#include "mainwindow.h"

// our main window constructor
mainWindow::mainWindow(QWidget *parent, const char *name): QMainWindow(parent, name) {
    makeActions();
    makeMenus();
    makeToolbars();
    
    workspace=new QWorkspace(this);
    this->setCentralWidget(workspace);
};

// create the actions used through the program
void mainWindow::makeActions() {
    newDbAct=new QAction(tr("New database"), tr("Ctrl+N"), this);
    newDbAct->setStatusTip("Create a new database");
    connect(newDbAct, SIGNAL(activated()), this, SLOT(slotNewDb()));
    
    openDbAct=new QAction(tr("Open database"), tr("Ctrl+O"), this);
    openDbAct->setStatusTip("Open a database");
    connect(openDbAct, SIGNAL(activated()), this, SLOT(slotOpenDb()));
    
    saveDbAct=new QAction(tr("Save database"), tr("Ctrl+S"), this);
    saveDbAct->setStatusTip("Save this database");
    connect(saveDbAct, SIGNAL(activated()), this, SLOT(slotSaveDb()));
    
    saveDbAsAct=new QAction(tr("Save As"), tr("Alt+S"), this);
    saveDbAct->setStatusTip("Save this database as another file");
    connect(saveDbAsAct, SIGNAL(activated()), this, SLOT(slotSaveDbAs()));
    
    exitAct=new QAction(tr("Exit"), tr("Ctrl+Q"), this);
    exitAct->setStatusTip("Exit KAccess");
    connect(exitAct, SIGNAL(activated()), qApp, SLOT(quit()));
    
    aboutKAccessAct=new QAction(tr("About KAccess"), tr("Alt+A"), this);
    aboutKAccessAct->setStatusTip("About KAccess");
    connect(aboutKAccessAct, SIGNAL(activated()), SLOT(aboutKAccess()));
    
    aboutQtAct=new QAction(tr("About Qt"), tr("Alt+Q"), this);
    aboutQtAct->setStatusTip("About the Qt library");
    connect(aboutQtAct, SIGNAL(activated()), qApp, SLOT(aboutQt()));
    
    return;
};

// create menus
void mainWindow::makeMenus() {
    fileMenu=new QPopupMenu(this);
    newDbAct->addTo(fileMenu);
    openDbAct->addTo(fileMenu);
    saveDbAct->addTo(fileMenu);
    saveDbAsAct->addTo(fileMenu);
    
    fileMenu->insertSeparator();
    exitAct->addTo(fileMenu);
    
    helpMenu=new QPopupMenu(this);
    aboutQtAct->addTo(helpMenu);
    helpMenu->insertSeparator();
    
    aboutKAccessAct->addTo(helpMenu);
    
    menuBar()->insertItem("&File", fileMenu);
    menuBar()->insertItem("&Help", helpMenu);
};

// create toolbars
void mainWindow::makeToolbars() {
    return;
};

// slot for making a new database
// TODO: close all open databases prior to opening a new one
void mainWindow::slotNewDb() {
    QString f=QFileDialog::getSaveFileName("/home/mike", "KAccess Databases (*kdb)", this, "open file dialog", "Save Database" );
    
    saveDialog sd("New Database", "Enter a name for this database", this);
    sd.show();
    sd.raise();
    sd.setActiveWindow();
    
    // the user accepted to create this database
    if (sd.exec() && sd.getText()!=QString::null) {
	dbWindow *newDb=new dbWindow(sd.getText(), workspace);
	newDb->show();
    }
};

// slot to open a database
void mainWindow::slotOpenDb() {
    return;
};

// slot to save a database
void mainWindow::slotSaveDb() {
    return;
};

// slot to save a database as another file
void mainWindow::slotSaveDbAs() {
    return;
};

// slot to display a message about KAccess
void mainWindow::aboutKAccess() {
    aboutKAccessDialog akDialog;
    
    akDialog.show();
    akDialog.raise();
    akDialog.setActiveWindow();
    
    akDialog.exec();
};
