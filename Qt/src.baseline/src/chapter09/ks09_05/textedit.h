/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: textedit.h
\brief ��ʾ��ͷ�ļ�
  
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/8 
*/

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>


class CTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	CTextEdit(QWidget* parent);
	~CTextEdit(){;}

protected:
	virtual void paintEvent(QPaintEvent *event);

};

#endif // TEXTEDIT_H