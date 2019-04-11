/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief      QMap的使用
            --添加成员
            --遍历
            --查找
            --删除

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

//#include "qglobal.h"
#include <QMap>
#include <QPair>
#include <QString>

#include <iostream>

#include "myclass.h"

void example01();
void example02();
void example03();

void printByIterator(const QMap<uint, QString>& mapObj);

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

	char ch = '\0';
	cin >> ch;

	return 0;
}

/**
* @brief  向QMap添加成员并遍历。
* @return 无
*/
void example01(){
	
	// 添加成员
	QMap<uint, QString> mapObj;
	mapObj[1] = "BeiJing";
	mapObj[2] = "ShangHia";
	mapObj[3] = "GuangZhou";
	mapObj[4] = "ShenZhen";

    mapObj.insert(5, "XiaMen");
    	
	// 遍历成员-使用迭代器(正序)
	//printByIterator(mapObj);
	cout << endl << "-------------- QMap ---------------" << endl;
	cout << "print members using iterator......" << endl;
	QMap<uint, QString>::iterator iteMap = mapObj.begin();
	for (iteMap = mapObj.begin(); iteMap != mapObj.end(); iteMap++) {
		cout << "-- key = " << iteMap.key() << ", value = " << iteMap.value().toLocal8Bit().data() << endl;
	}

	// 查找
	//QMap<uint, QString>::iterator iteMap;
	// 迭代器 = map对象.find(key);
	iteMap = mapObj.find(5);
	if (iteMap != mapObj.end())	{
		cout << endl << "-------------- QMap ---------------" << endl;
		// 迭代器.key()表示键; 迭代器.value()表示对应的值
		cout << "find member where key = 5, and value = " << iteMap.value().toLocal8Bit().data() << endl;
	} else {
		cout << "cannot find member from map where key = 5." << endl;
    }

	// 删除
	cout << endl << "-------------- QMap ---------------" << endl;
	if (iteMap != mapObj.end())	{
		cout << "erase it from map." << endl;
		mapObj.erase(iteMap);
	} 

	// 遍历成员-使用迭代器(正序)
	printByIterator(mapObj);    


}
/**
* @brief  使用自定义类对象
* @return 无
*/
void example02(){
	// 添加成员
	QMap<CMyClass, uint> mapObj;
	CMyClass myclass1(2011, "lisa");
	CMyClass myclass2(2012, "mike");
	CMyClass myclass3(2012, "mike");
	CMyClass myclass4(2013, "john");
	CMyClass myclass5(2013, "ping");
	CMyClass myclass6(2025, "ping");
	// 如果想让下面的语句编译通过并且按照预期执行，需要为CMyClass类提供拷贝构造函数，并重载operator<操作符。
    mapObj[myclass1] = 1;
    mapObj[myclass2] = 2;
    mapObj[myclass3] = 3;
    mapObj[myclass4] = 4;
    mapObj[myclass5] = 5;
    mapObj[myclass6] = 6;
    
	// 遍历成员
	cout << endl << "-------------- QMap ---------------" << endl;
    QMap<CMyClass, uint>::iterator iteMap;
    for (iteMap = mapObj.begin(); iteMap != mapObj.end(); iteMap++) {
        cout << "key = ("<< iteMap.key().getId() << ", " << iteMap.key().getName().toLocal8Bit().data() << "), value = "<< iteMap.value() << endl;
    }

	// 查找&删除
	cout << endl << "-------------- QMap ---------------" << endl;
	cout << "begin find member in QMap......" << endl;
	CMyClass myclassx(2013, "john");
	iteMap = mapObj.find(myclassx);
	if (iteMap != mapObj.end()) {
		cout << "find myclassx in map. key = (" << iteMap.key().getId() << ", " << iteMap.key().getName().toLocal8Bit().data() <<"), value = "  << iteMap.value() << endl;
        mapObj.erase(iteMap); // 删除
	}
	else {
		cout << "cannot find myclassx in map" << endl;
	}

	cout << endl << "-------------- QMap ---------------" << endl;
	cout << endl << "after erase:" << endl;
    for (iteMap = mapObj.begin(); iteMap != mapObj.end(); iteMap++) {
        cout << "key = (" << iteMap.key().getId() << ", " << iteMap.key().getName().toLocal8Bit().data() << "), value = " << iteMap.value() << endl;
    }
}

/**
* @brief  QMap的value是列表类型。
* @return 无
*/
void example03() {

    // 添加成员
    QMap<uint, QStringList> mapObj;
   
    QMap<uint, QStringList>::iterator iteMap;
    
    iteMap = mapObj.find(1);
    if (iteMap == mapObj.end())
    {
        cout << "not found!" << endl;
		if (0) {
			mapObj[1].push_back("hello");// 有的编译器执行该行代码时报错
		}
		else
		{
			// 有的编译器不允许直接对未初始化的value操作，
			// 而应该用下面的3行代码：先定义一个QStringList对象lst，把数据插入lst,然后把lst作为value填写到QMap
			QStringList lst;
			lst.push_back("hello");
			mapObj[1] = lst;
		}

    }
    else {
        mapObj[1].push_back("hello");
    } 
}
void printByIterator(const QMap<uint, QString>& mapObj)
{
	cout << endl << "-------------- QMap ---------------" << endl;
	cout << "print members using iterator......" << endl;
	QMap<uint, QString>::const_iterator iteMap = mapObj.constBegin();
	for (iteMap = mapObj.constBegin(); iteMap != mapObj.constEnd(); iteMap++) {
		cout << "-- key = " << iteMap.key() << ", value = " << iteMap.value().toLocal8Bit().data() << endl;
	}
}

