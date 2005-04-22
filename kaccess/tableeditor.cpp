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
// tableeditor.cpp: implementations of the tableEditor class

#include <qlayout.h>

#include "tableeditor.h"

// tableEditor constructor
tableEditor::tableEditor(tableModel *rootTable, QWidget *parent, const char *name): 
	QMainWindow(parent, name) {
    
    // caption: Table: NAME
    QString tName="Table: ";
    if (rootTable)
	tName+=rootTable->name;
    else
	tName+="Table";
    setCaption(tName);
    
    editorWidget=new tableEditorWidget(rootTable, this);
    setCentralWidget(editorWidget);
    
};

// method to set a table
void tableEditor::setTable(QTable *tb) {
    editorWidget->setTable(tb);
};
    
// method to get a table
QTable* tableEditor::getTable() const {
    return editorWidget->getTable();
};

/*************************************************************************
  * start tableEditorWidget implementations				 *
  ************************************************************************/

tableEditorWidget::tableEditorWidget(tableModel *rootTable, QWidget *parent, const char *name):
	QWidget(parent, name) {
    
    grid=new QGridLayout(this, 1, 1);
    setMinimumSize(800, 600);
    QTable *nTable=rootTable->toQTable(this);
//    QTable *nTable=new QTable(2, 1, this);
    
    if (nTable) {
	table=nTable;
	setCaption("Table: Table"); // TODO: table naming
    }
    
    // this shouldn't happen, but just in case it does, we'll allocate memory for a dummy table
    else {
	table=new QTable(2, 1, this);
	setCaption("Table: Table");
    }
    
    // add the table to the grid layout
    grid->addWidget(table, 0, 0);
};
