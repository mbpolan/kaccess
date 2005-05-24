/***************************************************************************
 *   Copyright (C) 2005 by the KAccess Team                                *
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
// kaccess.cpp: main project file

// nessesary includes
#include <gtkmm/main.h>
#include "mainwindow.h"

// main
int main(int argc, char *argv[]) {
	// preload a database file
	if (argc == 1) {
		// TODO: loading code
	}
	
	Gtk::Main app(argc, argv);
	
	// main window
	MainWindow *mw=new MainWindow("NULL");
	
	// run the app
	app.run(*mw);
	
	// delete the window
	delete mw;
	
	return 0;
};
