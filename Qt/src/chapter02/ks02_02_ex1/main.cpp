#include <iostream>
#include "dialog.h"
#include <QApplication>
using namespace std;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	Dialog dlg;
	dlg.exec();

	return 0;
}