/********************************************************************************
** Form generated from reading UI file 'application.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATION_H
#define UI_APPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApplicationClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPlainTextEdit *plainTextEdit;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ApplicationClass)
    {
        if (ApplicationClass->objectName().isEmpty())
            ApplicationClass->setObjectName(QStringLiteral("ApplicationClass"));
        ApplicationClass->resize(600, 400);
        centralWidget = new QWidget(ApplicationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setCheckable(false);
        pushButton->setChecked(false);
        pushButton->setAutoDefault(false);
        pushButton->setFlat(false);

        gridLayout->addWidget(pushButton, 2, 2, 1, 1);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setTabChangesFocus(true);
        plainTextEdit->setReadOnly(true);
        plainTextEdit->setBackgroundVisible(false);

        gridLayout->addWidget(plainTextEdit, 0, 2, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 2, 1, 1);

        ApplicationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ApplicationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        ApplicationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ApplicationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ApplicationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ApplicationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ApplicationClass->setStatusBar(statusBar);

        retranslateUi(ApplicationClass);

        QMetaObject::connectSlotsByName(ApplicationClass);
    } // setupUi

    void retranslateUi(QMainWindow *ApplicationClass)
    {
        ApplicationClass->setWindowTitle(QApplication::translate("ApplicationClass", "Application", 0));
        pushButton->setText(QApplication::translate("ApplicationClass", "\345\267\262\351\230\205\350\257\273\345\271\266\345\220\214\346\204\217\346\255\244\345\215\217\345\256\232", 0));
        plainTextEdit->setPlainText(QApplication::translate("ApplicationClass", "       	                        \344\277\235\345\257\206\345\215\217\345\256\232\n"
"    \346\240\271\346\215\256\344\270\255\345\205\264\351\200\232\350\256\257\350\202\241\344\273\275\346\234\211\351\231\220\350\264\243\344\273\273\345\205\254\345\217\270\350\246\201\346\261\202\357\274\214\345\205\254\345\217\270\345\221\230\345\267\245\345\277\205\351\241\273\351\201\265\344\273\216\344\273\245\344\270\213\344\277\235\345\257\206\350\247\204\345\210\231\357\274\214\345\246\202\346\234\211\350\277\235\345\217\215\346\204\277\346\216\245\345\217\227\345\233\275\345\256\266\346\263\225\345\276\213\345\210\266\350\243\201\357\274\232\n"
"    1. \344\270\215\345\276\227\344\274\240\346\222\255\345\205\254\345\217\270\344\273\243\347\240\201\343\200\201\346\226\207\346\241\243\345\210\260\344\272\222\350\201\224\347\275\221\357\274\233\n"
"    2. \344\270\215\345\276\227\346\263\204\351\234\262\345\205\254\345\217\270\345\225\206\344\270\232\346\234\272\345\257\206\343\200\201\346\212\225\346\240\207\346\226\271"
                        "\346\241\210\343\200\202\n"
"    \350\257\267\344\273\224\347\273\206\351\230\205\350\257\273\346\234\254\345\215\217\345\256\232\345\271\266\347\255\276\345\220\215\346\217\220\344\272\244\343\200\202", 0));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("ApplicationClass", "\350\257\267\347\255\276\345\220\215", 0));
    } // retranslateUi

};

namespace Ui {
    class ApplicationClass: public Ui_ApplicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_H
