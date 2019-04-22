#ifndef _UIFILEDEF_H_
#define _UIFILEDEF_H_

#include <QColor>
#include <QMap>
#include <QPalette>
#include <QPoint>
#include <QString>
#include <QStringList>
#include <vector>

#include "actiondef.h"
#include "uitypedef.h"

//! ui文件中的页面控制工具
typedef struct _PageControlTool_
{
	QString						m_name;		// 名字
	QString						m_caption;	// 标题
	QString						m_icon;		// 图片名称
	QString						m_desc;		// 描述
	int							m_pageid;	// 控制页面id(仅对页面切换按钮有效)
	_PageControlTool_()
	{
		m_name = QString::null;
		m_caption = QString::null;
		m_icon = QString::null;
		m_desc = QString::null;
		m_pageid = 0;
	};
}PageContrlTool, *PPageContrlTool;

//! ui文件中的tool定义
typedef struct _DrawTool_
{
	QString						m_name;			// 名字
	QString						m_caption;		// 标题
	CUiTypeenum::EUiType		m_type;			// 类型
	QString						m_icon;			// 图片名称
	QString						m_desc;			// 描述
	QString						m_accel;		// 快捷键
	CActionenum::EDrawAction	m_Action;		// Action
	CActionenum::EDrawWidget	m_Widget;		// Widget
	QString						m_bChecked;		// checkable按钮状态
	_DrawTool_()
	{
		m_name = QString::null;
		m_caption = QString::null;
		m_icon = QString::null;
		m_type = CUiTypeenum::EMyPushButton;
		m_desc = QString::null;
		m_accel = QString::null;
		m_Action = CActionenum::EAction_Copy;
		m_Widget = CActionenum::EToolButton_Format;
		m_bChecked = QString::null;
	};
}DrawTool,*PDrawTool;

//! tool位置信息定义
typedef struct _ToolPos_
{
	QString m_toolName;		//名字
	eUiToolType	eToolType;	//工具类型
	qint32 m_row;			//行号
    qint32 m_col;			//列号
    qint32 m_rowSpan;		//行数
    quint32 m_colSpan;		//列数
    quint32 m_length;		//长度（仅为分隔符独有的属性）
	Qt::Alignment m_align;	//对齐方式
	QString m_default;			//是否为默认功能(仅对二级菜单起作用)
	_ToolPos_()
	{
		m_toolName=QString::null;
		eToolType = e_SingleTool;
		m_row = 0;
		m_col = 0;
		m_rowSpan = 0;
		m_colSpan = 0;
		m_length = 0;
		m_align = 0;
		m_default = QString::null;
	}
}ToolPos,*PToolPos;

//! ui文件工具面板定义
typedef struct _DrawToolPanel_
{
	QString m_name;			//名字
    quint32	m_id;			//ID
	QString m_caption;		//标题
	QString m_icon;			//图片名字
	qint32  m_hSpacing;		//水平间距
    qint32	m_vSpacing;		//垂直间距
	std::vector<PToolPos> m_tools;	//工具列表

	_DrawToolPanel_()
	{
		m_name = QString::null;
		m_caption = QString::null;
		m_icon = QString::null;
		m_id = 0;
		m_hSpacing = 1;
		m_vSpacing = 1;
		m_tools.clear();
	}
}DrawToolPanel, *PDrawToolPanel;

//! ui文件工具页面定义
typedef struct _DrawToolPage_
{
	QString m_name;		// 名称
	quint32 m_id;		// ID
	QString m_caption;	// 标题
	QString m_icon;		// 图片名字 
	QStringList m_panels;	//工具面板列表
	_DrawToolPage_()
	{
		m_name = QString::null;
		m_id = 0;
		m_caption = QString::null;
		m_icon = QString::null;
		m_panels.clear();
	};
}DrawToolPage, *PDrawToolPage;

//! 多选项工具定义
typedef struct _MultiTool_
{
	QString							m_name;
	CUiTypeenum::EUiGroupType		m_type;		// 类型
	QString							m_caption;	// 标题
	QString							m_icon;		// icon
	std::vector<PToolPos>			m_tools;	//选项列表
	QString							m_desc;		// 描述

	_MultiTool_()
	{
		m_name = QString::null;
		m_type = CUiTypeenum::EGroupBar_Qt;
		m_caption = QString::null;
		m_icon = QString::null;
		m_tools.clear();
		m_desc = QString::null;
	}
}MultiTool,*PMultiTool;

//! 页面切换工具：key值为切换按钮名字，value值为按钮信息
typedef QMap<QString, PPageContrlTool> PPageControlToolMap;

//! 绘图工具控件：key值为工具名字，value值为工具信息
typedef QMap<QString, PDrawTool> PDrawToolMap;

//! 绘图工具面板：key值为工具面板名字，value值为工具面板信息
typedef QMap<QString, PDrawToolPanel> PDrawToolPanelMap;

//! 绘图工具页面：key值为工具页名字，value值为工具页信息
typedef QMap<QString, PDrawToolPage> PDrawToolPageMap;

//! 绘图工具多选项工具：key值为多选项工具名字,value值为工具信息
typedef QMap<QString, PMultiTool> PMultiToolMap;


#endif