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

/// Enumerated row type
enum ROW_TYPE { ROW_TEXT	= 0x00, 
		ROW_NUMBER	= 0x01, 
		ROW_DATE_TIME	= 0x02, 
		ROW_MEMO	= 0x03, 
		ROW_YES_NO	= 0x04 
	      };

/** Class that stores information about the type of field in a table.
  * Every field in a table has its own attributes, and this class is used
  * to store that information.
*/
class TableDataModel {
	public:
		/// Constructor
		TableDataModel();
		
		/// Destructor
		virtual ~TableDataModel();
		
		/** Set the ROW_TYPE of row
		  * \param _type The type of row
		*/
		void setRowType(ROW_TYPE _type) { type=_type; };
		
		/** Get the ROW_TYPE for this row
		  * \return The type of row
		*/
		ROW_TYPE getRowType() const { return type; };
		
	protected:
		// the type of row
		ROW_TYPE type;
};

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
		
		/// A single row in the TableDesigner
		class Row {
			public:
				/// Default constructor
				Row() {};
				
				/** Constructor
				  * \paran name The row's name
				  * \param data TableDataModel for this row
				  * \param description A description of this row
				*/
				Row(std::string name, TableDataModel *data, std::string description) {
					attrs.first=name;
					attrs.second=data;
					attrs.third=description; 
				};
				
				/** Get the row's name
				  * \return The name of the row
				*/
				std::string getName() const { return attrs.first; };
				
				/** Get this row's attribute data
				  * \return The attribute data for this row
				*/
				TableDataModel* getData() const { return attrs.second; };
				
				/** Get this row's description
				  * \param The description for this row
				*/
				std::string getDescription() const { return attrs.third; };
				
			protected:
				Triplet<std::string, TableDataModel*, std::string> attrs;
		};
		
		/// Function to add a row to the model.
		/** Adds a new row to the model following the parameters provided.
		  * \param name The name of the field
		  * \param data An instance of TableDataModel holding the attributes for this row
		  * \param description A brief description of this row's purpose
		*/
		void addRow(const Row &row);
		
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
		void insertRowByPos(int pos, const Row &row);
		
		/** Get the size of the model
		  * \return The size of this model
		*/
		int size() const { return modelData.size(); };
		
		/** Get a certain row from the model
		  * \return The requested row's Triplet
		*/
		Row getRow(int pos) const;
		
		/** Set the row with the primary key
		  * \param row The target row
		*/
		void setPKeyRow(int row) { pkeyRow=row; };
		
		/** Get the row containing the primary key
		  * \return The row number
		*/
		int getPKeyRow() const { return pkeyRow; };
		
		/** Set the name of this table
		  * \param _name The name of this table
		*/
		void setName(std::string _name) { name=_name; };
		
		/** Get the name of this table
		  * \return The table's name
		*/
		std::string getName() const { return name; };
		
	protected:
		/// List of rows and their respective attributes
		std::list<Row > modelData;
		
		/// The row that is the primary key
		int pkeyRow;
		
		/// The name of this table
		std::string name;
};

// typedef'd TableModel iterator
typedef std::list<TableModel::Row>::iterator TableModelIterator;

// typedef'd const TableModel iterator
typedef std::list<TableModel::Row>::const_iterator TableModelConstIterator;

#endif
