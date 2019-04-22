#include "application.h"
#include <qdatetime.h>
#include <qerrormessage.h>
#include <qmessagebox.h>

Application::Application(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.lineEdit->setFocus();

	connect(ui.lineEdit, SIGNAL(returnPressed()), ui.pushButton, SIGNAL(clicked()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(onSumbitted()));
}

Application::~Application()
{

}

void Application::onSumbitted()
{
	if(ui.lineEdit->text().length() == 0){
		QErrorMessage *error = new QErrorMessage; 
		error->setWindowTitle(QString::fromLocal8Bit("����")); 
		error->showMessage(QString::fromLocal8Bit("ǩ��У�����")); 

		return;
	}
	else
	{
		QString content = QString::fromLocal8Bit("ȷ����������") + ui.lineEdit->text();
		QMessageBox::information(NULL, QString::fromLocal8Bit("��Ϣȷ��"), content);
	}

	QString str = "\n\n\n\n\t\t\t\t\t" + ui.lineEdit->text();
	QDateTime local(QDateTime::currentDateTime());
	QDate date = local.date();
	str = str + "\n\t\t\t\t\t" + date.toString();
	ui.plainTextEdit->appendPlainText(str);
	
	ui.lineEdit->clear();
	ui.pushButton->setDisabled(true);
}
