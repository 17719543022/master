/********************************************************************************
** Form generated from reading UI file 'dialogbase.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGBASE_H
#define UI_DIALOGBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CDialogBase
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QFontComboBox *fontComboBox;
    QComboBox *cbFontSize;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *CDialogBase)
    {
        if (CDialogBase->objectName().isEmpty())
            CDialogBase->setObjectName(QStringLiteral("CDialogBase"));
        CDialogBase->resize(525, 447);
        gridLayout_2 = new QGridLayout(CDialogBase);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fontComboBox = new QFontComboBox(CDialogBase);
        fontComboBox->setObjectName(QStringLiteral("fontComboBox"));

        horizontalLayout->addWidget(fontComboBox);

        cbFontSize = new QComboBox(CDialogBase);
        cbFontSize->setObjectName(QStringLiteral("cbFontSize"));

        horizontalLayout->addWidget(cbFontSize);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(CDialogBase);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        gridLayout_2->addLayout(horizontalLayout_2, 3, 0, 1, 1);

        plainTextEdit = new QPlainTextEdit(CDialogBase);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(14);
        plainTextEdit->setFont(font);

        gridLayout_2->addWidget(plainTextEdit, 0, 0, 1, 1);


        retranslateUi(CDialogBase);
        QObject::connect(buttonBox, SIGNAL(accepted()), CDialogBase, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CDialogBase, SLOT(reject()));

        QMetaObject::connectSlotsByName(CDialogBase);
    } // setupUi

    void retranslateUi(QDialog *CDialogBase)
    {
        CDialogBase->setWindowTitle(QApplication::translate("CDialogBase", "Dialog", 0));
        cbFontSize->clear();
        cbFontSize->insertItems(0, QStringList()
         << QApplication::translate("CDialogBase", "8", 0)
         << QApplication::translate("CDialogBase", "10", 0)
         << QApplication::translate("CDialogBase", "12", 0)
         << QApplication::translate("CDialogBase", "16", 0)
         << QApplication::translate("CDialogBase", "24", 0)
         << QApplication::translate("CDialogBase", "32", 0)
         << QApplication::translate("CDialogBase", "64", 0)
        );
        plainTextEdit->setPlainText(QApplication::translate("CDialogBase", "This is a signal/slot demo!\n"
"Please Enjoy!", 0));
    } // retranslateUi

};

namespace Ui {
    class CDialogBase: public Ui_CDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGBASE_H
