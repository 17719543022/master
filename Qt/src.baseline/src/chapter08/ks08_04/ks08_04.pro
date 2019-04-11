include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT += widgets

#CONFIG += console

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter04/ks08_04

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks08_04

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks08_04.pro 	\
				delegate.h		\
				tablemodel.h	\
				ceditor.h 		\
				tableview.h
	
SOURCES    +=  main.cpp 	\
				delegate.cpp \
				tablemodel.cpp \
				ceditor.cpp \
				tableview.cpp

RESOURCES += ks08_04.qrc

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {	
		LIBS	+= -lbasedll_d

		TARGET = ks08_04_d
	}
	CONFIG(release, debug|release) {			   
		LIBS	+= -lbasedll

		TARGET	= ks08_04
	}
} else {
	debug {
		LIBS	+= -lbasedll_d
	
		TARGET	= ks08_04_d
	}
	release {
		LIBS	+= -lbasedll
		
		TARGET 	= ks08_04
	}
}