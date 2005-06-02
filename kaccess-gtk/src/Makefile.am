bin_PROGRAMS = kaccess

AM_CXXFLAGS = `pkg-config gtkmm-2.4 --cflags`
kaccess_LDFLAGS = `pkg-config gtkmm-2.4 --libs` -lxml2

kaccess_SOURCES = dbtreeview.cpp dbtreeview.h dbwindow.cpp dbwindow.h kaccess.cpp mainwindow.cpp mainwindow.h

CLEANFILES = *~ *.o
