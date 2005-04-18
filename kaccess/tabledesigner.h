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
// tabledesigner.h: contains the tableDesigner class and variants

#ifndef tabledesigner_h
#define tabledesigner_h

#include <qmainwindow.h>
#include <qwidget.h>

class QAction;
class QLabel;
class QLineEdit;
class QGridLayout;
class QPushButton;
class QStringList;
class QTable;
class QToolBar;
class descriptionFrame;
class fieldDataEditor;

class tableDesignerWidget;

// the table designer class
class tableDesigner: public QMainWindow {
    Q_OBJECT
    
    public:
	tableDesigner(QWidget *parent=0, const char *name=0);
	
	// various methods
	QTable* getTable() const {return table;}
	
    public slots:
	void hideAndClear();
	
    signals:
	void tdSaveButtonClicked(QString);
	
    private:
	QToolBar *mainToolbar;
	
	QTable *table;
	tableDesignerWidget *designer;
	
	QAction *primaryKeyAct;
	
	// private methods
	void makeActions();
	void makeToolbars();
};

// widget that is used to in class tableDesigner
class tableDesignerWidget: public QWidget {
    Q_OBJECT
    
    public:
	tableDesignerWidget(QWidget *parent, const char *name=0);
	
	// methods
	void fillDataTypeBox(QStringList&);
	
	QTable *table; // the main table
	
	// other methods
	bool isPrimaryKeyActivated() const {return hasPrimaryKey;}
	void clear();
	
    public slots:
	void updateCellDescription(int, int);
	void broadcastSaveButtonClicked();
	void setPrimaryKey(bool);
	
    signals:
	void saveButtonClicked(QString);
	void cancelButtonClicked();
	
    private:
	QLineEdit *fieldSize; // the size of the field (used by all editors)
	QStringList data_types; // list of data types
	
	QLabel *msgLabel; // FIXME: use descriptionFrame instead of this
	QGridLayout *grid; // layout grid
	
	fieldDataEditor *f_editor; // field editors
	descriptionFrame *dFrame; // description frame
	
	// buttons
	QPushButton *saveTableButton;
	QPushButton *cancelButton;
	
	bool hasPrimaryKey;
	int primaryKey;
};

#endif
