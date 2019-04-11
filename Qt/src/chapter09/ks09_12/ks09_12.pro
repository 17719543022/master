include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt

QT			+= widgets xml

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks09_12

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/

TRANSLATIONS += $$TRAIN_SRC_PATH/translations/ks09_12.ts

#FORMS 		+= dialogbase.ui
				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks09_12.pro \
				textedit.h \
				mainwindow.h \
				listwidget.h \
				city.h \
				province.h \
				country.h \
				treeview.h \
				serialize.h \
				logevt.h \
				logdockwidget.h
				   
	
SOURCES    +=  main.cpp \
				textedit.cpp \
				mainwindow.cpp \
				listwidget.cpp \
				city.cpp \
				province.cpp \
				country.cpp \
				treeview.cpp \
				logevt.cpp \
				logdockwidget.cpp
				
RESOURCES	+= ks09_12.qrc
				
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {		
		LIBS += -lbasedll_d
		TARGET = ks09_12_d
	}
	CONFIG(release, debug|release) {			   
		LIBS += -lbasedll
		TARGET	= ks09_12
	}
} else {
	debug {		
		LIBS += -lbasedll_d
		TARGET	= ks09_12_d
	}
	release {
		LIBS += -lbasedll
		TARGET 	= ks09_12
	}
}