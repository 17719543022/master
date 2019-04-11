
TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= console
QT			+= widgets

TARGET     	= ks02_03
OBJECTS_DIR = $$(TRAINDEVHOME)/obj/chapter02/ks02_03

DESTDIR     = $$(TRAINDEVHOME)/bin

MOC_DIR		= $$(OBJECTS_DIR)/moc
UI_DIR		= $$(OBJECTS_DIR)/ui

				
FORMS		+= dialogbase.ui

HEADERS		+= ks.pro \
				dialog.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp