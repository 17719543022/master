/*! * Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief	  QVector的使用
		  	

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

//#include "qglobal.h"
#include <QVector>

#include <iostream>
#include <algorithm>

#include "myclass.h"

void example01();
void example02();
void example03();

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
* @brief  向QVector添加成员并遍历。
* @return 无
*/
void example01(){
	
	// 添加成员
	QVector<quint32> vecId;
	QVector<quint32>::iterator iteVec = vecId.begin();
	vecId.push_back(2011);
	vecId.push_back(2033);
	vecId.push_back(2033);
	vecId.push_back(2042);
	vecId.push_back(2045);
	// push_front
	vecId.push_front(2046);


	// 遍历成员-使用下标
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members using idx......" << endl;
	int idxVec = 0;
	for (idxVec = 0; idxVec < vecId.size(); idxVec++) {
		cout << "    vecId[" << idxVec << "] =" << vecId[idxVec] << endl;
	}

	// 遍历成员-使用迭代器(正序)
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members using iterator......" << endl;
	iteVec = vecId.begin();
	idxVec = 0;
	for (iteVec = vecId.begin(); iteVec != vecId.end(); iteVec++) {
		cout << "    " << *iteVec << endl;
	}	

	// 遍历成员-使用迭代器(倒序)
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members using reverse iterator......" << endl;
	QVector<quint32>::reverse_iterator reverseIteVec = vecId.rbegin();
	for (reverseIteVec = vecId.rbegin(); reverseIteVec != vecId.rend(); reverseIteVec++) {
		cout << "    " << *reverseIteVec << endl;
	}	

	// 查找&插入
	iteVec = std::find(vecId.begin(), vecId.end(), 2042);
	if (iteVec != vecId.end())	{ // 在2042之前插入数据:10000.
		vecId.insert(iteVec, 10000); // insert before
		cout << endl << "-------------- QVector ---------------" << endl;
		cout << "insert 10000 before 2042 in vector." << endl;
	}
	// 遍历成员
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members using idx......" << endl;
	for (idxVec = 0; idxVec < vecId.size(); idxVec++) {
		cout << "    vecId[" << idxVec << "] =" << vecId[idxVec] << endl;
	}

	// 查找&删除
	iteVec = std::find(vecId.begin(), vecId.end(), 2042);
	if (iteVec != vecId.end())	{
		cout << "erase 2042 from vector." << endl;
		vecId.erase(iteVec);
	}
	// 遍历成员
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members using idx......" << endl;
	for (idxVec = 0; idxVec < vecId.size(); idxVec++) {
		cout << "    vecId[" << idxVec << "] =" << vecId[idxVec] << endl;
	}


	// 查找&删除
	for (iteVec=vecId.begin(); iteVec != vecId.end(); )	{
		if ((*iteVec) == 2033)	{
			cout << "find 2033 in vector." << endl;
			iteVec = vecId.erase(iteVec); // erase()接口会返回删除后的下一个迭代位置
		} else {
			iteVec++;
		}
	}
	// 遍历成员
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members using idx......" << endl;
	for (idxVec = 0; idxVec < vecId.size(); idxVec++) {
		cout << "    vecId[" << idxVec << "] =" << vecId[idxVec] << endl;
	}

}
/**
* @brief  使用自定义类对象
* @return 无
*/
void example02(){
	// 添加成员
	QVector<CMyClass> vecObj;
	CMyClass myclass1(2011, "lisa");
	CMyClass myclass2(2012, "mike");
	CMyClass myclass3(2012, "mike");
	CMyClass myclass4(2013, "john");
	CMyClass myclass5(2013, "ping");
	CMyClass myclass6(2025, "ping");

	// 如果想让下面的语句编译通过并且按照预期执行，需要为CMyClass类提供拷贝构造函数
	vecObj.push_back(myclass1);
	vecObj.push_back(myclass2);
	vecObj.push_back(myclass3);
	vecObj.push_back(myclass4);
	vecObj.push_back(myclass5);
	vecObj.push_back(myclass6);

	// 遍历成员，使用下标
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members using idx......" << endl;
	int idxVec = 0;
	for (idxVec = 0; idxVec < vecObj.size(); idxVec++) {
		cout << "    vecObj[" << idxVec << "] : id = " << vecObj[idxVec].getId() << ", name = " << vecObj[idxVec].getName().toLocal8Bit().data() << endl;
	}

	// 遍历成员，使用迭代器
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members using iterator......" << endl;
	QVector<CMyClass>::iterator iteVec = vecObj.begin();
	idxVec = 0;
	for (iteVec = vecObj.begin(); iteVec != vecObj.end(); iteVec++) {
		cout << "    vecObj[" << idxVec++ << "] : id = " << (*iteVec).getId() << ", name = " << (*iteVec).getName().toLocal8Bit().data() << endl;
	}

	// 查找
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "begin find member in QVector......" << endl;
	CMyClass myclassx(2013, "john");
	QVector<CMyClass>::iterator iteVecMy = std::find(vecObj.begin(), vecObj.end(), myclassx);
	if (iteVecMy != vecObj.end()) {
		cout << "find myclassx in vector." << endl;
	}
	else {
		cout << "cannot find myclassx in vector" << endl;
	}
}

/**
* @brief  使用自定义类对象指针
* @return 无
*/
void example03() {
	// 添加成员
	QVector<CMyClass*> vecObj;
	CMyClass* pMyclass1 = new CMyClass(2011, "lisa");
	CMyClass* pMyclass2 = new CMyClass(2012, "mike");
	CMyClass* pMyclass3 = new CMyClass(2012, "mike");
	CMyClass* pMyclass4 = new CMyClass(2013, "john");
	CMyClass* pMyclass5 = new CMyClass(2013, "ping");
	CMyClass* pMyclass6 = new CMyClass(2025, "ping");

	// 无需为CMyClass类提供拷贝构造函数
	vecObj.push_back(pMyclass1);
	vecObj.push_back(pMyclass2);
	vecObj.push_back(pMyclass3);
	vecObj.push_back(pMyclass4);
	vecObj.push_back(pMyclass5);
	vecObj.push_back(pMyclass6);

	// 遍历成员
	cout << endl << "-------------- QVector ---------------" << endl;
	cout << "print members in custom defined class using idx......" << endl;
	int idxVec = 0;
	for (idxVec = 0; idxVec < vecObj.size(); idxVec++) {
		cout << "    vecObj[" << idxVec << "] : id = " << vecObj[idxVec]->getId() << ", name = " << vecObj[idxVec]->getName().toLocal8Bit().data() << endl;
	}

	// 退出前要释放内存
	// 方法1，使用下标遍历
	if (0)	{
		cout << endl << "-------------- QVector ---------------" << endl;
		cout << "desctruct members before exit......" << endl;
		idxVec = 0;
		for (idxVec = 0; idxVec < vecObj.size(); idxVec++) {
			cout << "    deleting " << idxVec << ", id = " << vecObj[idxVec]->getId() << ", name = " << vecObj[idxVec]->getName().toLocal8Bit().data() << endl;
			delete vecObj[idxVec];
		}
	}
	else
	{
		cout << endl << "-------------- QVector ---------------" << endl;
		cout << "desctruct members before exit......" << endl;
		// 方法2，使用迭代器遍历
		QVector<CMyClass*>::iterator iteVec = vecObj.begin();
		idxVec = 0;
		for (iteVec = vecObj.begin(); iteVec != vecObj.end(); iteVec++) {
			if (NULL != *iteVec) {
				cout << "    deleting element:" << idxVec++ << ", id = " << (*iteVec)->getId() << ", name = " << (*iteVec)->getName().toLocal8Bit().data() << endl;
				delete (*iteVec);
			}
		}
	}


	vecObj.clear();
}
