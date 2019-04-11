include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_06

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks05_06

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_06.pro \
				address.h	 \		
				dialog.h \
				myobject.h

	
SOURCES    +=  main.cpp \
				address.cpp	 \		
				dialog.cpp \
				myobject.cpp

				
FORMS		+= address.ui \
				dialogbase.ui 

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
				   
		TARGET = ks05_06_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks05_06
	}
} else {
	debug {
		
		TARGET	= ks05_06_d
	}
	release {			   
		
		TARGET 	= ks05_06
	}
}