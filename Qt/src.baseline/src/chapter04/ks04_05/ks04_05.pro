include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG += console
# 需要用到QApplication
QT += widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks04_05/

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks04_05

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks04_05.pro 	\
				myclass.h
	
SOURCES    +=  main.cpp \
				myclass.cpp


OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {	
	
		TARGET = ks04_05_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks04_05
	}
} else {
	debug {
	
		TARGET	= ks04_05_d
	}
	release {
		
		TARGET 	= ks04_05
	}
}