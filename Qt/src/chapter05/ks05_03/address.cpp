/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: address.cpp
\brief  CWidgetAddress���ʵ���ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/9
*/
#include "address.h"


CWidgetAddress::CWidgetAddress(QWidget* pParent) : QWidget(pParent) {
	setupUi(this);

	//connect(m_btnSave, SIGNAL(clicked()), this, SLOT(on_addressSaved()));
	connect(m_btnSave, &QPushButton::clicked, 
        this, &CWidgetAddress::slot_btnSaveClicked);
}

CWidgetAddress::~CWidgetAddress(){
	
}


void CWidgetAddress::slot_btnSaveClicked()
{
    emit sigAddressSaved(m_lineEdit->text());
}
