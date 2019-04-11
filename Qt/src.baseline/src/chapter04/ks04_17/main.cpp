/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief mian()函数的实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#include <QList>
#include "qglobal.h"

#include <iostream>

#include "base/basedll/baseapi.h"
#include "city.h"
#include "country.h"
#include "province.h"

using std::cout;
using std::endl;

void example01(void);
void example02(void);

void print(CCountry* pCountry);

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	if (true) {
		example01();
	}

	if (true) {
		example02();
	}
		
	system("pause");
	return 0;
}


/**
* @brief 初始化数据并序列化.
* @return void
*/
void example01(void) {
	CProvince* pProvince = NULL;
	CCity* pCity = NULL;
	CCountry* pCountry = new CCountry(QString::fromLocal8Bit("中国"));
	if (NULL == pCountry) {
		return;
	}
	// add province
	{
		pProvince = new CProvince();
		pCountry->addProvince(pProvince);
		pProvince->setCountry(pCountry);
		pProvince->setName(QString::fromLocal8Bit("山东"));
		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("济南"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("青岛"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}
	// add province
	{
		pProvince = new CProvince();
		pCountry->addProvince(pProvince);
		pProvince->setCountry(pCountry);
		pProvince->setName(QString::fromLocal8Bit("河北"));
		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("北戴河"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("张家口"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}

	cout << "----------------------------------------" << endl;
	cout << "save file content:" << endl;
	// 打印输出
	print(pCountry);

	// 序列化
	QString strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_17/country.dat");
	pCountry->serializeBinary(strFileName, NULL);

	// 释放内存
	delete pCountry;
	
}


void print(CCountry* pCountry) {
	QList<CProvince*> lstProvinces;
	QList<CProvince*>::iterator iteProvince;
	QList<CCity*> lstCities;
	QList<CCity*>::iterator iteCity;
	if (NULL == pCountry) {
		return;
	}

	cout << pCountry->getName().toLocal8Bit().data() << endl;

	pCountry->getProvinces(lstProvinces);
	iteProvince = lstProvinces.begin();
	while (iteProvince != lstProvinces.end()) {
		cout << "\t省(州):" << (*iteProvince)->getName().toLocal8Bit().data() << endl;
		(*iteProvince)->getCities(lstCities);
		iteCity = lstCities.begin();
		while (iteCity != lstCities.end()) {
			cout << "\t\t城市:" << (*iteCity)->getName().toLocal8Bit().data() << endl;
			iteCity++;
		}
		iteProvince++;
	}

}

/**
* @brief 反序列化.
* @return void
*/
void example02(void) {
	CCountry* pCountry = new CCountry();
	QString strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_17/country.dat");
	pCountry->deSerializeBinary(strFileName, NULL);

	cout << "----------------------------------------" << endl;
	cout << "read file content:" << endl;

	// 打印输出
	print(pCountry);

}