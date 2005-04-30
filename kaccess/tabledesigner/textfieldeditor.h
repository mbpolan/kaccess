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
// textfieldeditor.h: derived text field editor widget

#ifndef textfieldeditor_h
#define textfieldeditor_h

#include <qwidget.h>

#include "fieldeditor.h"

class QGridLayout;

// text field editor
class textFieldEditorWidget;
class textFieldEditor: public fieldEditor {
    public:
	textFieldEditor(QWidget *parent=0, const char *name=0);
	
    protected:
	QGridLayout *grid;
	textFieldEditorWidget *fwidget;
};

// widget used in the text field editor
class textFieldEditorWidget: public fieldEditorWidget {
    public:
	textFieldEditorWidget(QWidget *parent=0, const char *name=0);
	
    private:
	QGridLayout *grid;
};

#endif
