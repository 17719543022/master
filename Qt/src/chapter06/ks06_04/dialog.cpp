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
#include <QGridLayout>
#include <QListWidget>


CDialog::CDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);
	initialize();
}

void CDialog::initialize()
{
	ui.listWidgetLeft->setSelectionMode(QListWidget::SingleSelection); // 允许单选
	ui.listWidgetRight->setSelectionMode(QListWidget::MultiSelection);  // 允许多选

	ui.listWidgetLeft->addItem("C++");
	ui.listWidgetLeft->addItem("java");
	ui.listWidgetLeft->addItem("python");
	ui.listWidgetLeft->addItem("Rubby");
	ui.listWidgetLeft->addItem("PHP");
	ui.listWidgetLeft->addItem("C#");

	connect(ui.btn2Left, &QPushButton::clicked, 
		this, &CDialog::slot_move2Left);

	connect(ui.btn2Right, &QPushButton::clicked, 
		this, &CDialog::slot_move2Right);

	connect(ui.listWidgetLeft, &QListWidget::itemClicked,
		this, &CDialog::slot_leftItemClicked);

	connect(ui.listWidgetLeft, &QListWidget::currentItemChanged,
		this, &CDialog::slot_currentItemChanged);

	connect(ui.listWidgetLeft, &QListWidget::itemDoubleClicked,
		this, &CDialog::slot_leftItemDoubleClicked);

	connect(ui.btnDescending, &QPushButton::clicked,
		this, &CDialog::slot_Descending);

	connect(ui.btnAscending, &QPushButton::clicked,
		this, &CDialog::slot_Ascending);
}
void CDialog::slot_Ascending()
{
	ui.listWidgetRight->sortItems(Qt::AscendingOrder);
}

void CDialog::slot_Descending()
{
	ui.listWidgetRight->sortItems(Qt::DescendingOrder);

}
void CDialog::slot_leftItemDoubleClicked(QListWidgetItem *pItem)
{
	int row = ui.listWidgetLeft->row(pItem);
	ui.listWidgetLeft->takeItem(row);
	ui.listWidgetRight->addItem(pItem);
}

void CDialog::slot_leftItemClicked(QListWidgetItem *item)
{
	QString str;
	str = "My favourite program language is:" + item->text();
	ui.label->setText(str);
	
	QFont ft = item->font();
	ft.setBold(true);
	item->setFont(ft);
}
void CDialog::slot_move2Left()
{
	QListWidgetItem* pItem = NULL;

	// 得到右侧列表中当前选中的item集合。
	QList<QListWidgetItem*> selectedItems =
		ui.listWidgetRight->selectedItems();

	if (selectedItems.size() == 0)
		return;

	int row = 0;
	QList<QListWidgetItem*>::iterator iteList = selectedItems.begin();
	for (; iteList != selectedItems.end(); iteList++)
	{ // 遍历选中的项目集合
		pItem = *iteList; 
		row = ui.listWidgetRight->row(pItem); // 得到项目的序号
		ui.listWidgetRight->takeItem(row);    // 从右侧移除
		ui.listWidgetLeft->addItem(pItem);    // 添加到左侧
	}
}

void CDialog::slot_move2Right()
{
	QListWidgetItem* pItem = ui.listWidgetLeft->currentItem(); // 得到当前选中的项目
	if (NULL == pItem)
		return;
	int row = ui.listWidgetLeft->row(pItem);// 得到项目的序号
	ui.listWidgetLeft->takeItem(row);		// 从右侧移除
	ui.listWidgetRight->addItem(pItem);		// 添加到左侧
}
void CDialog::slot_currentItemChanged(QListWidgetItem * /*current*/, QListWidgetItem *previous)
{
	if (NULL != previous)	{ // 将前一次选中的项目字体恢复
		QFont ft =	previous->font();
		ft.setBold(false);
		previous->setFont(ft);
	}
}