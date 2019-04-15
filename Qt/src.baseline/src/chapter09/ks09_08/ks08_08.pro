include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks08_08

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/

TRANSLATIONS += $$TRAIN_SRC_PATH/translations/ks08_08.ts

#FORMS 		+= dialogbase.ui
				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks08_08.pro \
				textedit.h \
				mainwindow.h
				   
	
SOURCES    +=  main.cpp \
				textedit.cpp \
				mainwindow.cpp
				
RESOURCES	+= ks08_08.qrc
				
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {		
		LIBS += -lbasedll_d
		TARGET = ks08_08_d
	}
	CONFIG(release, debug|release) {			   
		LIBS += -lbasedll
		TARGET	= ks08_08
	}
} else {
	debug {		
		LIBS += -lbasedll_d
		TARGET	= ks08_08_d
	}
	release {
		LIBS += -lbasedll
		TARGET 	= ks08_08
	}
}