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

#ifndef TABLEDESIGNER_H
#define TABLEDESIGNER_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/window.h>

#include "designertreeview.h"

/** The standard designer for tables.
  * The TableDesigner is the graphical designer for new tables. It basically
  * contains an DesignerTreeView widget that is used in the editor body. The
  * DesignerTreeView widget has editable cells which allows the user to input
  * data. For more information, see the DesignerTreeView widget.
  *
  * A row has its own attributes, as well as type, that the user can edit via an
  * editor that is also located in the TableDesigner.
*/
class TableDesigner: public Gtk::Window {
	public:
		/// Default constructor
		/** Creates an instance of TableDesigner
		*/
		TableDesigner();
		
		/// Destructor
		virtual ~TableDesigner();
		
	private:
		// containers
		Gtk::VBox *vb;
		Gtk::HBox *hb;
		Gtk::HButtonBox *hbb;
		Gtk::Frame *frame;
		Gtk::ScrolledWindow *treeViewWindow;
		Gtk::ScrolledWindow *editorWindow;
		
		// widgets
		Gtk::Label *msgLabel;
		
		Gtk::Button *okButton;
		Gtk::Button *cancelButton;
		
		// tree view
		DesignerTreeView *dtview;
};

#endif
