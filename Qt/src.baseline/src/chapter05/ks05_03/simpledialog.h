/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: simpledialog.h
\brief  CSimpleDialog��Ķ����ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/9
*/

#ifndef SIMPLEDIALOG_H
#define SIMPLEDIALOG_H

#include "ui_simpledialogbase.h" // ͷ�ļ���������: simpledialogbase.ui  ---> ui_simpledialogbase.h


// ��һ���������������ui�ļ��жԻ��������������鿴���е�����
// �ڶ����������������ui�ļ��жԻ�����������(objeceName����)�� CDialogBase
class CSimpleDialog : public QDialog, public Ui::CSimpleDialogBase
{
	Q_OBJECT
public:
	CSimpleDialog(QWidget* pParent);
	~CSimpleDialog();

public slots:
private:
};

#endif // SIMPLEDIALOG_H