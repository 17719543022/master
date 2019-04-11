include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_13

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/base/basedll

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_13.pro \
				maindialog.h
	
SOURCES    +=  main.cpp \
				maindialog.cpp
				
FORMS		+=  maindialogbase.ui

RESOURCES	+= ks05_13.qrc

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		TARGET = ks05_13_d
	}
	CONFIG(release, debug|release) {				   
		TARGET	= ks05_13
	}
} else {
	debug {	
		TARGET	= ks05_13_d
	}
	release {			   	
		TARGET 	= ks05_13
	}
}