include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG += console

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks04_15

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks04_15

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks04_15.pro 	\
				country.h \
				province.h \
				city.h
	
SOURCES    +=  main.cpp 	\
				country.cpp \
				province.cpp \
				city.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {	
		LIBS	+= -lbasedll_d

		TARGET = ks04_15_d
	}
	CONFIG(release, debug|release) {			   
		LIBS	+= -lbasedll

		TARGET	= ks04_15
	}
} else {
	debug {
		LIBS	+= -lbasedll_d
	
		TARGET	= ks04_15_d
	}
	release {
		LIBS	+= -lbasedll
		
		TARGET 	= ks04_15
	}
}