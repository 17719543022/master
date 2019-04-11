include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++



TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks04_12

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks04_12

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks04_12.pro 			   
	
SOURCES    +=  main.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {	
	
		TARGET = ks04_12_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks04_12
	}
} else {
	debug {
	
		TARGET	= ks04_12_d
	}
	release {
		
		TARGET 	= ks04_12
	}
}