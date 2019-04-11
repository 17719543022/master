#ifndef _ACTIONMGR_H_
#define _ACTIONMGR_H_

#include <QMap>
#include <QObject>

#include "actiondef.h"

class QAction;

class CActionMgr : public QObject
{
	Q_OBJECT
public:
	//! ����Ĵ���������
	static CActionMgr* instance();
	void destroy();

	//! ��������ʼ��������UI�ļ�������UI��Ϣ
	void initInstance();

	//! �����˳�����
	void exitInstance();

public:
	//���Actionָ��
	QAction* getAction(CActionenum::EDrawAction eAction) const;
	QWidget* getWidget(CActionenum::EDrawWidget eWidget) const;

	void addAction(CActionenum::EDrawAction eAction, QAction* pAction);
	void addWidget(CActionenum::EDrawWidget eWidget, QWidget* pWidget);

private://����Ϊ����ģʽ��˽�й��캯�������徲ָ̬��
	CActionMgr(void);
	CActionMgr(const CActionMgr&);
	CActionMgr& operator=(const CActionMgr&);
	~CActionMgr(void);
	//!���徲ָ̬��
	static CActionMgr* pInstance;

private:
	QMap<CActionenum::EDrawAction, QAction*> pActionMap;

	QMap<CActionenum::EDrawWidget, QWidget*> pWidgetMap;
};

#endif