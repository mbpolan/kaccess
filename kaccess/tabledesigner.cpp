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

#include <qlineedit.h>
#include <qtable.h>
#include <qlayout.h>
#include <qstringlist.h>
#include <qlabel.h>

#include "tabledesigner.h"
#include "widgets.h"

tableDesigner::tableDesigner(QWidget *parent, const char *name): QDialog(parent, name) {
    setCaption("Designing table");
    setMinimumSize(800, 600);
    
    designer=new tableDesignerWidget(this);
    designer->setMinimumSize(800, 600);
};

/**********************************************************
  * tableDesignerWidget implementations
  *********************************************************/

tableDesignerWidget::tableDesignerWidget(QWidget *parent, const char *name): QWidget(parent, name) {
    grid=new QGridLayout(this, 3, 2);
    table=new QTable(50, 3, this);
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
    
    msgLabel=new QLabel("<font color=blue>Here you create or edit tables in this database.</font>", this);
    grid->addWidget(msgLabel, 1, 1, Qt::AlignCenter);
    
    grid->setRowStretch(0, 10);
    grid->setRowStretch(1, 5);
    grid->setRowStretch(2, 3);
    
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
