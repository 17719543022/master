include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= lib
LANGUAGE	= C++

CONFIG += dll


TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks04_19/dll

DESTDIR     = $$TRAIN_LIB_PATH
DLLDESTDIR  = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks04_19

win32{
	DEFINES *= __KS04_19_DLL_SOURCE__ 
}

HEADERS		+= $$TRAIN_SRC_PATH/gui_base.pri \
				ks04_19_dll.pro \
				$$TRAIN_INCLUDE_PATH/ks04_19/myclass.h
	
SOURCES    	+=  myclass.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		LIBS	+= -lks04_19_config_dll_d		   

		TARGET = ks04_19_dll_d
	}
	CONFIG(release, debug|release) {			   
		LIBS	+= -lks04_19_config_dll
		TARGET	= ks04_19_dll
	}
} else {
	debug {				  
		LIBS	+= -lks04_19_config_dll_d		   				   
		TARGET	= ks04_19_dll_d
	}
	release {				  
		LIBS	+= -lks04_19_config_dll
		TARGET 	= ks04_19_dll
	}
}