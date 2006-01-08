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
// dialogs.h: various dialogs

#ifndef DIALOGS_H
#define DIALOGS_H

#include <QDialog>

// forward declarations
class QLabel;
class QPixmap;
class QTextEdit;
class QTabWidget;

/** Dialog that displays information about KAccess.
*/

class AboutDialog: public QDialog {
	public:
		/** Constructor 
		  * Builds a default AboutDialog
		  * \param parent Parent widget for this dialog
		*/
		AboutDialog(QWidget *parent=0);
	
	protected:
		/// Construct the GUI
		void construct();
		
		/// Icon image
		QPixmap *m_Icon;
		
		/// Tabbed widget for easy nagivation
		QTabWidget *m_TabWidget;
		
		/// General info label
		QLabel *m_GeneralLabel;
		
		/// Version label
		QLabel *m_VersionLabel;
		
		/// License information
		QTextEdit *m_LicenseView;
};

#endif
