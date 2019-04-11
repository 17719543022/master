/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: address.h
\brief  CWidgetAddress��Ķ����ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/9
*/

#ifndef ADDRESS_H
#define ADDRESS_H

#include "ui_address.h" // ͷ�ļ���������: address.ui  ---> ui_address.h


// ��һ���������������ui�ļ��жԻ��������������鿴���е�����
// �ڶ����������������ui�ļ��жԻ�����������(objeceName����)�� CWidgetAddressBase
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