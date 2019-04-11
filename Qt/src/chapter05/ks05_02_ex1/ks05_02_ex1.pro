include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_02_ex1

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks05_02_ex1

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_02_ex1.pro \
				dialog.h
	
SOURCES    +=  main.cpp \
				dialog.cpp
				
FORMS		+= dialogbase.ui

RESOURCES	+= ks05_02_ex1.qrc

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
				   
		TARGET = ks05_02_ex1_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks05_02_ex1
	}
} else {
	debug {
		
		TARGET	= ks05_02_ex1_d
	}
	release {			   
		
		TARGET 	= ks05_02_ex1
	}
}