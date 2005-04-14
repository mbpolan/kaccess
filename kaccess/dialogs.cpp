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
    
    // set some row spacings
    for (int i=0; i<grid->numRows(); i++)
	grid->setRowSpacing(i, 3);
	    
    grid->addMultiCellWidget(msgLabel, 0, 0, 0, 1);
    grid->addMultiCellWidget(lineEdit, 1, 1, 0, 1);
    grid->addWidget(okButton, 2, 0);
    grid->addWidget(cancelButton, 2, 1);
    
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
