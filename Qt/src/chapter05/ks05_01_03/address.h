/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: address.h
\brief  CWidgetAddress类的定义文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#ifndef ADDRESS_H
#define ADDRESS_H

#include "ui_address.h" // 头文件名称来自: address.ui  ---> ui_address.h


// 第一个父类的名称来自ui文件中对话框的类名：对象查看器中的类名
// 第二个父类的名称来自ui文件中对话框基类的名称(objeceName属性)： CWidgetAddressBase
class CWidgetAddress : public QWidget, public Ui::CWidgetAddressBase
{
	Q_OBJECT
public:
	CWidgetAddress(QWidget* pParent);
	~CWidgetAddress();

Q_SIGNALS:
	void addressSaved(const QString& strAddress);

public slots:
	void on_addressSaved();
};

#endif  // ADDRESS_H