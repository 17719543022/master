include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= lib
LANGUAGE	= C++

CONFIG		+= dll
QT			+= xml

TEMPDIR		= $$TRAIN_OBJ_PATH/base/basedll

DESTDIR     = $$TRAIN_LIB_PATH
DLLDESTDIR  = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/base/basedll

win32{
	DEFINES *= __BASEDLL_SOURCE__ 
}

HEADERS		+= $$TRAIN_SRC_PATH/gui_base.pri \
				basedll.pro \
				$$TRAIN_INCLUDE_PATH/base/basedll/baseapi.h \
				$$TRAIN_INCLUDE_PATH/base/basedll/iniconfig.h \
				$$TRAIN_INCLUDE_PATH/base/basedll/fileattribute.h 
				
				
SOURCES    	+=  basedll.cpp \
				fileattribute.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		   
		TARGET = basedll_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= basedll
	}
} else {
	debug {				  
				   
		TARGET	= basedll_d
	}
	release {				  
				   
		TARGET 	= basedll
	}
}