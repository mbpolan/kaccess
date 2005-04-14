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

#include <qdialog.h>
#include <qwidget.h>

class QLineEdit;
class QTable;
class QGridLayout;
class QStringList;
class QLabel;
class QPushButton;
class descriptionFrame;
class fieldDataEditor;

class tableDesignerWidget;

// the table designer class
class tableDesigner: public QDialog {
    Q_OBJECT
    
    public:
	tableDesigner(QWidget *parent=0, const char *name=0);
	
	// various methods
	QTable* getTable() const {return table;}
	
    signals:
	void tdSaveButtonClicked(QString);
	
    private:
	QTable *table;
	tableDesignerWidget *designer;
};

// widget that is used to in class tableDesigner
class tableDesignerWidget: public QWidget {
    Q_OBJECT
    
    public:
	tableDesignerWidget(QWidget *parent, const char *name=0);
	
	// methods
	void fillDataTypeBox(QStringList&);
	
	QTable *table; // the main table	
	
    public slots:
	void updateCellDescription(int, int);
	void broadcastSaveButtonClicked();
	
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
};

#endif
