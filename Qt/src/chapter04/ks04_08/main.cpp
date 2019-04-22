/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: main.cpp
\brief      QVariant��ʹ��
            
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
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
* @brief  ����Qt����QVariant����ת��
* @return ��
*/
void example01(){
	
	QVariant var1(1); // ����
	cout << "this is an integer:" << var1.toInt();
	
	uint uVal = 599;
	QVariant var2(uVal); // �޷�������
	cout << "this is a unsigned integer:" << var2.toUInt();

	double dVal = 100.23456;
	QVariant var3(dVal); // ˫���ȸ�����
	cout << "this is a double:" << var3.toDouble();

	QString str("I am string");
	QVariant var4 = str; // ���ַ���
	cout << "this is a string:" << var4.toString().toLocal8Bit().data();
	
	QPointF pt(102.35, 200.1);
	QVariant var5(pt);
	cout << "this is a pointf:" << var5.toPointF().x() << ", "<< var5.toPointF().y();

}
/**
* @brief  QVariant::value<>()��ʹ��
* @return ��
*/
void example02(){
	QColor clr1(Qt::darkMagenta);
	QVariant var1(clr1);

	QColor clr2 = var1.value<QColor>();
	cout << "clr : " << clr2.redF() << " , " << clr2.greenF() << clr2.blueF() << endl;


	QFont ft1("����", 12.6);
	QVariant var2(ft1);
	QFont ft2 = var2.value<QFont>();
	cout << "font family:" << ft2.family().toLocal8Bit().data() << ", point size=" << ft2.pointSizeF() << endl;
}

/**
* @brief  QVariantList��ʹ��
* @return ��
*/
void example03() {

	QVariant var1(1); // ����

	uint uVal = 599;
	QVariant var2(uVal); // �޷�������

	double dVal = 100.23456;
	QVariant var3(dVal); // ˫���ȸ�����

	QString str("I am string");
	QVariant var4 = str; // ���ַ���

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
* @return ��
*/
void example04() {

	cout << QVariant::typeToName(QVariant::Int);
	cout << QVariant::typeToName(QVariant::Double);

	double dVal = 100.23456;
	QVariant var3(dVal); // ˫���ȸ�����
	cout << QVariant::nameToType(var3.typeName());

}
