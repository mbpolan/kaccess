/***************************************************************************
 *   Copyright (C) 2004 by KanadaKid                                       *
 *   kanadakid@gmail.com                                                   *
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
 
#include <qmainwindow.h>

class objButtonList;
class QGroupBox;
class QListView;
class QAction;
class QPushButton;
class QToolbar;
class QDockWindow;

class dbWindow: public QMainWindow {
    Q_OBJECT
    
    public:
	dbWindow(const char *dbName, QWidget *parent=0, const char *name=0);
	
	void makeActions();
	void makeButtons();
	void makeToolbars();
	void makeObjList();
	
    public slots:
	void newSelected();
	void openSelected();
	void designSelected();
	
    private:
	QDockWindow *sidePanel;
	
	QAction *openThingAct;
	QAction *newThingAct;
	QAction *designThingAct;
	
	objButtonList  *objButtons;
	QListView *objList;
	
	QToolBar *mainTb;
};
