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
// tablemodel.h: class that holds info about a table

#ifndef tablemodel_h
#define tablemodel_h

#include <qstring.h>
#include <vector>

class columnData;
class QTable;

// tableModel class that holds information about a table
class tableModel {
    public:
	tableModel(int rows=0, int cols=0);
	
	// various methods
	void setCols(int c) {columns=c;}
	int getCols() const {return columns;}
	
	void setRows(int r) {rows=r;}
	int getRows() const {return rows;}
	
	void addColumn(QString label, int dataType, QString description);
	std::pair<QString, columnData*> columnAt(int);
	
	QTable *toQTable(QWidget *parent); // convert to a QTable and return a pointer to it
	QString name;
	
    private:
	int rows, columns;
	std::vector<std::pair<QString, columnData*> > colDatas;
};

// class that stores information about a field
class columnData {
    public:
	columnData(int data, QString descr, int size=256);
	
	int dataType;
	QString description;
	int fieldSize;
	int decimalPlaces, numberSize;
	bool allowZero, required, indexed, unicodeCompr;
	
	QString formatting, inputMask, caption, defaultVal, validationText;
	QString currencyFormat;
	
};	

#endif
