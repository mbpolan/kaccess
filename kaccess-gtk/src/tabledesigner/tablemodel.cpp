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
// tablemodel.cpp: implementations of classes in tablemodel.h

#include "tablemodel.h"

// constructor for TableDataModel class
TableDataModel::TableDataModel() {
};

// destructor for TableDataModel class
TableDataModel::~TableDataModel() {
};

/***************************************************************************/ 

// constructor for TableModel class
TableModel::TableModel() {
};

// destructor for TableModel class
TableModel::~TableModel() {
};

// function to add a row to the model
void TableModel::addRow(std::string name, TableDataModel *data, std::string description) {
	Triplet<std::string, TableDataModel*, std::string> t(name, data, description);
	modelData.push_back(t);
};

// function to remove a row based on name
bool TableModel::removeRowByName(std::string name) {
	for(TableModelIterator it=modelData.begin(); it!=modelData.end(); ++it) {
		if ((*it).first==name) {
			delete (*it).second;
			it=modelData.erase(it);
			
			return true;
		}
	}
	
	return false;
};

// function to insert a row
void TableModel::insertRowByPos(int pos, std::string name, TableDataModel *data, std::string description) {
	int c=0;
	for (TableModelIterator it=modelData.begin(); it!=modelData.end(); ++it) {
		if (c==pos) {
			Triplet<std::string, TableDataModel*, std::string> t(name, data, description);
			modelData.insert(it, t);
			break;
		}
	}
};
