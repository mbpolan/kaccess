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
// fieldEditor.cpp: fieldEditor implementations

#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>

#include "fieldeditor.h"

// constructor
fieldEditor::fieldEditor(QWidget *parent, const char *name): QWidget(parent, name) {
    fwidget=new fieldEditorWidget(this);
};

// constructor for the fieldEditorWidget
fieldEditorWidget::fieldEditorWidget(QWidget *parent, const char *name): QWidget(parent, name) {
};
