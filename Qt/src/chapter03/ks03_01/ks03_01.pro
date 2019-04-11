include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets


TEMPDIR		= $$TRAIN_OBJ_PATH/chapter03/ks03_01

DESTDIR     = $$TRAIN_BIN_PATH

OBJECTS_DIR = $$TEMPDIR
MOC_DIR	= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

TRANSLATIONS += ks03_01.ts
				
FORMS		+= dialogbase.ui

HEADERS		+= ks03_01.pro \
				dialog.h
	
	
SOURCES    +=  main.cpp \
				dialog.cpp				
		

debug_and_release {
	CONFIG(debug, debug|release) {	
	
		TARGET = ks03_01_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks03_01
	}
} else {
	debug {
	
		TARGET	= ks03_01_d
	}
	release {
		
		TARGET 	= ks03_01
	}
}