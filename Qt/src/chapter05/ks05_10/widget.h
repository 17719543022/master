/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: widget.h
\brief  CWidget类定义头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#ifndef WIDGET_H
#define WIDGET_H

#include "ui_widgetbase.h" // 头文件名称来自: dialogbase.ui  ---> ui_widgetbase.h


// 第一个父类的名称来自ui文件中对话框的类名：对象查看器中的类名
// 第二个父类的名称来自ui文件中对话框基类的名称(objeceName属性)： CWidgetBase
class CWidget : public QWidget, public Ui::CWidgetBase
{
	Q_OBJECT
public:
	CWidget(QWidget* pParent);
	~CWidget();

protected:

private slots:
	void on_fontFamilyChanged(const QFont &font);
	void on_fontSizeChanged(int);

};

#endif  // WIDGET_H