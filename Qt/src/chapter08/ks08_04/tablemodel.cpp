/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file tablemodel.cpp
\brief  Table模型类的实现文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/1
*/
#include "tablemodel.h"

CTableModel::CTableModel(QObject *parent):QStandardItemModel(parent)
{

}

CTableModel::CTableModel(int rows, int columns, QObject *parent)
	:QStandardItemModel(rows, columns, parent)
{
}

int CTableModel::rowCount(const QModelIndex &parent) const 
{
	return QStandardItemModel::rowCount(parent);
}

int CTableModel::columnCount(const QModelIndex &parent) const
{
	return QStandardItemModel::columnCount(parent);
}

QVariant CTableModel::headerData(int section, 
								Qt::Orientation orientation, 
								int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal)	{
			if (section == 0)	{
				return tr("attribute");
			}
			else{
				return tr("value");
			}
		}
		else {
			return QVariant(QString::null);
		}
	}
	return QStandardItemModel::headerData(section, orientation, role);
}

bool CTableModel::setHeaderData(int section, 
								Qt::Orientation orientation, 
								const QVariant &value,
								int role)
{
	return QStandardItemModel::setHeaderData(section, orientation, value, role);
}


Qt::ItemFlags CTableModel::flags(const QModelIndex &dataIndex) const
{
	Qt::ItemFlags itemFlags = Qt::ItemIsEnabled;

	if (1 == dataIndex.column()) {
		if (dataIndex.parent().isValid()) {// 是子数据项
			itemFlags =
				Qt::ItemFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
		}
		else {// 是根数据项
			itemFlags = (hasChildren(index(dataIndex.row(), 0, dataIndex.parent()))
				? Qt::ItemIsEnabled // 有子数据项，则本身不允许编辑
				: Qt::ItemFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable));
		}
	}
	return itemFlags;
}


QVariant CTableModel::data(const QModelIndex &index, int role) const
{
	QModelIndex idxParent = index.parent().isValid()
		? index.parent()
		: index;
	QVariant var;
	if (index.column() == 0) { // 第0列无需特殊处理
		var = QStandardItemModel::data(index, role);
		return var;
	}
	if (Qt::EditRole == role) {
		var = QStandardItemModel::data(index, Qt::EditRole);
		return var;
	}
	else if (Qt::DisplayRole == role) {
		var = QStandardItemModel::data(index, Qt::EditRole);
		switch (idxParent.row())
		{
		case EAttr_Checked:
			var = (var.toBool() ? "yes" : "no");
			break;
		case EAttr_LastOneFlag:
			var = (var.toInt() ? "Y" : "N");
			break;
		case Eattr_Animate: 
			if (idxParent == index) {// "动画"

			}
			else if (index.row() == (Eattr_AnimateSpeed)) {// "动画速度"
				CTableModel::EAnimateSpeed animateSpeed =
					static_cast<CTableModel::EAnimateSpeed>(var.toInt());
				switch (animateSpeed)
				{
				case EAnimateSpeed_Slow:
					var = QString::fromLocal8Bit("慢速");
					break;
				case EAnimateSpeed_Normal:
					var = QString::fromLocal8Bit("中速");
					break;
				case EAnimateSpeed_Fast:
					var = QString::fromLocal8Bit("快速");
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	return var;
}

bool CTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (Qt::EditRole == role) {
		QStandardItemModel::setData(index,value, role);

		return true;
	}	
	return false;
}
