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
// mainwindow.h: contains the mainWindow class

#ifndef mainwindow_h
#define mainwindow_h

#include <qmainwindow.h>

class QWorkspace;
class QAction;
class QPopupMenu;

// the main application window
class mainWindow: public QMainWindow {
    Q_OBJECT
    
    public:
	mainWindow(QWidget *parent=0, const char *name=0);
	
	void makeActions();
	void makeMenus();
	void makeToolbars();
	
    public slots:
	void slotNewDb();
	void slotOpenDb();
	void slotSaveDb();
	void slotSaveDbAs();
	void aboutKAccess();
       
   private:
	QWorkspace *workspace;
	
	// actions
	QAction *newDbAct;
	QAction *openDbAct;
	QAction *saveDbAct;
	QAction *saveDbAsAct;
	QAction *exitAct;
	
	QAction  *aboutKAccessAct;
	QAction *aboutQtAct;
	
	// menus
	QPopupMenu *fileMenu;
	QPopupMenu *editMenu;
	QPopupMenu *helpMenu;
	QPopupMenu *OpsMenu;
};

#endif
