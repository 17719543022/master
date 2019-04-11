TEMPLATE	= app
LANGUAGE	= C++
CONFIG		+= qt
QT         += widgets

TARGET     	= ks05_01

FORMS 		+= dialogbase.ui

HEADERS		+= ks.pro \
			   dialog.h 
	
	
SOURCES    += \
			    main.cpp \
				dialog.cpp
