include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG += console
# ��Ҫ�õ�QApplication
QT += widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks04_03/exe

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks04_03

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks04_03.pro 			   
	
SOURCES    +=  main.cpp

TRANSLATIONS = ks04_03.ts

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {	
	
		TARGET = ks04_03_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks04_03
	}
} else {
	debug {
	
		TARGET	= ks04_03_d
	}
	release {
		
		TARGET 	= ks04_03
	}
}