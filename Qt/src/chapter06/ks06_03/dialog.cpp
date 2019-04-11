/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief	
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 

*/
#include "dialog.h"
#include <QComboBox>
#include <iostream>

using std::cout;
using std::endl;

enum EUserType {
	EUserType_Invalid=0,// 无效
	EUserType_Admin,	// 管理员
	EUserType_User,		// 普通用户
	EUserType_Guest,	// guest用户
	EUserType_Other,	// guest用户

	EUserType_Max,		// 枚举最大值
};
CDialog::CDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);

	ui.cbRole->addItem("user", static_cast<int>(EUserType_User));

	ui.cbRole->addItem("guest");
	ui.cbRole->setItemData(1, static_cast<int>(EUserType_Guest));

	ui.cbRole->addItem(QIcon(":/images/user.png"), "other", static_cast<int>(EUserType_Other));
	
	QStringList strList;
	strList << "maintain" << "security" << "owner";
	ui.cbRole->addItems(strList);
	
	ui.cbRole->insertSeparator(2);

	ui.cbRole->insertItem(0, "admin", static_cast<int>(EUserType_Admin));

	connect(ui.cbRole, SIGNAL(currentIndexChanged(int)), 
		this, SLOT(slot_roleChanged(int)));
	connect(ui.btnPopup, SIGNAL(clicked()),
		this, SLOT(slot_popup()));
}

void CDialog::slot_popup()
{
	ui.cbRole->showPopup();
}

void CDialog::slot_roleChanged(int)
{
	int idx = ui.cbRole->currentIndex();
	QString str = ui.cbRole->currentText();
	int nUserType = ui.cbRole->itemData(idx).toInt();
	//int nData = ui.cbRole->currentData(Qt::EditRole).toInt();
	EUserType userType = static_cast<EUserType>(nUserType);
	switch (userType) {
	case EUserType_Admin:
		cout << "admin" << endl;
		cout << "current user:" << str.toLocal8Bit().data()<<endl;
		break;
	default:
		break;
	}
}
