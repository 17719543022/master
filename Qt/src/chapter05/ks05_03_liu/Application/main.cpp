#include "application.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Application w;
	w.show();
	return a.exec();
}
