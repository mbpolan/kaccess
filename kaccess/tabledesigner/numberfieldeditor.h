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
// numberfieldeditor.h: derived field editor for numbers

#ifndef numberfieldeditor_h
#define numberfieldeditor_h

#include "fieldeditor.h"

class QGridLayout;

// number field editor
class numberFieldEditorWidget;
class numberFieldEditor: public fieldEditor {
    public:
	numberFieldEditor(QWidget *parent=0, const char *name=0);
	
    private:
	QGridLayout *grid;
	numberFieldEditorWidget *fwidget;
};

// widget used in the numberFieldEditor
class numberFieldEditorWidget: public fieldEditorWidget {
    public:
	numberFieldEditorWidget(QWidget *parent=0, const char *name=0);
	
    private:
	QGridLayout *grid;
};
    
#endif
