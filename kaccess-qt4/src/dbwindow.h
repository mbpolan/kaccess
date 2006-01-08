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
// dbwindow.h: the DBWindow class

#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QMainWindow>

// forward declarations
class QGroupBox;
class QListWidget;
class QPushButton;

/** The window that is used for each database for control.
  * This is the window that control all aspects of database management. Everytime
  * a new database is made, it is assigned an instance of this window so the user
  * can control it.
*/

class DBWindow: public QMainWindow {
	Q_OBJECT
	
	public:
		/** Constructor
		  * \param parent Parent widget
		*/
		DBWindow(QWidget *parent=0);
		
		/// Clears the database
		void clear();
		
		/** Set the database name
		  * \param name The new name for this database
		*/
		void setName(const QString &name);
		
		/** Get the name of the database
		  * \return The name of this database
		*/
		QString getName() const { return m_DBName; };
		
		/** Check if the database has been modified
		  * \return True is modified, otherwise false
		*/
		bool modified() const { return m_Modified; };
		
		/** Set if the database is active or not
		  * \param active True for active, false otherwise
		*/
		void setActive(bool active) { m_Active=active; };
		
		/** Check if the database is active 
		  * \return True is active, false otherwise
		*/
		bool active() const { return m_Active; };
	
	signals:
		/// Signal emitted when the window was modified
		void sigWindowModified();
	
	public slots:
		/// Slot for clicks on the TablesButton
		void onTablesButtonClicked();
		
		/// Slot for CommentButton clicks
		void onCommentButtonClicked();
		
		/// Slot for DBOptsButton clicks
		void onDBOptsButtonClicked();
		
	protected:
		/// Build the GUI
		void construct();
		
		/// Flag that this window is modified
		void flagModified(bool yes) { m_Modified=yes; };
		
		/// Was the database modified?
		bool m_Modified;
		
		/// Is this window active?
		bool m_Active;
		
		/// Name of the database
		QString m_DBName;
		
		/// Tables view button
		QPushButton *m_TablesButton;
		
		/// Comment button
		QPushButton *m_CommentButton;
		
		/// Database options button
		QPushButton *m_DBOptsButton;
		
		/// Tree view containing tables
		QListWidget *m_TableView;
		
		/// Group for button
		QGroupBox *m_ButtonGroup;
};

#endif
