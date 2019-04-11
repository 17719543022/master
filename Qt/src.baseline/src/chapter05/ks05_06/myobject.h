/*! 
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
public slots:
	void slot_addressChanged(const QString&);
private:
};

#endif // MYOBJECT_H