/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
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

#include "widgets.h"

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
};
