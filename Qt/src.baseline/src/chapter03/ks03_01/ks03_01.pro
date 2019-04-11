include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets


TARGET     	= ks03_01
TEMPDIR		= $$TRAIN_OBJ_PATH/chapter03/ks03_01

DESTDIR     = $$TRAIN_BIN_PATH

OBJECTS_DIR = $$TEMPDIR
MOC_DIR	= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

				
FORMS		+= dialogbase.ui

HEADERS		+= ks03_01.pro \
				dialog.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp