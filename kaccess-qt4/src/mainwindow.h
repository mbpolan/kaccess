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
// mainwindow.h: the MainWindow class

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "dialogs.h"

// forward declarations
class QWorkspace;
class DBWindow;

/** The main window used as a base for all new windows.
  * This is the main window that is the first to be drawn on the screen. If you plan
  * on making customized windows that should appear after this window is constructed,
  * then make sure to set a MainWindow as the parent for that window. This will ensure
  * that any windows opened will be properly disposed of once the application is closed.
*/

class MainWindow: public QMainWindow {
	Q_OBJECT
	
	public:
		/// Constructor
		/** Constructs the MainWindow
		  * \param parent The parent for this widget; should be NULL
		  * \param flags Flags to pass to this window (see Qt4 docs)
		*/
		MainWindow(QWidget *parent=0, Qt::WFlags flags=0);
	
	public slots:
		/// New database action handler
		void onNewDB();
		
		/// Open database action handler
		void onOpenDB();
		
		/// Save database action handler
		void onSaveDB();
		
		/// Save database as action handler
		void onSaveDBAs();
		
		/// Close database action handler
		void onCloseDB();
		
		/// Quit action handler
		void onQuit();
		
		/// About KAccess handler
		void onAboutKAccess();
		
	protected:
		/// Build the GUI
		void construct();
		
		/// Create actions
		void buildActions();
		
		/// Create the MenuBar
		void buildMenubar();
		
		/// Create the status bar
		void buildStatusBar();
		
		/// Various File menu actions
		QAction *m_NewDBAct;
		QAction *m_OpenDBAct;
		QAction *m_SaveDBAct;
		QAction *m_SaveDBAsAct;
		QAction *m_CloseDBAct;
		QAction *m_QuitAct;
		
		/// Various Help menu actions
		QAction *m_AboutKAccessAct;
		
		/// Workspace widget (central)
		QWorkspace *m_Workspace;
		
		/// About KAccess dialog
		AboutDialog *m_AboutDialog;
		
		/// Database control window
		DBWindow *m_DBWindow;
};

#endif
