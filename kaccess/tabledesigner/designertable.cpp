/***************************************************************************
 *   Copyright (C) 2005 by the KAccess Team                                *
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
// designertable.cpp: designerTable's implementations

#include "designertable.h"

// the main constructor of designerTable
designerTable::designerTable(QStringList data_types, QWidget *parent, const char *name): 
	QTable(parent, name) {
    
    // we set up a basic table first
    setNumCols(3);
    setNumRows(50);
    setSelectionMode(QTable::NoSelection);
    
    // set the header labels
    QHeader *h=horizontalHeader();
    h->setLabel(0, "Field Name");
    h->setLabel(1, "Data Type");
    h->setLabel(2, "Field Description");
    
    // change column 2 cells to be QComboBoxes
    for (int i=0; i < numRows(); i++)
	this->setItem(i, 1, new QComboTableItem(this, data_types, false));
};
