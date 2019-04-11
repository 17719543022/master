/*! 
\file: myobject.h
\brief  CMyObject类的定义文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
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