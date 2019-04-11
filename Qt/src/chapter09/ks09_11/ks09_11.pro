include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt

QT			+= widgets xml

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks09_11

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/

TRANSLATIONS += $$TRAIN_SRC_PATH/translations/ks09_11.ts

#FORMS 		+= dialogbase.ui
				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks09_11.pro \
				textedit.h \
				mainwindow.h \
				listwidget.h \
				city.h \
				province.h \
				country.h \
				treeview.h \
				serialize.h
				   
	
SOURCES    +=  main.cpp \
				textedit.cpp \
				mainwindow.cpp \
				listwidget.cpp \
				city.cpp \
				province.cpp \
				country.cpp \
				treeview.cpp
				
RESOURCES	+= ks09_11.qrc
				
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {		
		LIBS += -lbasedll_d
		TARGET = ks09_11_d
	}
	CONFIG(release, debug|release) {			   
		LIBS += -lbasedll
		TARGET	= ks09_11
	}
} else {
	debug {		
		LIBS += -lbasedll_d
		TARGET	= ks09_11_d
	}
	release {
		LIBS += -lbasedll
		TARGET 	= ks09_11
	}
}