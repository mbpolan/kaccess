/***************************************************************************
 *   Copyright (C) 2006 by The KAccess Team                                *
 *   http://kaccess.sf.net                                                 *
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
// mainwindow.cpp: implementations of MainWindow class

#include <QInputDialog>
#include <QMessageBox>
#include <QWorkspace>

#include "dbwindow.h"
#include "mainwindow.h"

// constructor
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags): QMainWindow(parent, flags) {
	setWindowTitle("KAccess");
	construct();
};

// new database action handler
void MainWindow::onNewDB() {
	if (m_DBWindow->active() && m_DBWindow->modified()) {
		// TODO: save current database
	}
	
	else {
		// get input for name
		QString str;
		do {
			bool ok;
			str=QInputDialog::getText(this, "Name", "Database Name", QLineEdit::Normal, "", &ok);
			
			// check length
			if (str.isEmpty() && ok) {
				QMessageBox::critical(this, "Name Error", "The name must be at least 1 character long!", 
							QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
				continue;
			}
			
			else if (ok)
				break;
			
			else
				return;
		}
		while(1);
		
		// clear the database
		m_DBWindow->clear();
		
		// set the name
		m_DBWindow->setName(str);
		m_DBWindow->setActive(true);
		
		// reshow the window
		m_DBWindow->show();
	}
};

// open database action handler
void MainWindow::onOpenDB() {
};

// save database action handler
void MainWindow::onSaveDB() {
};

// save database as action handler
void MainWindow::onSaveDBAs() {
};

// close database action handler
void MainWindow::onCloseDB() {
	if (m_DBWindow->active() && m_DBWindow->modified()) {
		// TODO: ask if to save
	}
	
	// clear and hide
	m_DBWindow->clear();
	m_DBWindow->hide();
};

// quit action handler
void MainWindow::onQuit() {
};

// about kaccess handler
void MainWindow::onAboutKAccess() {
	m_AboutDialog->exec();
};

// build the ui
void MainWindow::construct() {
	// create the workspace widget
	m_Workspace=new QWorkspace(this);
	
	// set the workspace as the central widget
	setCentralWidget(m_Workspace);
	
	// create actions
	buildActions();
	
	// create menubar
	buildMenubar();
	
	// create the status bar
	buildStatusBar();
	
	// create the AboutDialog
	m_AboutDialog=new AboutDialog(this);
	m_AboutDialog->setModal(true);
	
	// create the dbWindow
	m_DBWindow=new DBWindow(m_Workspace);
	
	// add the window
	m_Workspace->addWindow(m_DBWindow);
	m_DBWindow->hide();
};

// create actions
void MainWindow::buildActions() {
	// new database action
	m_NewDBAct=new QAction(QIcon(":/images/newdb.png"), tr("&New Database"), this);
	m_NewDBAct->setStatusTip(tr("Create a new database"));
	m_NewDBAct->setShortcut(tr("Ctrl+N"));
	QObject::connect(m_NewDBAct, SIGNAL(triggered()), this, SLOT(onNewDB()));
	
	// open database action
	m_OpenDBAct=new QAction(QIcon(":/images/opendb.png"), tr("&Open Database"), this);
	m_OpenDBAct->setStatusTip(tr("Open a previously saved database"));
	m_OpenDBAct->setShortcut(tr("Ctrl+O"));
	QObject::connect(m_OpenDBAct, SIGNAL(triggered()), this, SLOT(onOpenDB()));
	
	// save database action
	m_SaveDBAct=new QAction(QIcon(":/images/savedb.png"), tr("&Save Database"), this);
	m_SaveDBAct->setStatusTip(tr("Save the current database"));
	m_SaveDBAct->setShortcut(tr("Ctrl+S"));
	QObject::connect(m_SaveDBAct, SIGNAL(triggered()), this, SLOT(onSaveDB()));
	
	// save database as action
	m_SaveDBAsAct=new QAction(QIcon(":/images/savedbas.png"), tr("Save Database As..."), this);
	m_SaveDBAsAct->setStatusTip(tr("Save the current database as a new file"));
	m_SaveDBAsAct->setShortcut(tr("Shift+Ctrl+S"));
	QObject::connect(m_SaveDBAsAct, SIGNAL(triggered()), this, SLOT(onSaveDBAs()));
	
	// close database action
	m_CloseDBAct=new QAction(QIcon(":/images/closedb.png"), tr("Close Database"), this);
	m_CloseDBAct->setStatusTip(tr("Close this database"));
	m_CloseDBAct->setShortcut(tr("Ctrl+C"));
	QObject::connect(m_CloseDBAct, SIGNAL(triggered()), this, SLOT(onCloseDB()));
	
	// quit action
	m_QuitAct=new QAction(QIcon(":/images/quit.png"), tr("Quit KAccess"), this);
	m_QuitAct->setStatusTip(tr("Close the current database (if any) and quit KAccess"));
	m_QuitAct->setShortcut(tr("Ctrl+Q"));
	QObject::connect(m_QuitAct, SIGNAL(triggered()), this, SLOT(onQuit()));
	
	// about kaccess action
	m_AboutKAccessAct=new QAction(QIcon(":/images/about.png"), tr("About KAccess"), this);
	m_AboutKAccessAct->setStatusTip(tr("Information about KAccess"));
	m_AboutKAccessAct->setShortcut(tr("Shift+Ctrl+A"));
	QObject::connect(m_AboutKAccessAct, SIGNAL(triggered()), this, SLOT(onAboutKAccess()));
};

// create the menu bar
void MainWindow::buildMenubar() {
	// file menu
	QMenu *file=menuBar()->addMenu(tr("&File"));
	
	// add actions
	file->addAction(m_NewDBAct);
	file->addAction(m_OpenDBAct);
	file->addAction(m_SaveDBAct);
	file->addAction(m_SaveDBAsAct);
	file->addAction(m_CloseDBAct);
	file->addSeparator();
	file->addAction(m_QuitAct);
	
	// help menu
	QMenu *help=menuBar()->addMenu(tr("&Help"));

	// add actions
	help->addAction(m_AboutKAccessAct);
};

// create status bar
void MainWindow::buildStatusBar() {
	statusBar()->showMessage("Welcome to KAccess!");
};
