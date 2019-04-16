#include "application.h"

Application::Application(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.fontComboBox, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(onFontFamilyChanged(const QFont &)));
}

Application::~Application()
{

}

void Application::onFontFamilyChanged(const QFont & font)
{
	ui.plainTextEdit->setFont(font);
}