include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks06_02

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks06_02

FORMS 		+= dialogbase.ui

				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks06_02.pro \
			    dialog.h 
				   
	
SOURCES    +=  main.cpp  \
			   dialog.cpp
				
RESOURCES	+= ks06_02.qrc
				
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {				   
		TARGET = ks06_02_d
	}
	CONFIG(release, debug|release) {			   
		TARGET	= ks06_02
	}
} else {
	debug {		
		TARGET	= ks06_02_d
	}
	release {
		TARGET 	= ks06_02
	}
}