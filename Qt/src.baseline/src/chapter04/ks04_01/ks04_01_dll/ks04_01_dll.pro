include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= lib
LANGUAGE	= C++

CONFIG += dll

TARGET     	= ks04_01_dll
TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks04_01/dll

DESTDIR     = $$TRAIN_LIB_PATH
DLLDESTDIR  = $$TRAIN_BIN_PATH


HEADERS		+= $$TRAIN_SRC_PATH/gui_base.pri \
				ks04_01_dll.pro \
				myclass.h
	
SOURCES    	+=  myclass.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		   
		TARGET = ks04_01_dll_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks04_01_dll
	}
} else {
	debug {				  
				   
		TARGET	= ks04_01_dll_d
	}
	release {				  
				   
		TARGET 	= ks04_01_dll
	}
}