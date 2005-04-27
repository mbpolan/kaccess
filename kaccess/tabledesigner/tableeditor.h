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
// tableeditor.h: a viewer for tables

#ifndef tableeditor_h
#define tableeditor_h

#include <qmainwindow.h>
#include <qtable.h>
#include <qwidget.h>

#include "tablemodel.h"

class QGridLayout;
class tableEditorWidget;

// a viewer-like main window for tables
class tableEditor: public QMainWindow {
    public:
	tableEditor(tableModel *rootTable, QWidget *parent=0, const char *name=0);
	
	// methods
	void setTable(QTable *tb);
	QTable* getTable() const;
	
	QString getName() const;
	
    private:
	tableEditorWidget *editorWidget;
};

// widget used in the tableEditor
class tableEditorWidget: public QWidget {
    public:
	tableEditorWidget(tableModel *rootTable, QWidget *parent=0, const char *name=0);
	
	// methods
	void setTable(QTable *tb) {if (table) delete table; table=tb;}
	QTable* getTable() const {return table;}
	
	QString getName() const {return tname;}
	
    private:
	QGridLayout *grid;
	
	QTable *table; // the main table
	QString tname; // table name
};
	
#endif
