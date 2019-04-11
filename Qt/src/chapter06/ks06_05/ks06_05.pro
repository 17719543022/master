include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks06_05

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks06_05

FORMS 		+= dialogbase.ui

				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks06_05.pro \
			    dialog.h 
				   
	
SOURCES    +=  main.cpp  \
			   dialog.cpp
				
RESOURCES	+= ks06_05.qrc
				
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {				   
		TARGET = ks06_05_d
	}
	CONFIG(release, debug|release) {			   
		TARGET	= ks06_05
	}
} else {
	debug {		
		TARGET	= ks06_05_d
	}
	release {
		TARGET 	= ks06_05
	}
}