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
// dialogs.h: classes that are dialogs or derive from QDialog and friends

#ifndef dialogs_h
#define dialogs_h

#include <qdialog.h>
#include <qspinbox.h>

class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class QTabWidget;
class QTextEdit;

// dialog box to save table
class saveDialog: public QDialog {
    public:
	saveDialog(QString title="Save", QString msg="Enter save name", QWidget *parent=0, const char *name=0);
	
	// methods
	void setMsg(QString msg);
	QString getMsg() const;
	
	QString getText() const;
	
    private:
	QGridLayout *grid;
	QLabel *msgLabel;
	
	QLineEdit *lineEdit;
	
	QPushButton *okButton;
	QPushButton *cancelButton;
};

// dialog used to present some information about kaccess
class aboutKAccessDialog: public QDialog {
    public:
	aboutKAccessDialog(QWidget *parent=0, const char *name=0);
	
    private:
	QGridLayout *grid;
	
	QTabWidget *tabBox;
	QLabel *aboutBox;
	QLabel *devBox;
	QLabel *imageLabel;
	QTextEdit *licenseBox;
	
	QLabel *kaccessLabel;
	
	QPushButton *okButton;
};

// input dialog with a spinbox with a slider
class integerInputDialog: public QDialog {
    public:
	integerInputDialog(int minVal=1, int maxVal=50, QString instrMsg="Enter a value to use.", 
			   QString title="Query", QWidget *parent=0, const char *name=0);
	
	int getValue() const {return spinBox->value();}
	
    private:
	QGridLayout *grid;
	QLabel *titleLabel;
	
	// slider and spinbox
	QSlider *hSlider;
	QSpinBox *spinBox;
	
	// buttons
	QPushButton *okButton;
	QPushButton *cancelButton;
};

#endif
