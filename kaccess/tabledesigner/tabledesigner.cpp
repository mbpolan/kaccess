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
#include <qpixmap.h>
#include <qmessagebox.h>
#include <qtoolbar.h>
#include <sstream>

#include "dialogs.h"
#include "tabledesigner.h"
#include "tabledesigner/designertable.h"
#include "widgets.h"

// graphics
#include "icons/insert_row.xpm"
#include "icons/primary_key.xpm"

// tableDesigner constructor
tableDesigner::tableDesigner(QWidget *parent, const char *name): QMainWindow(parent, name) {
    setCaption("Designing table");
    
    designer=new tableDesignerWidget(this);
    designer->setMinimumSize(this->width(), this->height());
    table=designer->table;
    this->setCentralWidget(designer);
    
    makePixmaps();
    makeActions();
    makeToolbars();
    
    // signal connection
    connect(designer, SIGNAL(saveButtonClicked(QString)), SLOT(parseSaveTable(QString)));
    connect(designer, SIGNAL(cancelButtonClicked()), SLOT(hideAndClear()));
};

// make the pixmaps
void tableDesigner::makePixmaps() {
    QPixmap gfx_insert_row=QPixmap((const char**) insert_row_xpm);
    QPixmap gfx_primary_key=QPixmap((const char**) primary_key_xpm);
    
    gfx.push_back(gfx_insert_row);
    gfx.push_back(gfx_primary_key);
};

// slot to clear and hide the table designer
void tableDesigner::hideAndClear() {
    designer->clear();
    this->hide();
};

// mathod to create the actions
void tableDesigner::makeActions() {
    primaryKeyAct=new QAction(tr("Primary Key"), QString::null, this);
    primaryKeyAct->setIconSet(gfx[GFX_PRIMARY_KEY]);
    connect(primaryKeyAct, SIGNAL(activated()), designer, SLOT(setPrimaryKey()));
    
    insertRowAct=new QAction(tr("Insert rows"), QString::null, this);
    insertRowAct->setIconSet(gfx[GFX_INSERT_ROW]);
    connect(insertRowAct, SIGNAL(activated()), designer, SLOT(insertNewRows()));
};

// make toolbars
void tableDesigner::makeToolbars() {
    mainToolbar=new QToolBar(this, tr("Table"));
    primaryKeyAct->addTo(mainToolbar);
    insertRowAct->addTo(mainToolbar);
    
    moveDockWindow(mainToolbar, Qt::DockTop);
};

// slot to make sure the table is ready to be saved
void tableDesigner::parseSaveTable(QString name) {
    // check to see if this table is empty
    if (!designer->table->item(0, 0)) {
	QMessageBox::critical(this, "Error", "A table must have at least one complete field.");
	return;
    }
    
    // check the primary key
    else if (!designer->isPrimaryKeyActivated()) {
	QMessageBox::critical(this, "Error", "You have not set a primary key. Please set "
			      "one before saving this table.");
	return;
    }
    
    // everything seems ok
    else {
	emit tdSaveButtonClicked(name);
	hideAndClear();
    }
};

/**********************************************************
  * tableDesignerWidget implementations
  *********************************************************/

tableDesignerWidget::tableDesignerWidget(QWidget *parent, const char *name): 
	QWidget(parent, name) {
    
    // set a data type field
    fillDataTypeBox(data_types);
    
    grid=new QGridLayout(this, 3, 2);
    table=new designerTable(data_types, this);
    f_editor=new fieldDataEditor(this);
    f_editor->setEditor(FIELD_EDITOR_TEXT);
    
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
    
    // for changing the field editor, if nessesary
    connect(table, SIGNAL(currentChanged(int, int)), SLOT(parseTableChange(int, int)));
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
    std::stringstream ss;
    
    // clear all cells
    for (int i=0; i<table->numRows(); i++) {
	for (int j=0; j<table->numCols(); j++) {
	    if (j!=1)
		table->clearCell(i, j);
	}
    }
    
    // reset the variables
    hasPrimaryKey=false;
    primaryKey=(-1);
    
    // restore the original table headers
    QHeader *h=table->verticalHeader();
    for (int i=0; i < table->numRows(); i++) {
	ss << i+1;
	h->setLabel(i, ss.str().c_str());
	ss.str("");
    }
    
};

// slot to update a field description. (we skip the button and QPoint parameters)
void tableDesignerWidget::updateCellDescription(int row, int col) {
    switch(col) {
	case 0x00: msgLabel->setText("<font color=blue>"
				     "This is the name of the field that will appear as a new column in your table."
				     "</font>"); break;
	    
	case 0x01: msgLabel->setText("<font color=blue>What kind of data should this field store is set here.</font>"); break;
	    
	case 0x02: msgLabel->setText("<font color=blue>Enter a description of this field to help you remember its " 
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
void tableDesignerWidget::setPrimaryKey() {
    // set a new key
    integerInputDialog id(table->numRows(), 1, "Enter row to set as a primary key", "Primary Key",
			      this, "pkey dialog");
    id.show();
    id.raise();
    id.setActiveWindow();
	
    // accept the new value
    if (id.exec()) {
	int row=id.getValue();
	std::stringstream ss;
	    
	// make sure the row is valid
	QHeader *h=table->verticalHeader();
	if (row-1 <=table->numRows() && row-1 >=0) {
	    // already set
	    if (hasPrimaryKey) {
		// first we restore the row numbers
		for (int i=0; i<table->numRows(); i++) {
		    ss << i+1;
		    h->setLabel(i, ss.str().c_str());
		    ss.str("");
		}
		
		// now we find the row and set the label
		h->setLabel(row-1, "*P*");
	    }
	    
	    // not set yet
	    else {
		// simply set the label
		h->setLabel(row-1, "*P*");
	    }
	    
	    hasPrimaryKey=true;
	    primaryKey=row;
	}
	
	// unset a previous key
	else if (row==0) {
	    // restore the rows
	    for (int i=0; i<table->numRows(); i++) {
		ss << i+1;
		h->setLabel(i, ss.str().c_str());
		ss.str("");
	    }
	    
	    // and change variables
	    hasPrimaryKey=false;
	    primaryKey=-1;
	}
    }
};

// slot to insert a new row
void tableDesignerWidget::insertNewRows() {
    integerInputDialog id(50, 1, "How many rows should be added?", "Insert Rows", this);
    id.show();
    id.raise();
    id.setActiveWindow();
    
    // accepted to insert rows
    if (id.exec()) {
	int count=id.getValue();
	int oldCount=table->numRows(); // original amount of rows
	
	// ask the table to insert more rows
	table->insertRows(table->numRows(), count);
	
	// add a combobox to the newly inserted rows
	int start=oldCount; // start of first new row
	for (int i=0; i<count; i++) {
	    table->setItem(start, 1, new QComboTableItem(table, data_types, false));
	    start+=1;
	}
	    
    }
};

// slot to change the field editor
void tableDesignerWidget::parseTableChange(int row, int col) {
    QTableItem *item;
    
    // get the table item from column 2 so we can decide what editor should be displayed
    switch(col) {
                case 0: item=table->item(row, col+1); break;
	case 1: item=table->item(row, col); break;
	case 2: item=table->item(row, col-1); break;
    }
    
    // hopefully we got our item
    if (item) {
	QComboTableItem *citem=dynamic_cast<QComboTableItem*> (item);
	
	// check if this item can be casted to a combo table item
	if (citem) {
	    int id=citem->currentItem(); // current field type
	    
	    // and switch the editor accordingly
	    switch(id) {
	                case FIELD_EDITOR_TEXT: f_editor->setEditor(FIELD_EDITOR_TEXT); break;
		case FIELD_EDITOR_NUMBER: f_editor->setEditor(FIELD_EDITOR_NUMBER); break;
		case FIELD_EDITOR_CURRENCY: f_editor->setEditor(FIELD_EDITOR_CURRENCY); break;
		case FIELD_EDITOR_YN: f_editor->setEditor(FIELD_EDITOR_YN); break;
		case FIELD_EDITOR_MEMO: f_editor->setEditor(FIELD_EDITOR_MEMO); break;
		case FIELD_EDITOR_DATE_TIME: f_editor->setEditor(FIELD_EDITOR_DATE_TIME); break;
	    }
	}
    }
};
