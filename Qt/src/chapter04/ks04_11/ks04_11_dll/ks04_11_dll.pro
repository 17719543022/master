include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= lib
LANGUAGE	= C++

CONFIG += dll


TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks04_11/dll

DESTDIR     = $$TRAIN_LIB_PATH
DLLDESTDIR  = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks04_11

win32{
	DEFINES *= __KS04_11_DLL_SOURCE__ 
}

HEADERS		+= $$TRAIN_SRC_PATH/gui_base.pri \
				ks04_11_dll.pro \
				$$TRAIN_INCLUDE_PATH/ks04_11/myclass.h
	
SOURCES    	+=  myclass.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		   
		TARGET = ks04_11_dll_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks04_11_dll
	}
} else {
	debug {				  
				   
		TARGET	= ks04_11_dll_d
	}
	release {				  
				   
		TARGET 	= ks04_11_dll
	}
}