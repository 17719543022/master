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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApplicationClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QFontComboBox *fontComboBox;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ApplicationClass)
    {
        if (ApplicationClass->objectName().isEmpty())
            ApplicationClass->setObjectName(QStringLiteral("ApplicationClass"));
        ApplicationClass->resize(306, 293);
        centralWidget = new QWidget(ApplicationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 2);

        fontComboBox = new QFontComboBox(centralWidget);
        fontComboBox->setObjectName(QStringLiteral("fontComboBox"));

        gridLayout->addWidget(fontComboBox, 1, 0, 1, 1);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEditable(false);

        gridLayout->addWidget(comboBox, 1, 1, 1, 1);

        ApplicationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ApplicationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 306, 23));
        ApplicationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ApplicationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ApplicationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ApplicationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ApplicationClass->setStatusBar(statusBar);

        retranslateUi(ApplicationClass);

        comboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ApplicationClass);
    } // setupUi

    void retranslateUi(QMainWindow *ApplicationClass)
    {
        ApplicationClass->setWindowTitle(QApplication::translate("ApplicationClass", "Application", 0));
        plainTextEdit->setPlainText(QApplication::translate("ApplicationClass", "\345\257\271\357\274\214\345\217\215\346\255\243\346\210\221\345\225\245\344\271\237\344\270\215\344\274\232\343\200\202\343\200\202\343\200\202", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("ApplicationClass", "8", 0)
         << QApplication::translate("ApplicationClass", "16", 0)
         << QApplication::translate("ApplicationClass", "24", 0)
         << QApplication::translate("ApplicationClass", "32", 0)
         << QApplication::translate("ApplicationClass", "40", 0)
         << QApplication::translate("ApplicationClass", "48", 0)
         << QApplication::translate("ApplicationClass", "56", 0)
         << QApplication::translate("ApplicationClass", "64", 0)
        );
        comboBox->setCurrentText(QApplication::translate("ApplicationClass", "8", 0));
    } // retranslateUi

};

namespace Ui {
    class ApplicationClass: public Ui_ApplicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_H
