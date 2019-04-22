include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_14

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/base/basedll

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_14.pro \
				maindialog.h
	
SOURCES    +=  main.cpp \
				maindialog.cpp
				
FORMS		+=  maindialogbase.ui

RESOURCES	+= ks05_14.qrc

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		TARGET = ks05_14_d
	}
	CONFIG(release, debug|release) {				   
		TARGET	= ks05_14
	}
} else {
	debug {	
		TARGET	= ks05_14_d
	}
	release {			   	
		TARGET 	= ks05_14
	}
}