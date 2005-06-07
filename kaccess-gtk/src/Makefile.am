bin_PROGRAMS = kaccess

AM_CXXFLAGS = `pkg-config gtkmm-2.4 --cflags`
kaccess_LDFLAGS = `pkg-config gtkmm-2.4 --libs` -lxml2

kaccess_SOURCES = buttons.h \
		  dbtreeview.cpp dbtreeview.h \
		  dbwindow.cpp dbwindow.h \
		  kaccess.cpp \
		  mainwindow.cpp mainwindow.h \
		  tabledesigner/designertreeview.cpp tabledesigner/designertreeview.h \
		  tabledesigner/cellrendererlist.cpp tabledesigner/cellrenderer.h \
		  tabledesigner/cellrendererpopup.cpp tabledesigner/cellrendererpopup.h \
		  tabledesigner/popupentry.cpp tabledesigner/popupentry.h \
		  tabledesigner/tabledesigner.cpp tabledesigner/tabledesigner.h \
		  tabledesigner/tablemodel.cpp tabledesigner/tablemodel.h

CLEANFILES = *~ *.o
