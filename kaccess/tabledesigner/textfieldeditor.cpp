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
// textfieldeditor.cpp: implementations of textFieldEditor class

#include <qlayout.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <vector>

#include "fieldeditor.h"
#include "textfieldeditor.h"

// constructor
textFieldEditor::textFieldEditor(QWidget *parent, const char *name): fieldEditor(parent, name) {
    grid=new QGridLayout(this, 1, 1);
    fwidget=new textFieldEditorWidget(this);
    grid->addWidget(fwidget, 0, 0);
};

// constructor for textFieldEditorWidget
textFieldEditorWidget::textFieldEditorWidget(QWidget *parent, const char *name): 
	fieldEditorWidget(parent, name) {
    static const char *ops[]={"Yes", "No", 0};
    
    // vectors
    std::vector<QLabel*> labels;
    std::vector<QWidget*> widgets;
    
    // set up needed labels first
    fieldSizeLabel=new QLabel(tr("Field Size"), this);
    labels.push_back(fieldSizeLabel);
    
    fieldFormattingLabel=new QLabel(tr("Format"), this);
    labels.push_back(fieldFormattingLabel);
    
    fieldInputMaskLabel=new QLabel(tr("Input Mask"), this);
    labels.push_back(fieldInputMaskLabel);
    
    fieldCaptionLabel=new QLabel(tr("Caption"), this);
    labels.push_back(fieldCaptionLabel);
    
    fieldDefaultValueLabel=new QLabel(tr("Default Value"), this);
    labels.push_back(fieldDefaultValueLabel);
    
    fieldValidationRuleLabel=new QLabel(tr("Validation Rule"), this);
    labels.push_back(fieldValidationRuleLabel);
    
    fieldValidationTextLabel=new QLabel(tr("Validation Text"), this);
    labels.push_back(fieldValidationTextLabel);
    
    fieldRequiredLabel=new QLabel(tr("Required"), this);
    labels.push_back(fieldRequiredLabel);
    
    fieldAllowZeroLabel=new QLabel(tr("Allow Zero"), this);
    labels.push_back(fieldAllowZeroLabel);
    
    fieldIndexedLabel=new QLabel(tr("Indexed"), this);
    labels.push_back(fieldIndexedLabel);
    
    // set up line edits
    fieldSize=new QLineEdit(this);
    widgets.push_back(fieldSize);
    
    fieldFormatting=new QLineEdit(this);
    widgets.push_back(fieldFormatting);
    
    fieldInputMask=new QLineEdit(this);
    widgets.push_back(fieldInputMask);
    
    fieldCaption=new QLineEdit(this);
    widgets.push_back(fieldCaption);
    
    fieldDefaultValue=new QLineEdit(this);
    widgets.push_back(fieldDefaultValue);
    
    fieldValidationRule=new QLineEdit(this);
    widgets.push_back(fieldValidationRule);
    
    fieldValidationText=new QLineEdit(this);
    widgets.push_back(fieldValidationText);
    
    // set up comboboxes
    fieldAllowZero=new QComboBox(this);
    widgets.push_back(fieldAllowZero);
    
    fieldRequired=new QComboBox(this);
    widgets.push_back(fieldRequired);
    
    fieldIndexed=new QComboBox(this);
    widgets.push_back(fieldIndexed);
    
    // add some options to the comboxes
    fieldAllowZero->insertStrList(ops);
    fieldRequired->insertStrList(ops);
    fieldIndexed->insertStrList(ops);
    
    grid=new QGridLayout(this, labels.size(), 2);
    
    // add in the widgets
    for (int i=0; i<labels.size(); i++) {
	grid->addWidget(labels[i], i, 0);
	grid->setRowStretch(i, 5);
	grid->setRowSpacing(i, 20);
    }
    
    for (int i=0; i<widgets.size(); i++) {
	grid->addWidget(widgets[i], i, 1);
    }
};
