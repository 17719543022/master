include ($$(TRAINDEVHOME)/src/gui_base.pri)

TEMPLATE	= app
LANGUAGE	= C++

QT			+= widgets

TEMPDIR		= $$TRAIN_OBJ_PATH/chapter05/ks05_05

DESTDIR     = $$TRAIN_BIN_PATH

INCLUDEPATH += $$TRAIN_INCLUDE_PATH/ks05_05

HEADERS		+=  $$TRAIN_SRC_PATH/gui_base.pri \
				ks05_05.pro \
				address.h	 \		
				dialog.h \
				simpledialog.h

	
SOURCES    +=  main.cpp \
				address.cpp	 \		
				dialog.cpp \
				simpledialog.cpp

				
FORMS		+= address.ui \
				dialogbase.ui \
				simpledialogbase.ui

OBJECTS_DIR = $$TEMPDIR
MOC_DIR		= $$TEMPDIR/moc
UI_DIR		= $$TEMPDIR/ui

debug_and_release {
	CONFIG(debug, debug|release) {
				   
		TARGET = ks05_05_d
	}
	CONFIG(release, debug|release) {			   
				   
		TARGET	= ks05_05
	}
} else {
	debug {
		
		TARGET	= ks05_05_d
	}
	release {			   
		
		TARGET 	= ks05_05
	}
}