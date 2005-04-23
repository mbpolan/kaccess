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
// mainwindow.cpp: implementations of mainWindow class

#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <qaction.h>
#include <qapplication.h>
#include <qfiledialog.h>
#include <qlineedit.h>
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qtable.h>
#include <qworkspace.h>
#include <sstream>

#include "dbwindow.h"
#include "dialogs.h"
#include "mainwindow.h"
#include "tablemodel.h"

// graphics
#include "icons/new_generic24.xpm"
#include "icons/open_generic24.xpm"
#include "icons/save_generic24.xpm"
#include "icons/save_as_generic24.xpm"

// our main window constructor
mainWindow::mainWindow(QWidget *parent, const char *name): QMainWindow(parent, name) {
    setCaption("KAccess CVS");
    makePixmaps();
    makeActions();
    makeMenus();
    makeToolbars();
    
    workspace=new QWorkspace(this);
    this->setCentralWidget(workspace);
};

// generate pixmaps
void mainWindow::makePixmaps() {
    QPixmap new_generic=QPixmap((const char**) new_generic_xpm24);
    QPixmap open_generic=QPixmap((const char**) open_generic_xpm24);
    QPixmap save_generic=QPixmap((const char**) save_generic_xpm24);
    QPixmap save_as_generic=QPixmap((const char**) save_as_generic_xpm24);
    
    // add to vector
    gfx.push_back(new_generic);
    gfx.push_back(open_generic);
    gfx.push_back(save_generic);
    gfx.push_back(save_as_generic);
};

// create the actions used through the program
void mainWindow::makeActions() {
    newDbAct=new QAction(tr("New database"), tr("Ctrl+N"), this);
    newDbAct->setIconSet(gfx[GFX_NEW_GENERIC24]);
    newDbAct->setStatusTip("Create a new database");
    connect(newDbAct, SIGNAL(activated()), this, SLOT(slotNewDb()));
    
    openDbAct=new QAction(tr("Open database"), tr("Ctrl+O"), this);
    openDbAct->setIconSet(gfx[GFX_OPEN_GENERIC24]);
    openDbAct->setStatusTip("Open a database");
    connect(openDbAct, SIGNAL(activated()), this, SLOT(slotOpenDbXML()));
    
    saveDbAct=new QAction(tr("Save database"), tr("Ctrl+S"), this);
    saveDbAct->setIconSet(gfx[GFX_SAVE_GENERIC24]);
    saveDbAct->setStatusTip("Save this database");
    connect(saveDbAct, SIGNAL(activated()), this, SLOT(slotSaveDbXML()));
    
    saveDbAsAct=new QAction(tr("Save As"), tr("Alt+S"), this);
    saveDbAsAct->setIconSet(gfx[GFX_SAVE_AS_GENERIC24]);
    saveDbAct->setStatusTip("Save this database as another file");
    connect(saveDbAsAct, SIGNAL(activated()), this, SLOT(slotSaveDbAs()));
    
    exitAct=new QAction(tr("Exit"), tr("Ctrl+Q"), this);
    exitAct->setStatusTip("Exit KAccess");
    connect(exitAct, SIGNAL(activated()), qApp, SLOT(quit()));
    
    aboutKAccessAct=new QAction(tr("About KAccess"), tr("Alt+A"), this);
    aboutKAccessAct->setStatusTip("About KAccess");
    connect(aboutKAccessAct, SIGNAL(activated()), SLOT(aboutKAccess()));
    
    aboutQtAct=new QAction(tr("About Qt"), tr("Alt+Q"), this);
    aboutQtAct->setStatusTip("About the Qt library");
    connect(aboutQtAct, SIGNAL(activated()), qApp, SLOT(aboutQt()));
    
    return;
};

// create menus
void mainWindow::makeMenus() {
    fileMenu=new QPopupMenu(this);
    newDbAct->addTo(fileMenu);
    openDbAct->addTo(fileMenu);
    saveDbAct->addTo(fileMenu);
    saveDbAsAct->addTo(fileMenu);
    
    fileMenu->insertSeparator();
    exitAct->addTo(fileMenu);
    
    helpMenu=new QPopupMenu(this);
    aboutQtAct->addTo(helpMenu);
    helpMenu->insertSeparator();
    
    aboutKAccessAct->addTo(helpMenu);
    
    menuBar()->insertItem("&File", fileMenu);
    menuBar()->insertItem("&Help", helpMenu);
};

// create toolbars
void mainWindow::makeToolbars() {
    return;
};

// slot for making a new database
// TODO: close all open databases prior to opening a new one
void mainWindow::slotNewDb() {
    QString f=QFileDialog::getSaveFileName("/home", "KAccess Databases (*kdb)", this, "open file dialog", "Save Database" );
    
    if (f!=QString::null) {
	saveDialog sd("New Database", "Enter a name for this database", this);
	sd.show();
	sd.raise();
	sd.setActiveWindow();
    
	// the user accepted to create this database
	if (sd.exec() && sd.getText()!=QString::null) {
	    dbWindow *newDb=new dbWindow(sd.getText(), workspace);
	    newDb->show();
	}
    }
};

// slot to open a database
void mainWindow::slotOpenDbXML() {
    QString path=QFileDialog::getOpenFileName("/home", "KAccess Databases (*kdb)", this, "open file dialog", "Open Database");
    xmlDocPtr doc=xmlParseFile(path.ascii());
    std::stringstream ss;
    
    if (doc) {
	xmlNodePtr root, ptr;
	root=xmlDocGetRootElement(doc);
	
	// check if this is a valid file
	if (strcmp((const char*) root->name, "kaccess-database")!=0) {
	    QMessageBox::critical(this, "Load error", "Unable to load database! The file is either corrupt or unsupported.");
	    return;
	}
	
	// database name
	QString dbName=(const char*) xmlGetProp(root, (const xmlChar*) "name");
	
	// the database overview window.note: keep this hidden until loading is complete
	dbWindow *dbWin=new dbWindow(dbName, workspace);
	dbWin->hide();
	
	// descend into the document's children nodes
	ptr=root->children;
	
	// load tables first
	int tcount=atoi((const char*) xmlGetProp(ptr, (const xmlChar*) "count")); // count of tables
	
	// table queue
	std::vector<std::pair<tableModel*, tableEditor*> > tableQueue;
	
	// if there are any tables, load them
	if (tcount > 0) {	    
	    xmlNodePtr tbl=ptr->children, struc;
	    tableModel *tmodel;
	    QString tableName;
	    
	    // load each table
	    for (int i=0; i<tcount; i++) {
		// make a new model
		tmodel=new tableModel;
		struc=tbl->children;
		
		// parse the table structure and generate a table
		int scount=atoi((const char*) xmlGetProp(struc, (const xmlChar*) "count")); // amount of entries here	
		
		// set the table name
		tableName=(const char*) xmlGetProp(tbl, (const xmlChar*) "name");
		tmodel->name=tableName;
		
		// load columns
		xmlNodePtr field=struc->children;
		for (int j=0; j<scount; j++) {
		    QString header=(const char*) xmlGetProp(field, (const xmlChar*) "header");
		    tmodel->addColumn(header, 0, "..."); // add this column
		
		    field=field->next;
		}
	    
		// create a table editor
		tableEditor *ed=new tableEditor(tmodel, dbWin);
		QTable *t=ed->getTable(); // we modify this table
	    
		// load data
		xmlNodePtr data=struc->next, rec=data->children;
		int dcount=atoi((const char*) xmlGetProp(data, (const xmlChar*) "count")), wRow=t->numRows();
		for (int j=0; j < dcount; j++) {
		    // start a new row
		    t->insertRows(wRow);
		    wRow+=1; // working row
		
		    // enter data for each column
		    for (int k=0; k < t->numCols(); k++) {
			ss << "field" << k;
			QString fdata=(const char*) xmlGetProp(rec, (const xmlChar*) ss.str().c_str());
			
			t->setItem(j, k, new QTableItem(t, QTableItem::OnTyping, fdata));
			ss.str("");
		    }
   		    rec=rec->next;
		}
	    
		// the table should now be loaded, add it to the queue list
		tableQueue.push_back(std::pair<tableModel*, tableEditor*> (tmodel, ed));
	    
		tbl=tbl->next;
	    }
	}
	
	// show the database window
	dbWin->show();
	
	// now add all those queued tables into the listview
	for (int i=0; i<tableQueue.size(); i++)
	    dbWin->addTableObj(tableQueue[i].first, tableQueue[i].second);
	
	xmlFreeDoc(doc);
    }	    	
    
    return;
};

// slot to save a database into an XML file
void mainWindow::slotSaveDbXML() {
    // the active database overview window
    dbWindow *dbWin=(dbWindow*) workspace->activeWindow();
    if (!dbWin)
	return;
    
    std::stringstream ss;
    xmlDocPtr doc=xmlNewDoc((const xmlChar*) "1.0");
    xmlNodePtr root, ptr;
    
    root=xmlNewDocNode(doc, NULL, ((const xmlChar*) "kaccess-database"), NULL);
    xmlSetProp(root, (const xmlChar*) "name", ((const xmlChar*) dbWin->caption().ascii())); // db name
    xmlDocSetRootElement(doc, root);
    
    ptr=xmlNewChild(root, NULL, (const xmlChar*) "tables", NULL);
    int tcount=dbWin->tableCount(); // amount of tables
    
    // count of tables
    ss << tcount;
    xmlSetProp(ptr, (const xmlChar*) "count", (const xmlChar*) ss.str().c_str());
    ss.str("");
    
    // save the tables
    xmlNodePtr tbl, struc;
    for (int i=0; i<tcount; i++) {
	// table node
	tbl=xmlNewChild(ptr, NULL, (const xmlChar*) "table", NULL);
	xmlSetProp(tbl, (const xmlChar*) "name", (const xmlChar*) dbWin->tableName(i).ascii());
	
	// first save the table structure
	// table structure contains the column header labels. when loaded, the headers will form the framework
	// for a new table.
	struc=xmlNewChild(tbl, NULL, (const xmlChar*) "structure", NULL);
	QTable *t=dbWin->table(i);
	
	// set a count of items
	ss << t->numCols();
	xmlSetProp(struc, (const xmlChar*) "count", (const xmlChar*) ss.str().c_str());
	ss.str("");
	
	// structure is based on columns
	xmlNodePtr field;
	QHeader *h=t->horizontalHeader();
	for (int j=0; j < h->count(); j++) {
	    // each column is stored as a new node
	    field=xmlNewChild(struc, NULL, (const xmlChar*) "field", NULL);
	    
	    // set the column header label
	    QString name=h->label(j);
	    
	    xmlSetProp(field, (const xmlChar*) "header", (const xmlChar*) name.ascii());
	    //xmlSetProp(field, (const xmlChar*) "type", (const xmlChar* ) ); // TODO: save type of field
	}
	
	// that's it for structure, now we save the actual table data
	QTableItem *t_item;
	xmlNodePtr p, data=xmlNewChild(tbl, NULL, (const xmlChar*) "data", NULL);
	
	// count of all data
	int dcount=t->numRows();
	ss << dcount;
	xmlSetProp(data, (const xmlChar*) "count", (const xmlChar*) ss.str().c_str());
	ss.str("");
	
	for (int j=0; j < t->numRows(); j++) {
	    p=xmlNewChild(data, NULL, (const xmlChar*) "record", NULL); // record node
	    
	    // add to the record node
	    for (int k=0; k < t->numCols(); k++) {
		t_item=t->item(j, k);
		
		// check if this field is blank or not
		QString t_item_text;
		if (t_item)
		    t_item_text=t_item->text();
		
		else
		    t_item_text="";
		
		// node name is field0, field1, field2, ...
		ss << "field" << k;
		xmlSetProp(p, (const xmlChar*) ss.str().c_str(), (const xmlChar*) t_item_text.ascii());
		ss.str("");
	    }
	}
    }
	
    // assuming everything was ok, we ask the user to a path
    QString savePath=QFileDialog::getSaveFileName("/home", "KAccess Databases (*kdb)", this, 
						  "save file dialog", "Save Database");
    savePath+=".kdb"; // kaccess database file extension
    
    xmlKeepBlanksDefault(1);
    xmlSaveFile(savePath.ascii(), doc);
		
};

// slot to save a database as another file
void mainWindow::slotSaveDbAs() {
    return;
};

// slot to display a message about KAccess
void mainWindow::aboutKAccess() {
    aboutKAccessDialog akDialog;
    
    akDialog.show();
    akDialog.raise();
    akDialog.setActiveWindow();
    
    akDialog.exec();
};
