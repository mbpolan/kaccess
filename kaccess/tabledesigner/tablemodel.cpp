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
// tablemodel.cpp: implementations of tableModel and related classes

#include <qtable.h>
#include "tablemodel.h"

// tableModel constructor
tableModel::tableModel(int r, int cols): rows(r), columns(cols) {
};

// method for adding a column to the table
void tableModel::addColumn(QString label, int dataType, QString descr) {
    std::pair<QString, columnData*> p(label, new columnData(dataType, descr, 50));
    colDatas.push_back(p);
};

// convert this model to a QTable
QTable* tableModel::toQTable(QWidget *parent) {
    QTable *nt=new QTable(rows, colDatas.size(), parent);
    QHeader *h=nt->horizontalHeader();
    
    for (int i=0; i<colDatas.size(); i++) {
	h->setLabel(i, colDatas[i].first);
    }
    
    // get rid of default row labels
    h=nt->verticalHeader();
    for (int i=0; i<rows; i++) {
	h->setLabel(i, "");
    }
    
    return nt;
};

/**************************************************************************
   * start columnData implementations
   *************************************************************************/

columnData::columnData(int data, QString descr, int size): dataType(data),  description(descr), fieldSize(size) {
    decimalPlaces=1, numberSize=256;
    allowZero=true;
    required=false;
    indexed=false;
    unicodeCompr=false;
    
    formatting="Standard";
    inputMask="NULL";
    caption="";
    defaultVal="0";
    validationText="A-Z; a-z; 0-9";
    currencyFormat="$";
};
    
    
