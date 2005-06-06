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
// tablemodel.h: TableModel class

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <iostream>
#include <list>

#include "../triplet.h"

/** Class that stores information about the type of field in a table.
  * Every field in a table has its own attributes, and this class is used
  * to store that information.
*/
class TableDataModel {
	public:
		TableDataModel();
		virtual ~TableDataModel();
		
	protected:
};

/// Typedef'd model iterator
typedef std::list<Triplet<std::string, TableDataModel*, std::string> >::iterator TableModelIterator;

/** Class that stores information about a table. 
  * The TableModel class simply accomplishes the function of storing information
  * about a table. This class can be useful if you wish to dump the data from the TableDesigner
  * and hold on to it for later use.
*/
class TableModel {
	public:
		/// Default constructor
		TableModel();
		virtual ~TableModel();
		
		/// Function to add a row to the model.
		/** Adds a new row to the model following the parameters provided.
		  * \param name The name of the field
		  * \param data An instance of TableDataModel holding the attributes for this row
		  * \param description A brief description of this row's purpose
		*/
		void addRow(std::string name, TableDataModel *data, std::string description);
		
		/// Remove a row from the table by name
		/** Removes a row from the model based on name of the row
		  * \param name The name of the target row
		  * \return Boolean value whether or not the row was removed
		*/
		bool removeRowByName(std::string name);
		
		/// Insert a new row with attributes and data
		/** Inserts a row after position pos with the provided parameters.
		  * \param pos The position to insert the row
		  * \param name The name of the field
		  * \param data An instance of TableDataModel holding the attributes for this row
		  * \param description A brief description of this row's purpose
		*/
		void insertRowByPos(int pos, std::string name, TableDataModel *data, std::string description);
		
	protected:
		/// List of rows and their respective attributes
		std::list<Triplet<std::string, TableDataModel*, std::string> > modelData;
};

#endif
