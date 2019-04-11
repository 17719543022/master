include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

CONFIG += console

QT += xml

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter00/syncdir

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks04_11

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				syncdir.pro 	\
				sync.h
	
SOURCES    +=  main.cpp \
				sync.cpp

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
		LIBS	+= -lks04_11_dll_d			
				   
		TARGET = syncdir_d
	}
	CONFIG(release, debug|release) {
		LIBS	+= -lks04_11_dll				   
				   
		TARGET	= syncdir
	}
} else {
	debug {
		LIBS	+= -lks04_11_dll_d
		
		TARGET	= syncdir_d
	}
	release {
		LIBS	+= -lks04_11_dll
		
		TARGET 	= syncdir
	}
}