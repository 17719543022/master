/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief QList的使用

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

//#include "qglobal.h"
#include <QString>
#include <QList>

#include <iostream>
#include <algorithm>

#include "myclass.h"

void example01();
void example02();
void example03();

void printByIndex(const QList<quint16>& lst);
void printByIterator(const QList<quint16>& lst);
void printByIteratorReverse(const QList<quint16>& lst);

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
	if (0) {
		example02();
	}

	// example03 
	if (1) {
		example03();
	}

	char ch = '\0';
	cin >> ch;

	return 0;
}

/**
* @brief  向QList添加成员并遍历。
* @return 无
*/
void example01(){
	
	// 添加成员
	QList<quint16> lstObj;
	lstObj.push_back(2011);
	lstObj.push_back(2033);
	lstObj.push_back(2033);
	lstObj.push_back(2042);
	lstObj.push_back(2045);
	// push_front
	lstObj.push_front(2046);


	// 遍历成员-使用下标
	printByIndex(lstObj);

	// 遍历成员-使用迭代器(正序)
	printByIterator(lstObj);

	// 遍历成员-使用迭代器(倒序)
	printByIteratorReverse(lstObj);

	// 查找&插入
	QList<quint16>::iterator iteList;
	iteList = std::find(lstObj.begin(), lstObj.end(), 2042);
	if (iteList != lstObj.end())	{
		lstObj.insert(iteList, 10000); // insert before
		cout << endl << "-------------- QList ---------------" << endl;
		cout << "insert 10000 before 2042 in list." << endl;
	}
	// 遍历成员
	int idxList = 0;
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "print members using idx......" << endl;
	for (idxList = 0; idxList < lstObj.size(); idxList++) {
		cout << "    lstObj[" << idxList << "] =" << lstObj[idxList] << endl;
	}

	// 查找&删除
	iteList = std::find(lstObj.begin(), lstObj.end(), 2042);
	if (iteList != lstObj.end())	{
		cout << "erase 2042 from list." << endl;
		lstObj.erase(iteList);
	}
	// 遍历成员
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "print members using idx......" << endl;
	for (idxList = 0; idxList < lstObj.size(); idxList++) {
		cout << "    lstObj[" << idxList << "] =" << lstObj[idxList] << endl;
	}


	// 查找&删除
	for (iteList=lstObj.begin(); iteList != lstObj.end(); )
	{
		if ((*iteList) == 2033)	{
			cout << "find 2033 in list.erasing..." << endl;
			iteList = lstObj.erase(iteList); // erase()接口会返回删除后的下一个迭代位置
		} else {
			iteList++;
		}
	}
	// 遍历成员
	printByIndex(lstObj);
	printByIterator(lstObj);
}
/**
* @brief  使用自定义类对象
* @return 无
*/
void example02(){
	// 添加成员
	QList<CMyClass> lstObj;
	CMyClass myclass1(2011, "lisa");
	CMyClass myclass2(2012, "mike");
	CMyClass myclass3(2012, "mike");
	CMyClass myclass4(2013, "john");
	CMyClass myclass5(2013, "ping");
	CMyClass myclass6(2025, "ping");

	// 如果想让下面的语句编译通过并且按照预期执行，需要为CMyClass类提供拷贝构造函数
	lstObj.push_back(myclass1);
	lstObj.push_back(myclass2);
	lstObj.push_back(myclass3);
	lstObj.push_back(myclass4);
	lstObj.push_back(myclass5);
	lstObj.push_back(myclass6);

	// 遍历成员
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "print members using idx......" << endl;
	int idxList = 0;
	for (idxList = 0; idxList < lstObj.size(); idxList++) {
		cout << "    lstObj[" << idxList << "] : id = " << lstObj[idxList].getId() << ", name = " << lstObj[idxList].getName().toLocal8Bit().data() << endl;
	}

	// 查找
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "begin find member in QList......" << endl;
	CMyClass myclassx(2013, "john");
	QList<CMyClass>::iterator iteList = std::find(lstObj.begin(), lstObj.end(), myclassx);
	if (iteList != lstObj.end()) {
		cout << "find myclassx in list." << endl;
	}
	else {
		cout << "cannot find myclassx in list" << endl;
	}
}

/**
* @brief  使用自定义类指针
* @return 无
*/
void example03() {
	// 添加成员
	QList<CMyClass*> lstObj;
	CMyClass* pMyclass1 = new CMyClass(2011, "lisa");
	CMyClass* pMyclass2 = new CMyClass(2012, "mike");
	CMyClass* pMyclass3 = new CMyClass(2012, "mike");
	CMyClass* pMyclass4 = new CMyClass(2013, "john");
	CMyClass* pMyclass5 = new CMyClass(2013, "ping");
	CMyClass* pMyclass6 = new CMyClass(2025, "ping");

	// 无需为CMyClass类提供拷贝构造函数
	lstObj.push_back(pMyclass1);
	lstObj.push_back(pMyclass2);
	lstObj.push_back(pMyclass3);
	lstObj.push_back(pMyclass4);
	lstObj.push_back(pMyclass5);
	lstObj.push_back(pMyclass6);

	// 遍历成员
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "print members in custom defined class using idx......" << endl;
	int idxList = 0;
	for (idxList = 0; idxList < lstObj.size(); idxList++) {
		cout << "    lstObj[" << idxList << "] : id = " << lstObj[idxList]->getId() << ", name = " << lstObj[idxList]->getName().toLocal8Bit().data() << endl;
	}

	// 退出前要释放内存
	// 方法1，使用下标遍历
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "desctruct members before exit......" << endl;
	idxList = 0;
	if (false) {
		for (idxList = 0; idxList < lstObj.size(); idxList++) {
			cout << "    deleting " << idxList << ", id = " << lstObj[idxList]->getId() << ", name = " << lstObj[idxList]->getName().toLocal8Bit().data() << endl;
			delete lstObj[idxList];
		}
	}
	else
	{
		// 方法2，使用迭代器遍历
		QList<CMyClass*>::iterator iteList = lstObj.begin();
		for (iteList = lstObj.begin(); iteList != lstObj.end(); iteList++, idxList++) {
			if (NULL != *iteList) {
				delete *iteList;
			}
		}
	}

	lstObj.clear();
}

void printByIterator(const QList<quint16>& lstObj){
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "print members using iterator......" << endl;
	QList<quint16>::const_iterator iteList = lstObj.constBegin();
	for (iteList = lstObj.constBegin(); iteList != lstObj.constEnd(); iteList++) {
		cout << "    " << *iteList << endl;
	}
}


void printByIteratorReverse(const QList<quint16>& lstObj){
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "print members using iterator reverse......" << endl;
	QList<quint16>::const_reverse_iterator iteList;
	for (iteList = lstObj.crbegin(); iteList != lstObj.crend(); iteList++) {
		cout << "    " << *iteList << endl;
	}
}

void printByIndex(const QList<quint16>& lstObj){
	cout << endl << "-------------- QList ---------------" << endl;
	cout << "print members using idx......" << endl;
	int idxList = 0;
	for (idxList = 0; idxList < lstObj.size(); idxList++) {
		cout << "    lstObj[" << idxList << "] =" << lstObj[idxList] << endl;
	}
}