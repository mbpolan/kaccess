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
// numberfieldeditor.cpp: implementations of numberFieldEditor class

#include <qlayout.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qscrollview.h>
#include <vector>

#include "fieldeditor.h"
#include "numberfieldeditor.h"

// constructor
numberFieldEditor::numberFieldEditor(QWidget *parent, const char *name): fieldEditor(parent, name) {
    grid=new QGridLayout(this, 1, 1);
    fwidget=new numberFieldEditorWidget(this);
    grid->addWidget(fwidget, 0, 0);
};

// constructor for numberFieldEditorWidget
numberFieldEditorWidget::numberFieldEditorWidget(QWidget *parent, const char *name): 
	fieldEditorWidget(parent, name) {
    static const char *qb_list[]={"Yes", "No", 0};
    
    // various vectors to store the widgets temporarily
    std::vector<QLabel*> labels;
    std::vector<QWidget*> widgets;
    
    // labels used in the widget
    fieldSizeLabel=new QLabel(tr("Field Size"), this);
    labels.push_back(fieldSizeLabel);
    
    fieldFormattingLabel=new QLabel(tr("Format"), this);
    labels.push_back(fieldFormattingLabel);
    
    fieldDecPlacesLabel=new QLabel(tr("Decimal Places"), this);
    labels.push_back(fieldDecPlacesLabel);
    
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
    
    fieldIndexedLabel=new QLabel(tr("Indexed"), this);
    labels.push_back(fieldIndexedLabel);
    
    // line edits that take info
    fieldSize=new QLineEdit(this);
    widgets.push_back(fieldSize);
    
    fieldFormatting=new QLineEdit(this);
    widgets.push_back(fieldFormatting);
    
    fieldDecPlaces=new QLineEdit(this);
    widgets.push_back(fieldDecPlaces);
    
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
    
    // comboboxes for certain criteria
    fieldRequired=new QComboBox(this);
    widgets.push_back(fieldRequired);
    
    fieldIndexed=new QComboBox(this);
    widgets.push_back(fieldIndexed);
    
    // give the comboboxes some options
    fieldRequired->insertStrList(qb_list);
    fieldIndexed->insertStrList(qb_list);
    
    grid=new QGridLayout(this, labels.size(), 2);
    
    // place the widgets in the grid
    for (int i=0; i<labels.size(); i++) {
	grid->addWidget(labels[i], i, 0);
	grid->setRowStretch(i, 5);
	grid->setRowSpacing(i, 20);
    }
    
    for (int i=0; i<widgets.size(); i++) {
	grid->addWidget(widgets[i], i, 1);
    }
};
