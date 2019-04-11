include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TRANSLATIONS = languagepack.ts

TARGET     	= ks03_02
TEMPDIR		= $$TRAIN_OBJ_PATH/chapter03/ks03_02

DESTDIR     = $$TRAIN_BIN_PATH

OBJECTS_DIR = $$TEMPDIR
MOC_DIR	= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

				
FORMS		+= dialogbase.ui

HEADERS		+= ks03_02.pro \
				dialog.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp