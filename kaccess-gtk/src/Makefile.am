bin_PROGRAMS = kaccess

AM_CXXFLAGS = `pkg-config gtkmm-2.4 --cflags`
kaccess_LDFLAGS = `pkg-config gtkmm-2.4 --libs` -lxml2

kaccess_SOURCES = buttons.h \
		  dbtreeview.cpp dbtreeview.h \
		  dbwindow.cpp dbwindow.h \
		  kaccess.cpp \
		  mainwindow.cpp mainwindow.h \
		  tabledesigner/cellrendererdatetime.h \
		  tabledesigner/cellrenderernumeric.h \
		  tabledesigner/cellrenderertable.h \
		  tabledesigner/designertreeview.cpp tabledesigner/designertreeview.h \
		  tabledesigner/cellrendererlist.cpp tabledesigner/cellrenderer.h \
		  tabledesigner/cellrendererpopup.cpp tabledesigner/cellrendererpopup.h \
		  tabledesigner/cellrendererstring.h \
		  tabledesigner/popupentry.cpp tabledesigner/popupentry.h \
		  tabledesigner/tabledesigner.cpp tabledesigner/tabledesigner.h \
		  tabledesigner/tablemodel.cpp tabledesigner/tablemodel.h \
		  tabledesigner/tableviewer.cpp tabledesigner/tableviewer.h \
		  triplelist.h \
		  triplet.h \
		  utilities.cpp utilities.h

CLEANFILES = *~ *.o
