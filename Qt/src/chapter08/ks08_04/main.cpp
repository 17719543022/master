/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file main.cpp
\brief delegate example main()函数
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/1
*/


#include <QApplication>
#include <QFile>
#include <QHeaderView>

#include "delegate.h"
#include "tablemodel.h"
#include "treeview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CTableModel model(CTableModel::Eattr_Max, 2);
	CTreeView treeView;
	treeView.setAlternatingRowColors(true);
	treeView.setModel(&model); // 将模型视图建立关联
	
	QFile file(":/qss/treeview.qss");
	bool bok = file.open(QFile::ReadOnly);
	if (bok) {
		QString styleSheet = QString::fromLatin1(file.readAll());
		treeView.setStyleSheet(styleSheet);
	}
   // tableView.horizontalHeader()->setStretchLastSection(true);

    CDelegate delegate;
	treeView.setItemDelegate(&delegate); // 为视图设置代理
	QModelIndex index;

    for (int row = 0; row < CTableModel::Eattr_Max; ++row) {
		// 先填写第0列
        index = model.index(row, 0, QModelIndex());
		if (CTableModel::EAttr_Id == row) {
			model.setData(index, "Id");
		}
		else if (CTableModel::EAttr_Descrition == row)	{
			model.setData(index, QString::fromLocal8Bit("描述"));
		}
		else if (CTableModel::EAttr_Checked == row)	{
			model.setData(index, QString::fromLocal8Bit("验证标志"));
		}
		else if (CTableModel::EAttr_LastOneFlag == row)	{
			model.setData(index, QString::fromLocal8Bit("是否最后一个"));
		}
		else if (CTableModel::Eattr_Animate == row)	{
			model.setData(index, QString::fromLocal8Bit("动画"));
			model.insertRows(0, 2, index);		// 插入两个子数据项
			model.insertColumns(0, 2, index);	// 插入两列(属性名、属性值)
			model.setData(model.index(CTableModel::Eattr_AnimateSpeed, 0, index), QString::fromLocal8Bit("速度"));
			model.setData(model.index(CTableModel::Eattr_AnimateType, 0, index), QString::fromLocal8Bit("类型"));
		}
		
		// 再填写第1列
		index = model.index(row, 1, QModelIndex());
		if (CTableModel::EAttr_Id == row) {
			model.setData(index, 0);
		}
		else if (CTableModel::EAttr_Descrition == row) {
			model.setData(index, QString::fromLocal8Bit("备注"));
		}
		else if (CTableModel::EAttr_Checked == row) {
			model.setData(index, false);
		}
		else if (CTableModel::EAttr_LastOneFlag == row) {
			model.setData(index, QVariant(static_cast<int>(Qt::Checked)));
		}
		else if (CTableModel::Eattr_Animate == row) {
			index = model.index(row, 0, QModelIndex());
			model.setData(model.index(0, 1,index), QVariant(static_cast<int>(CTableModel::EAnimateSpeed_Normal)));
			model.setData(model.index(1, 1, index), 1);
		}
    }
	// tmp
	//for (int row = 0; row < CTableModel::Eattr_Max; ++row) {
	//	index = model.index(row, 1);
	//	tableView.openPersistentEditor(index);
	//}
	treeView.setWindowTitle(QObject::tr("Delegate Example"));
	treeView.show();
    return app.exec(); // 将app运行起来
}


