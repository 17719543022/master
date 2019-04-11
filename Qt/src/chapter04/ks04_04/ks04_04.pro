include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG += console
# 需要用到QApplication
QT += widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks04_04

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks04_04

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks04_04.pro 	\
				myclass.h
	
SOURCES    +=  main.cpp \
				myclass.cpp

TRANSLATIONS = ks04_04.ts

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {	
		LIBS += -lbasedll_d

		TARGET = ks04_04_d
	}
	CONFIG(release, debug|release) {			   
		LIBS += -lbasedll
			   
		TARGET	= ks04_04
	}
} else {
	debug {
		LIBS += -lbasedll_d
	
		TARGET	= ks04_04_d
	}
	release {
		LIBS += -lbasedll
		
		TARGET 	= ks04_04
	}
}