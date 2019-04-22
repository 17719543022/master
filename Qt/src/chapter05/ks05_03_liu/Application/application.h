#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtWidgets/QMainWindow>
#include "ui_application.h"

class Application : public QMainWindow
{
	Q_OBJECT

public:
	Application(QWidget *parent = 0);
	~Application();

private slots:
	void onSumbitted();

private:
	Ui::ApplicationClass ui;
};

#endif // APPLICATION_H
