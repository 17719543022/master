include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_04

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks05_04

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_04.pro \
				mainwindow.h	 \		
				mdichild.h 

	
SOURCES    +=  main.cpp \
				mainwindow.cpp	 \		
				mdichild.cpp 
				
RESOURCES    = ks05_04.qrc

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
				   
		TARGET = ks05_04_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks05_04
	}
} else {
	debug {
		
		TARGET	= ks05_04_d
	}
	release {			   
		
		TARGET 	= ks05_04
	}
}