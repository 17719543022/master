
TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= console
QT			+= widgets


TARGET     	= ks02_04
TEMPDIR		= $$(TRAINDEVHOME)/obj/chapter02/ks02_04

DESTDIR     = $$(TRAINDEVHOME)/bin

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

				
FORMS		+= dialogbase.ui

HEADERS		+= ks02_04.pro \
				dialog.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp