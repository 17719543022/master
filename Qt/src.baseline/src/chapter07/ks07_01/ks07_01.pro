include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG		+= qt

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks07_01

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks07_01

FORMS 		+= dialogbase.ui \
				customwidgetbase.ui

				
HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks07_01.pro \
			    dialog.h \
				customwidget.h
				   
	
SOURCES    +=  main.cpp  \
			   dialog.cpp \
			   customwidget.cpp
				
RESOURCES	+= ks07_01.qrc
				
OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {				   
		TARGET = ks07_01_d
	}
	CONFIG(release, debug|release) {			   
		TARGET	= ks07_01
	}
} else {
	debug {		
		TARGET	= ks07_01_d
	}
	release {
		TARGET 	= ks07_01
	}
}