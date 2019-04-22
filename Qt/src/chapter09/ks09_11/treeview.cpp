/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file treeview.cpp
\brief treeview实现文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/1
*/

#include <QMouseEvent>
#include <QStandardItemModel>

#include "treeview.h"

void CTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
	QPoint pos = event->pos();
	QPersistentModelIndex index = indexAt(pos);
	QAbstractItemModel* pModel = model();
	if (NULL != pModel) {
		QStandardItemModel* pStandardModel = dynamic_cast<QStandardItemModel*>(model());
		if (NULL != pStandardModel)	{
			QString str = pStandardModel->data(index).toString();
			emit itemDoubleClicked(str);
		}
	}

	QTreeView::mousePressEvent(event);
}