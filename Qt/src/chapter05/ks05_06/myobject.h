/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: myobject.h
\brief  CMyObject��Ķ����ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/9
*/

#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class CMyObject : public QObject
{
	Q_OBJECT
public:
	CMyObject();
	~CMyObject();

public:
	void saveLog(const QString&);
private slots:
	void slot_addressChanged(const QString&);
private:
};

#endif // MYOBJECT_H