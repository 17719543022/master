include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= lib
LANGUAGE	= C++

CONFIG		+= dll 
QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter12/ks12_02/action_addline

DESTDIR     = $$TRAIN_LIB_PATH
DLLDESTDIR  = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/chapter12/ks12_02/action_addline

win32{
	DEFINES *= __ACTION_ADDLINE_SOURCE__ 
}

HEADERS		+= $$TRAIN_SRC_PATH/gui_base.pri \
				action_addline.pro \
				action_addline.h  
				
				
SOURCES    	+=  action_addline.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		   
		TARGET = action_addline_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= action_addline
	}
} else {
	debug {				  
				   
		TARGET	= action_addline_d
	}
	release {				  
				   
		TARGET 	= action_addline
	}
}