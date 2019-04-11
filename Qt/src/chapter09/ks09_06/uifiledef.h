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

//! ui�ļ��е�ҳ����ƹ���
typedef struct _PageControlTool_
{
	QString						m_name;		// ����
	QString						m_caption;	// ����
	QString						m_icon;		// ͼƬ����
	QString						m_desc;		// ����
	int							m_pageid;	// ����ҳ��id(����ҳ���л���ť��Ч)
	_PageControlTool_()
	{
		m_name = QString::null;
		m_caption = QString::null;
		m_icon = QString::null;
		m_desc = QString::null;
		m_pageid = 0;
	};
}PageContrlTool, *PPageContrlTool;

//! ui�ļ��е�tool����
typedef struct _DrawTool_
{
	QString						m_name;			// ����
	QString						m_caption;		// ����
	CUiTypeenum::EUiType		m_type;			// ����
	QString						m_icon;			// ͼƬ����
	QString						m_desc;			// ����
	QString						m_accel;		// ��ݼ�
	CActionenum::EDrawAction	m_Action;		// Action
	CActionenum::EDrawWidget	m_Widget;		// Widget
	QString						m_bChecked;		// checkable��ť״̬
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

//! toolλ����Ϣ����
typedef struct _ToolPos_
{
	QString m_toolName;		//����
	eUiToolType	eToolType;	//��������
	qint32 m_row;			//�к�
    qint32 m_col;			//�к�
    qint32 m_rowSpan;		//����
    quint32 m_colSpan;		//����
    quint32 m_length;		//���ȣ���Ϊ�ָ������е����ԣ�
	Qt::Alignment m_align;	//���뷽ʽ
	QString m_default;			//�Ƿ�ΪĬ�Ϲ���(���Զ����˵�������)
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

//! ui�ļ�������嶨��
typedef struct _DrawToolPanel_
{
	QString m_name;			//����
    quint32	m_id;			//ID
	QString m_caption;		//����
	QString m_icon;			//ͼƬ����
	qint32  m_hSpacing;		//ˮƽ���
    qint32	m_vSpacing;		//��ֱ���
	std::vector<PToolPos> m_tools;	//�����б�

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

//! ui�ļ�����ҳ�涨��
typedef struct _DrawToolPage_
{
	QString m_name;		// ����
	quint32 m_id;		// ID
	QString m_caption;	// ����
	QString m_icon;		// ͼƬ���� 
	QStringList m_panels;	//��������б�
	_DrawToolPage_()
	{
		m_name = QString::null;
		m_id = 0;
		m_caption = QString::null;
		m_icon = QString::null;
		m_panels.clear();
	};
}DrawToolPage, *PDrawToolPage;

//! ��ѡ��߶���
typedef struct _MultiTool_
{
	QString							m_name;
	CUiTypeenum::EUiGroupType		m_type;		// ����
	QString							m_caption;	// ����
	QString							m_icon;		// icon
	std::vector<PToolPos>			m_tools;	//ѡ���б�
	QString							m_desc;		// ����

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

//! ҳ���л����ߣ�keyֵΪ�л���ť���֣�valueֵΪ��ť��Ϣ
typedef QMap<QString, PPageContrlTool> PPageControlToolMap;

//! ��ͼ���߿ؼ���keyֵΪ�������֣�valueֵΪ������Ϣ
typedef QMap<QString, PDrawTool> PDrawToolMap;

//! ��ͼ������壺keyֵΪ����������֣�valueֵΪ���������Ϣ
typedef QMap<QString, PDrawToolPanel> PDrawToolPanelMap;

//! ��ͼ����ҳ�棺keyֵΪ����ҳ���֣�valueֵΪ����ҳ��Ϣ
typedef QMap<QString, PDrawToolPage> PDrawToolPageMap;

//! ��ͼ���߶�ѡ��ߣ�keyֵΪ��ѡ�������,valueֵΪ������Ϣ
typedef QMap<QString, PMultiTool> PMultiToolMap;


#endif