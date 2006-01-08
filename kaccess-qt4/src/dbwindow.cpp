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
// dbwindow.cpp: implemenations of DBWindow class

#include <QGroupBox>
#include <QLayout>
#include <QListWidget>
#include <QPushButton>

#include "dbwindow.h"

// constructor
DBWindow::DBWindow(QWidget *parent): QMainWindow(parent) {
	setWindowTitle("Database");
	construct();
};

// clear the database
void DBWindow::clear() {
	m_TableView->clear();
	m_DBName="";
	m_Modified=m_Active=false;
};

// set the database name
void DBWindow::setName(const QString &name) {
	QString title="Database: ";
	title+=name;
	setWindowTitle(title);
	
	m_DBName=name;
};

// slot for clicks on the TablesButton
void DBWindow::onTablesButtonClicked() {
};

// slot for CommentButton clicks
void DBWindow::onCommentButtonClicked() {
};

// slot for DBOptsButton clicks
void DBWindow::onDBOptsButtonClicked() {
};

// build the gui
void DBWindow::construct() {
	// set some defaults
	m_DBName="Database";
	m_Modified=false;
	m_Active=false;
	
	// base group widget
	QFrame *frame=new QFrame(this);
	
	// grid layout
	QGridLayout *grid=new QGridLayout(frame);
	
	// create the group box
	m_ButtonGroup=new QGroupBox("Menu", frame);
	
	// layout for button
	QVBoxLayout *bvbox=new QVBoxLayout;
	
	// create the buttons
	m_TablesButton=new QPushButton("Tables", m_ButtonGroup);
	m_CommentButton=new QPushButton("Comment", m_ButtonGroup);
	m_DBOptsButton=new QPushButton("DB Options", m_ButtonGroup);
	
	// add the buttons
	bvbox->addWidget(m_TablesButton);
	bvbox->addWidget(m_CommentButton);
	bvbox->addWidget(m_DBOptsButton);
	
	// set the layout
	m_ButtonGroup->setLayout(bvbox);
	
	// connect signals
	QObject::connect(m_TablesButton, SIGNAL(clicked()), this, SLOT(onTablesButtonClicked()));
	QObject::connect(m_CommentButton, SIGNAL(clicked()), this, SLOT(onCommentButtonClicked()));
	QObject::connect(m_DBOptsButton, SIGNAL(clicked()), this, SLOT(onDBOptsButtonClicked()));
	
	// create list view
	m_TableView=new QListWidget(frame);
	
	// add the widgets to the layout
	grid->addWidget(m_ButtonGroup, 0, 0);
	grid->addWidget(m_TableView, 0, 1);
	
	// set central widget
	setCentralWidget(frame);
};
