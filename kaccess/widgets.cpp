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

#include <qpushbutton.h>
#include <qlayout.h>
#include <qgroupbox.h>
#include <qlabel.h>

#include "widgets.h"

/*********************************************************************
  * objButtonList widget *
  ********************************************************************/

// constructor for the object button list widget
objButtonList::objButtonList(QWidget *parent, const char *name): QWidget(parent, name) {
    grid=new QGridLayout(this, 3, 1);
    
    tableViewButton=new QPushButton("Tables", this);
    tableViewButton->setOn(false);
    tableViewButton->setFlat(true);
    
    formViewButton=new QPushButton("Forms", this);
    formViewButton->setOn(false);
    formViewButton->setFlat(true);
    
    reportViewButton=new QPushButton("Reports", this);
    reportViewButton->setOn(false);
    reportViewButton->setFlat(true);
    
    grid->addWidget(tableViewButton, 1, 0);
    grid->addWidget(formViewButton, 2, 0);
    grid->addWidget(reportViewButton, 3, 0);
    
    connect(tableViewButton, SIGNAL(clicked()), this, SLOT(broadcastTableButton()));
    connect(formViewButton, SIGNAL(clicked()), this, SLOT(broadcastFormButton()));
    connect(reportViewButton, SIGNAL(clicked()), this, SLOT(broadcastReportButton()));
};

// slot to emit a table button clicked signal
void objButtonList::broadcastTableButton() {
    emit buttonClicked(0x01);
};

// slot to emit a form button clicked signal
void objButtonList::broadcastFormButton() {
    emit buttonClicked(0x02);
};

// slot to emit a report buttton clicked signal
void objButtonList::broadcastReportButton() {
    emit buttonClicked(0x03);
};

/*********************************************************************
  * descriptionFrame widget *
  ********************************************************************/

descriptionFrame::descriptionFrame(QWidget *parent, const char *name): QWidget(parent, name) {
    box=new QGroupBox(this);
    grid=new QGridLayout(box, 3, 1);
    
    // defaults
    data="NULL";
    colorTag="#0000A0";
    msg="NULL";
    
    for (int i=0; i < grid->numRows(); i++)
	grid->setRowSpacing(i, 3);
    
    msgLabel=new QLabel(data, box);
    
    grid->addWidget(msgLabel, 1, 0);
};

// form a single string to be displayed in the label
void descriptionFrame::condense() {
    data="<font color="; // start tag
    data+=(colorTag="#0000A0"); // default color is dark blue
    data+=(msg="NULL"); // our message
    data+=(QString) "</font>"; // end tag
    
    msgLabel->setText(data);
};

/*********************************************************************
  * fieldDataEditor widget *
  ********************************************************************/

fieldDataEditor::fieldDataEditor(QWidget *parent, const char *name): QTabWidget(parent, name) {
    addTab(new QWidget(this), "General"); // general page
    addTab(new QWidget(this), "Lookup"); // lookup page
    
    // now we create each editor
    editors.push_back(new textFieldEditor(this));
    editors.push_back(new numberFieldEditor(this));
    editors.push_back(new currencyFieldEditor(this));
    editors.push_back(new ynFieldEditor(this));
    editors.push_back(new memoFieldEditor(this));
    editors.push_back(new dateTimeFieldEditor(this));
    
};

/*********************************************************************
  * abstract fieldEditor widget *
  ********************************************************************/

fieldEditor::fieldEditor(QWidget *parent, const char *name): QWidget(parent, name) {
};

/*********************************************************************
  * textFieldEditor widget *
  ********************************************************************/

textFieldEditor::textFieldEditor(QWidget *parent, const char *name): fieldEditor(parent, name) {
};

/*********************************************************************
  * numberFieldEditor widget *
  ********************************************************************/

numberFieldEditor::numberFieldEditor(QWidget *parent, const char *name): fieldEditor(parent, name) {
};

/*********************************************************************
  * currencyFieldEditor widget *
  ********************************************************************/

currencyFieldEditor::currencyFieldEditor(QWidget *parent, const char *name): fieldEditor(parent, name) {
};

/*********************************************************************
  * ynFieldEditor widget *
  ********************************************************************/

ynFieldEditor::ynFieldEditor(QWidget *parent, const char *name): fieldEditor(parent, name) {
};

/*********************************************************************
  * memoFieldEditor widget *
  ********************************************************************/

memoFieldEditor::memoFieldEditor(QWidget *parent, const char *name): fieldEditor(parent, name) {
};

/*********************************************************************
  * dateTimeFieldEditor widget *
  ********************************************************************/

dateTimeFieldEditor::dateTimeFieldEditor(QWidget *parent, const char *name): fieldEditor(parent, name) {
};
