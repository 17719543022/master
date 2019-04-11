/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief      QVariant的使用
            
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#include "qglobal.h"
#include <QColor>
#include <QFont>
#include <QPointF>
#include <QVariant>
#include <QString>

#include <iostream>

//#include "myclass.h"

void example01();
void example02();
void example03();
void example04();

using std::cout;
using std::endl;
using std::cin;

//
int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);


	// example01 
	if (0) {
		example01();
	}

	// example02 
	if (1) {
		example02();
	}

    // example03 
    if (0) {
        example03();
    }

    // example03 
    if (0) {
        example04();
    }

	char ch = '\0';
	cin >> ch;

	return 0;
}

/**
* @brief  常见Qt类与QVariant互相转换
* @return 无
*/
void example01(){
	
	QVariant var1(1); // 整数
	cout << "this is an integer:" << var1.toInt();
	
	uint uVal = 599;
	QVariant var2(uVal); // 无符号整数
	cout << "this is a unsigned integer:" << var2.toUInt();

	double dVal = 100.23456;
	QVariant var3(dVal); // 双精度浮点数
	cout << "this is a double:" << var3.toDouble();

	QString str("I am string");
	QVariant var4 = str; // 用字符串
	cout << "this is a string:" << var4.toString().toLocal8Bit().data();
	
	QPointF pt(102.35, 200.1);
	QVariant var5(pt);
	cout << "this is a pointf:" << var5.toPointF().x() << ", "<< var5.toPointF().y();

}
/**
* @brief  QVariant::value<>()的使用
* @return 无
*/
void example02(){
	QColor clr1(Qt::darkMagenta);
	QVariant var1(clr1);

	QColor clr2 = var1.value<QColor>();
	cout << "clr : " << clr2.redF() << " , " << clr2.greenF() << clr2.blueF() << endl;


	QFont ft1("宋体", 12.6);
	QVariant var2(ft1);
	QFont ft2 = var2.value<QFont>();
	cout << "font family:" << ft2.family().toLocal8Bit().data() << ", point size=" << ft2.pointSizeF() << endl;
}

/**
* @brief  QVariantList的使用
* @return 无
*/
void example03() {

	QVariant var1(1); // 整数

	uint uVal = 599;
	QVariant var2(uVal); // 无符号整数

	double dVal = 100.23456;
	QVariant var3(dVal); // 双精度浮点数

	QString str("I am string");
	QVariant var4 = str; // 用字符串

	QPointF pt(102.35, 200.1);


	QVariantList lst;
	lst << var1 << var2 << var3 << var4;

	QVariant var;
	QVariantList::iterator iteLst = lst.begin();
	for (iteLst = lst.begin(); iteLst != lst.end(); iteLst++)
	{
		var = *iteLst;
		cout << "type is " << var.typeName() << ", value is ";
		switch (var.type())
		{
		case QVariant::Int:
			cout << var.toInt() << endl;
			break;
		case QVariant::String:
			cout << var.toString().toLocal8Bit().data() << endl;
			break;
		case QVariant::Double:
			cout << var.toDouble();
			break;
		case QVariant::RectF:
			cout << "x:" << var.toPointF().x() << ", y:"<<var.toPointF().y();
			break;
		default:
			break;
		}
	}
}

/**
* @brief  QVariant::nameToType(), QVariant::typeToName()
* @return 无
*/
void example04() {

	cout << QVariant::typeToName(QVariant::Int);
	cout << QVariant::typeToName(QVariant::Double);

	double dVal = 100.23456;
	QVariant var3(dVal); // 双精度浮点数
	cout << QVariant::nameToType(var3.typeName());

}
