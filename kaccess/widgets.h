/***************************************************************************
 *   Copyright (C) 2005 by KanadaKid                                       *
 *   kanadakid@gmail.com                                                   *
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

#include <qwidget.h>
#include <qtabwidget.h>
#include <vector>

class QGridLayout;
class QPushButton;
class QGroupBox;
class QLabel;
class QLineEdit;
class QComboBox;

// fieldEditor defines
#define FIELD_EDITOR_TEXT	0
#define FIELD_EDITOR_NUMBER	1
#define FIELD_EDITOR_CURRENCY	2
#define FIELD_EDITOR_YN		3
#define FIELD_EDITOR_MEMO	4
#define FIELD_EDITOR_DATE_TIME	5

// a widget that displays a list of object buttons
class objButtonList: public QWidget {
    Q_OBJECT
    
    public:
	objButtonList(QWidget *parent, const char *name=0);
	
	QPushButton *tableViewButton;
	QPushButton *formViewButton;
	QPushButton *reportViewButton;
	
    public slots:
	void broadcastTableButton();
	void broadcastFormButton();
	void broadcastReportButton();
	
    signals:
	void buttonClicked(int);
	
    private:
	QGridLayout *grid;
};

// widget that displays text in a frame
class descriptionFrame: public QWidget {
    public:
	descriptionFrame(QWidget *parent=0, const char *name=0);
	
	void setText(const char *text) {msg=text; condense();}
	QString text() const {return msg;}
	
	void setColor(const char *hexColor) {colorTag=hexColor; condense();}
	QString color() const {return colorTag;}
	
	void clear() {data="";}
	
    private:
	void condense(); // form a single string
	
	QGroupBox *box;
	QGridLayout *grid;
	
	QString data; // final string
	QString colorTag;
	QString msg;
	
	QLabel *msgLabel;
};

class fieldEditor;
// widget used to edit a field in a table
class fieldDataEditor: public QTabWidget {
    public:
	fieldDataEditor(QWidget *parent, const char *name=0);
	
	// various methods
	void setEditor(int);
	
    private:
	std::vector<fieldEditor*> editors;
	
};

// an abstract field editor class
class fieldEditor: public QWidget {
    public:
	fieldEditor(QWidget *parent=0, const char *name=0);
	
    private:
	// generic widgets
	QLineEdit *fieldSize;
	QLineEdit *fieldFormatting;
	QLineEdit *fieldInputMask;
	QLineEdit *fieldCaption;
	QLineEdit *fieldDefaultValue;
	QLineEdit *fieldValidationText;
	
	// comboboxes
	QComboBox *fieldAllowZero;
	QComboBox *fieldRequired;
	QComboBox *fieldIndexed;
	QComboBox *fieldunicodeCompression;
	
	// number specific widgets
	QComboBox *fieldDecimalPlaces;
	QComboBox *fieldNumberSize;
	
	// currenct specific
	QComboBox *fieldCurrencyFormat;
};

// text field editor
class textFieldEditor: public fieldEditor {
    public:
	textFieldEditor(QWidget *parent=0, const char *name=0);
};

// number field editor
class numberFieldEditor: public fieldEditor {
    public:
	numberFieldEditor(QWidget *parent=0, const char *name=0);
};

// currency field editor
class currencyFieldEditor: public fieldEditor {
    public:
	currencyFieldEditor(QWidget *parent=0, const char *name=0);
};

// yes/no field editor
class ynFieldEditor: public fieldEditor {
    public:
	ynFieldEditor(QWidget *parent=0, const char *name=0);
};

// memo field editor
class memoFieldEditor: public fieldEditor {
    public:
	memoFieldEditor(QWidget *parent=0, const char *name=0);
};

// date/time field editor
class dateTimeFieldEditor: public fieldEditor {
    public:
	dateTimeFieldEditor(QWidget *parent=0, const char *name=0);
};
