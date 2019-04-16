#include "application.h"

Application::Application(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.fontComboBox, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(onFontFamilyChanged(const QFont &)));
	connect(ui.comboBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onFontSizeChanged(const QString &)));
}

Application::~Application()
{

}

void Application::onFontFamilyChanged(const QFont & font)
{
	int size = ui.comboBox->currentText().toInt();
	QFont fLocal = font;
	fLocal.setPointSize(size);
	ui.plainTextEdit->setFont(fLocal);
}

void Application::onFontSizeChanged(const QString & str)
{
	QFont font = ui.fontComboBox->currentFont();
	font.setPointSize(str.toInt());
	ui.plainTextEdit->setFont(font);
}