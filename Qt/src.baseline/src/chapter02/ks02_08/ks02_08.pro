include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG += console


DESTDIR     = $$TRAIN_BIN_PATH

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks02_08.pro 
	
SOURCES    +=  main.cpp 

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter02/ks02_08
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {	
	
		TARGET = ks02_08_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks02_08
	}
} else {
	debug {
	
		TARGET	= ks02_08_d
	}
	release {
		
		TARGET 	= ks02_08
	}
}