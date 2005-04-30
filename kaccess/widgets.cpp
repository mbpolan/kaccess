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
// widgets.cpp: implementations of custom widgets

#include <qapplication.h>
#include <qeventloop.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qscrollview.h>

// fieldDataEditor nessesary includes
#include "tabledesigner/currencyfieldeditor.h"
#include "tabledesigner/dtfieldeditor.h"
#include "tabledesigner/memofieldeditor.h"
#include "tabledesigner/numberfieldeditor.h"
#include "tabledesigner/textfieldeditor.h"
#include "tabledesigner/ynfieldeditor.h"

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
  * fieldDateEditor widget *
  ********************************************************************/

// main constructor
fieldDataEditor::fieldDataEditor(QWidget *parent, const char *name): QTabWidget(parent, name) {
    // the main scroll view window
    scrollView=new QScrollView(this);
    scrollView->setResizePolicy(QScrollView::AutoOneFit);
    
    // now we create each editor
    editors.push_back(new textFieldEditor(scrollView->viewport()));
    editors.push_back(new numberFieldEditor(scrollView->viewport()));
    editors.push_back(new currencyFieldEditor(scrollView->viewport()));
    editors.push_back(new ynFieldEditor(scrollView->viewport()));
    editors.push_back(new memoFieldEditor(scrollView->viewport()));
    editors.push_back(new dateTimeFieldEditor(scrollView->viewport()));
    
    // hide all of the editors by default
    for (int i=0; i<editors.size(); i++)
	editors[i]->hide();
    
    // set the default editor to a text editor
    scrollView->addChild(editors[FIELD_EDITOR_TEXT]);
    editors[FIELD_EDITOR_TEXT]->show();
    last_editor=FIELD_EDITOR_TEXT;
    
    // add tabs
    addTab(scrollView, "General"); // general page
    addTab(new QWidget(this), "Lookup"); // lookup page
    
    // process any pending events
   qApp->eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
    
};

// method to set the editor to show
void fieldDataEditor::setEditor(int editor_id) {
    fieldEditor *fe=dynamic_cast<fieldEditor*> (editors[last_editor]);
    if (fe) {
	// hide all editors again
	for (int i=0; i<editors.size(); i++)
	    editors[i]->hide();
	
	scrollView->removeChild(fe);
	scrollView->addChild(editors[editor_id] ? editors[editor_id] : NULL);
	
	// show the editor if found and update the last editor id
	if (editors[editor_id]) {
	    editors[editor_id]->show();
	    last_editor=editor_id;
	}
    }
};
