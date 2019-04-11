/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file tablemodel.h
\brief  Table模型类的头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/1
*/
#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QStandardItemModel>


class CTableModel : public QStandardItemModel
{
	Q_OBJECT
public:
	/// 各行所代表的意义
	enum EAttrIndex {
		EAttr_Id = 0,		// id
		EAttr_Descrition,	// 描述
		EAttr_Checked,		// 是否已验证
		EAttr_LastOneFlag,	// 是否最后一个
		Eattr_AnimateSpeed,	// 速度

		Eattr_Max,
	};

	/// 速度枚举值
	enum EAnimateSpeed {
		EAnimateSpeed_Slow = 0, // 慢速
		EAnimateSpeed_Normal,	// 中速
		EAnimateSpeed_Fast,		// 快速

		EAnimateSpeed_Max,
	};
public:
	explicit CTableModel(QObject *parent = 0);
	CTableModel(int rows, int columns, QObject *parent = nullptr);

	/**
	* @brief  获取parent的子数据项的行数
	* @param[in] index 数据项序号
	* @return 行数。
	*/
	int rowCount(const QModelIndex &parent) const override;
	/**
	* @brief 获取parent的子数据项的列数
	* @param[in] index 数据项序号
	* @return 列数。
	*/
	int columnCount(const QModelIndex &parent) const override;
	/**
	* @brief  获取行、列标题
	* @param[in] section 行/列序号
	* @param[in] orientation 方向：行/列
	* @return 指定行/列的标题。
	*/
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	/**
	* @brief  设置行、列标题
	* @param[in] section 行/列序号
	* @param[in] orientation 方向：行/列
	* @return 指定行/列的标题。
	*/
	virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
		int role = Qt::EditRole);
	
	/**
	* @brief  设置某数据项的标志
	* @param[in] index 数据项序号
	* @return 指定数据项的标志
	*/
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	/**
	* @brief  获取数据
	* @param[in] index 数据项序号
	* @param[in] role 角色，见setData(). 取值范围：Qt::EditRole, Qt::DispalyRole.
	* @return 指定的数据。
	*/
	QVariant data(const QModelIndex &index, int role) const override;
	/**
	* @brief  设置数据
	* @param[in] index 序号
	* @param[in] value 数据
	* @param[in] role 角色
	* @return true:成功, false:失败。
	*/
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

private:
};

#endif
