include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_10

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/base/basedll

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_10.pro \
				widget.h \
				maindialog.h
	
SOURCES    +=  main.cpp \
				widget.cpp \
				maindialog.cpp
				
FORMS		+= widgetbase.ui \
			   maindialogbase.ui

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		LIBS   += -lbasedll_d   
		TARGET = ks05_10_d
	}
	CONFIG(release, debug|release) {			   
		LIBS   += -lbasedll				   
		TARGET	= ks05_10
	}
} else {
	debug {
		LIBS   += -lbasedll_d		
		TARGET	= ks05_10_d
	}
	release {			   
		LIBS   += -lbasedll		
		TARGET 	= ks05_10
	}
}