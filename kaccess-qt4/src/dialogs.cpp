/***************************************************************************
 *   Copyright (C) 2006 by The KAccess Team                                *
 *   http://kaccess.sf.net                                                 *
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
// dialogs.cpp: implementations of Dialog classes

#include <QFile>
#include <QLabel>
#include <QLayout>
#include <QPixmap>
#include <QTabWidget>
#include <QTextEdit>
#include <QTextStream>

#include "dialogs.h"

#include "images/kaccess.xpm"

/********************************************/
// AboutDialog

// constructor
AboutDialog::AboutDialog(QWidget *parent): QDialog(parent) {
	setWindowTitle("About KAccess");
	construct();
};

// build the gui
void AboutDialog::construct() {
	// main layout
	QVBoxLayout *box=new QVBoxLayout(this);
	
	// hbox for icon and version label
	QHBoxLayout *hb=new QHBoxLayout;
	
	// tab widget
	m_TabWidget=new QTabWidget(this);
	
	// general info label
	m_GeneralLabel=new QLabel;
	m_GeneralLabel->setText("KAccess Development Team<br><br>"
		     "<b>Programmers</b><br>"
		     "Mike Polan (<i>kanadakid@gmail.com</i>)<br>"
		     "Stephan Santos (<i>bandana_blue@users.sourceforge.net</i>)<br>"
		     "<br><b>Web Team</b><br>"
		     "George Rile (<i>millenium_man3@users.sourceforge.net</i>)");
	m_GeneralLabel->setTextFormat(Qt::RichText);
	
	// license view
	m_LicenseView=new QTextEdit;
	QTextDocument *doc=new QTextDocument;
	
	// FIXME: display the entire license
	doc->setPlainText("Licensed under the GNU GPL License");
	m_LicenseView->setDocument(doc);
	m_LicenseView->setReadOnly(true);
	
	// version label
	m_VersionLabel=new QLabel("<b>KAccess v1.0</b>", this);
	m_VersionLabel->setTextFormat(Qt::RichText);
	
	// icon
	m_Icon=new QPixmap(kaccess_xpm);
	QLabel *ilabel=new QLabel(this);
	ilabel->setPixmap(*m_Icon);
	
	// add some tabs
	m_TabWidget->addTab(m_GeneralLabel, "Authors");
	m_TabWidget->addTab(m_LicenseView, "License");
	
	// add widgets
	hb->addWidget(ilabel);
	hb->addWidget(m_VersionLabel);
	
	// add the layouts/widgets
	box->addLayout(hb);
	box->addWidget(m_TabWidget);
};
