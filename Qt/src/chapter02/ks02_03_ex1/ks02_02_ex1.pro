
TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= console
QT			+= widgets

TARGET     	= ks02_02_ex1
OBJECTS_DIR = $$(TRAINDEVHOME)/obj/chapter02/ks02_02_ex1

DESTDIR     = $$(TRAINDEVHOME)/bin


MOC_DIR		= $$(OBJECTS_DIR)/moc
UI_DIR		= $$(OBJECTS_DIR)/ui

#INCLUDEPATH *=  \
#				$$UI_DIR
				
FORMS		+= dialog.ui

HEADERS		+= ks02_02_ex1.pro \
				dialog.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp
