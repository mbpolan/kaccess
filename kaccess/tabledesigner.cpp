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
// tabledesigner.cpp: implementations of tableDesigner class and friends

#include <qaction.h>
#include <qlineedit.h>
#include <qtable.h>
#include <qlayout.h>
#include <qstringlist.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qtoolbar.h>
#include <sstream>

#include "dialogs.h"
#include "tabledesigner.h"
#include "widgets.h"

// tableDesigner constructor
tableDesigner::tableDesigner(QWidget *parent, const char *name): QMainWindow(parent, name) {
    setCaption("Designing table");
    setMinimumSize(800, 600);
    
    designer=new tableDesignerWidget(this);
    designer->setMinimumSize(800, 600);
    table=designer->table;
    this->setCentralWidget(designer);
    
    makeActions();
    makeToolbars();
    
    // signal connection
    connect(designer, SIGNAL(saveButtonClicked(QString)), SIGNAL(tdSaveButtonClicked(QString)));
    connect(designer, SIGNAL(saveButtonClicked(QString)), SLOT(hideAndClear()));
    connect(designer, SIGNAL(cancelButtonClicked()), SLOT(hideAndClear()));
};

// slot to clear and hide the table designer
void tableDesigner::hideAndClear() {
    designer->clear();
    this->hide();
};

// mathod to create the actions
void tableDesigner::makeActions() {
    primaryKeyAct=new QAction(tr("Primary Key"), QString::null, this);
    primaryKeyAct->setToggleAction(true);
    connect(primaryKeyAct, SIGNAL(toggled(bool)), designer, SLOT(setPrimaryKey(bool)));
};

// make toolbars
void tableDesigner::makeToolbars() {
    mainToolbar=new QToolBar(this, tr("Table"));
    primaryKeyAct->addTo(mainToolbar);
    
    moveDockWindow(mainToolbar, Qt::DockTop);
};

/**********************************************************
  * tableDesignerWidget implementations
  *********************************************************/

tableDesignerWidget::tableDesignerWidget(QWidget *parent, const char *name): 
	QWidget(parent, name) {
    
    grid=new QGridLayout(this, 3, 2);
    table=new QTable(50, 3, this);
    f_editor=new fieldDataEditor(this);
    table->setSelectionMode(QTable::NoSelection);
    
    // set a data type field
    fillDataTypeBox(data_types);

    // remove row numbering
    QHeader *h=table->verticalHeader();
    for (int i=0; i < table->numRows(); i++)
	h->setLabel(i, "");
    
    // set column labels
    h=table->horizontalHeader();
    h->setLabel(0, "Field Name");
    h->setLabel(1, "Data Type");
    h->setLabel(2, "Field Description");
    
    for (int i=0; i < table->numRows(); i++)
	table->setItem(i, 1, new QComboTableItem(table, data_types, false));
    
    grid->addMultiCellWidget(table, 0, 0, 0, 1/*, Qt::AlignCenter*/);
    
    grid->addWidget(f_editor, 1, 0);
    
    msgLabel=new QLabel("<font color=blue>Here you create or edit tables in this database.</font>", this);
    grid->addWidget(msgLabel, 1, 1, Qt::AlignCenter);
    
    // make the buttons
    saveTableButton=new QPushButton("Save Table", this);
    cancelButton=new QPushButton("Cancel", this);
    connect(saveTableButton, SIGNAL(clicked()), SLOT(broadcastSaveButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), SIGNAL(cancelButtonClicked()));
    
    grid->addWidget(saveTableButton, 2, 0);
    grid->addWidget(cancelButton, 2, 1);
    
    // stretch factors
    grid->setRowStretch(0, 10);
    grid->setRowStretch(1, 5);
    grid->setRowStretch(2, 3);
    
    grid->setColStretch(0, 7);
    grid->setColStretch(1, 3);
    
    // resize the rows of the table
    table->setColumnWidth(2, ((table->width()-(table->columnWidth(0)+table->columnWidth(1)))));
    
    // for updating the data table's description based on cell
    connect(table, SIGNAL(clicked(int, int, int, const QPoint&)), this, SLOT(updateCellDescription(int, int)));
};

// fill a table combo box with data types
void tableDesignerWidget::fillDataTypeBox(QStringList &box) {
    box+="Text"; 
    box+="Number";
    box+="Memo";
    box+="Number";
    box+="Date/Time";
    box+="Yes/No";
};

// method to clear the table
void tableDesignerWidget::clear() {
    for (int i=0; i<table->numRows(); i++) {
	for (int j=0; j<table->numCols(); j++) {
	    if (j!=1)
		table->clearCell(i, j);
	}
    }
};

// slot to update a field description. (we skip the button and QPoint parameters)
void tableDesignerWidget::updateCellDescription(int row, int col) {
    switch(col) {
	case 0x00: msgLabel->setText("<font color=blue>"
				     "This is the name of the field that will appear as a new column in your table."
				     "</font>"); break;
	    
	case 0x01: msgLabel->setText("<font color=blue>What kind of data should this field store is set here.</font>"); break;
	    
	case 0x02: msgLabel->setText("<font color=blue>Enter a description of this field to help you remeber its " 
				     "purpose later."); break;
    }
    
    return;
};

// slot to emit a signal containing the name of the table
void tableDesignerWidget::broadcastSaveButtonClicked() {    
    saveDialog sd;
    
    sd.show();
    sd.raise();
    sd.setActiveWindow();
    
    if (sd.exec()) {
	QString name=sd.getText();
	if (name!=QString::null)
	    emit saveButtonClicked(name);
    }
};

// slot to set a primary key
// TODO: still gotta debug this and make sure it works
void tableDesignerWidget::setPrimaryKey(bool set) {
/*
    // set a new key
    if (set) {
	saveDialog sd("Key", "Enter row number to be set as a primary key", this);
	sd.show();
	sd.raise();
	sd.setActiveWindow();
	
	if (sd.exec()) {
	    int row=atoi(sd.getText().ascii());
	    
	    // make sure the row is valid
	    if (row-1 <=table->numRows() && row-1 >=0) {
		QHeader *h=table->verticalHeader();
		h->setLabel(row-1, "*P*");
		primaryKey=row-1;
		hasPrimaryKey=true;
	    }
	}
    }
    
    // unset a key
    else {
	std::stringstream ss;
	ss << primaryKey;
	
	QHeader *h=table->verticalHeader();
	h->setLabel(primaryKey, ss.str().c_str());
	primaryKey=-1;
	hasPrimaryKey=false;
    }
    */
};
	
