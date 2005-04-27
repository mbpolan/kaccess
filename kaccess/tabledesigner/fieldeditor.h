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
// fieldeditor.h: an abstract field editing widget

#ifndef fieldeditor_h
#define fieldeditor_h

#include <qwidget.h>

// forward declarations
class QComboBox;
class QLabel;
class QLineEdit;

// an abstract field editor class
class fieldEditor: public QWidget {
    public:
	fieldEditor(QWidget *parent=0, const char *name=0);
	
    private:
	// generic widgets
	QLineEdit *fieldSize;
	QLineEdit *fieldFormatting;
	QLineEdit *fieldInputMask;
	QLineEdit *fieldCaption;
	QLineEdit *fieldDefaultValue;
	QLineEdit *fieldValidationText;
	
	// comboboxes
	QComboBox *fieldAllowZero;
	QComboBox *fieldRequired;
	QComboBox *fieldIndexed;
	QComboBox *fieldunicodeCompression;
	
	// number specific widgets
	QComboBox *fieldDecimalPlaces;
	QComboBox *fieldNumberSize;
	
	// currenct specific
	QComboBox *fieldCurrencyFormat;
	
	// labels
	QLabel *fieldSizeLabel;
	QLabel *fieldFormattingLabel;
	QLabel *fieldInputMaskLabel;
	QLabel *fieldCaptionLabel;
	QLabel *fieldDefaultValueLabel;
	QLabel *fieldValidationTextLabel;
	QLabel *fieldAllowZeroLabel;
	QLabel *fieldRequiredLabel;
	QLabel *fieldIndexedLabel;
	QLabel *fieldUniComprLabel;
	QLabel *fieldDecPlacesLabel;
	QLabel *fieldNumPlacesLabel;
	QLabel *fieldCurrencyFrmtLabel;
};

#endif
