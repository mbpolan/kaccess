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
// dialogs.cpp: implementations of dialogs

#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qspinbox.h>
#include <qtabwidget.h>
#include <qtextedit.h>

#include "dialogs.h"

/*********************************************************************
  * saveDialog widget *
  ********************************************************************/

saveDialog::saveDialog(QString title, QString msg, QWidget *parent, const char *name): QDialog(parent, name) {
    setCaption(title);
    grid=new QGridLayout(this, 3, 2);
    
    msgLabel=new QLabel(msg, this);
    lineEdit=new QLineEdit(this);
    
    // buttons
    okButton=new QPushButton("Ok", this);
    cancelButton=new QPushButton("Cancel", this);
	    
    grid->addMultiCellWidget(msgLabel, 0, 0, 0, 1);
    grid->addMultiCellWidget(lineEdit, 1, 1, 0, 1);
    grid->addWidget(okButton, 2, 0);
    grid->addWidget(cancelButton, 2, 1);
    
    // set some row spacings
    for (int i=0; i<grid->numRows(); i++)
	grid->setRowSpacing(i, 3);
    
    grid->setMargin(3);
    
    // connect the push buttons
    connect(okButton, SIGNAL(clicked()), SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
};

// set the dialog's label
void saveDialog::setMsg(QString msg) {
    msgLabel->setText(msg);
};

// get the dialog's label
QString saveDialog::getMsg() const {
    return msgLabel->text();
};

// get the value stored in the line edit
QString saveDialog::getText() const {
    return lineEdit->text();
};


/*********************************************************************
  * aboutKAccess dialog *
  ********************************************************************/

// aboutKAccessDialog constructor
aboutKAccessDialog::aboutKAccessDialog(QWidget *parent, const char *name): QDialog(parent, name) {
    setCaption("About KAccess");
    setFixedSize(410, 290);
    
    grid=new QGridLayout(this, 3, 1);
    tabBox=new QTabWidget(this);
    
    // general info about KAccess
    aboutBox=new QLabel("<b>KAccess Database Management</b><br>"
		      "<br>(c) 2005, The KAccess Team<br>"
		      "Website: <a href=http://kaccess.sf.net>http://kaccess.sf.net</a>", this);
    aboutBox->setAlignment(Qt::AlignCenter);
    
    // developers
    devBox=new QLabel("<br><b>The KAccess Team</b><hr><br>"
	                    "<b>Developers</b><br>"
		    "<br>Mike Polan (KanadaKid)<br>kanadakid@gmail.com<br>"
		    "<br>Stephan Santos (bandana_blue)<br>bandana_blue@users.sourceforge.net<br>"
		    "<br><b>Website Management</b><br>"
		    "<br>George Rile (millennium_man3)<br>millennium_man@usa.com<br>", this);
    
    // TODO: this is where we will put the GPL
    licenseBox=new QTextEdit(this);
    
    // prevent the user from changing any text
    licenseBox->setReadOnly(true);
    
    tabBox->insertTab(aboutBox, "About");
    tabBox->insertTab(devBox, "Authors");
    tabBox->insertTab(licenseBox, "License Agreement");
    
    // title label
    kaccessLabel=new QLabel("<font size=14>KAccess v(CVS)</font>", this);
    
    // the 'ok' button
    okButton=new QPushButton("Ok", this);
    connect(okButton, SIGNAL(clicked()), SLOT(accept()));
    
    // now we add the widgets into the grid
    grid->addWidget(kaccessLabel, 0, 0);
    grid->addWidget(tabBox, 1, 0);
    grid->addWidget(okButton, 2, 0);
    
    // stretch factors
    grid->setRowStretch(0, 3);
    grid->setRowStretch(1, 8);
    grid->setRowStretch(2, 2);
    
    // row spacing
    for (int i=0; i<grid->numRows(); i++)
	grid->setRowSpacing(i, 3);
    
    // margin
    grid->setMargin(3);
};

/*********************************************************************
  * integerInputDialog dialog *
  ********************************************************************/

// integerInput dialog constructor
integerInputDialog::integerInputDialog(int maxVal, int minVal, QString instrMsg, QString title, QWidget *parent, const char *name): 
	QDialog(parent, name) {
    
    setCaption(title);
    grid=new QGridLayout(this, 4, 2);
    
    // message across the top of the widget
    titleLabel=new QLabel(instrMsg, this);
    
    // spin box
    // syntax: minimum value, maximum value, steps (1), parent, name
    spinBox=new QSpinBox(minVal, maxVal, 1, this);
    
    // slider
    hSlider=new QSlider(minVal, maxVal, 1, minVal, Qt::Horizontal, this);
    
    // buttons
    okButton=new QPushButton("Ok", this);
    cancelButton=new QPushButton("Cancel", this);
    connect(okButton, SIGNAL(clicked()), SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
    
    // add the widgets to the grid layout manager
    grid->addMultiCellWidget(titleLabel, 0, 0, 0, 1); // title label (2 cells)
    grid->addWidget(spinBox, 1, 0); // spin box
    grid->addMultiCellWidget(hSlider, 2, 2, 0, 1); // slider (2 cells)
    grid->addWidget(okButton, 3, 0); // ok button
    grid->addWidget(cancelButton, 3, 1); // cancel button
    
    // connect the two widgets (slider and spin box)
    connect(hSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), hSlider, SLOT(setValue(int)));
    
    // set a margin
    grid->setMargin(3);
};
