/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: dialog.cpp
\brief  CDialog ���ʵ���ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/9
*/

#include "dialog.h"

#include "address.h"
#include "simpledialog.h"


CDialog::CDialog(QWidget* pParent) : QDialog(pParent) {
	setupUi(this);

	initialDialog();
}

CDialog::~CDialog(){

}
void CDialog::initialDialog() {
	
	// �����Զ���ؼ�����
	CWidgetAddress* pWidgetAddress = new CWidgetAddress(this);
	
	connect(pWidgetAddress, SIGNAL(addressSaved(const QString &)), 
        this, SLOT(on_slot_addressSaved(const QString &)));
	//connect(pWidgetAddress, SIGNAL(addressSaved(const QString &)), 
 //       this, SIGNAL(sig_addressSaved(const QString &)));
	connect(pWidgetAddress, &CWidgetAddress::addressSaved,
        this, &CDialog::sig_addressSaved);

	// ��Ҫ�����Զ�����
	QGridLayout *gridLayout_2;
	gridLayout_2 = new QGridLayout(this);
	gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
	gridLayout_2->addWidget(pWidgetAddress, 0, 0, 1, 1);

}


void CDialog::on_slot_addressSaved(const QString& strAddress){
	
	if (NULL != m_plainTextEdit->document()) {
		QString str = "The Address is:" + strAddress;
		m_plainTextEdit->document()->setPlainText(str);
	}
}

