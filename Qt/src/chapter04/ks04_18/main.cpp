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

void example01(bool);
void example02(void);
void example03(void);

void print(CCountry* pCountry);

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	bool bBinary = 0;

	example01(bBinary);

	if (bBinary) {
		example02();
	}
	else {
		example03();
	}
		
	system("pause");
	return 0;
}


/**
* @brief 初始化数据并序列化.
* @param[in] bBinary true:保存为二进制, false:保存为XML
* @return void
*/
void example01(bool bBinary) {
	CProvince* pProvince = NULL;
	CCity* pCity = NULL;
	CCountry* pCountry = new CCountry(QString::fromLocal8Bit("中国"));
	if (NULL == pCountry) {
		return;
	}

  
    pCountry->addCustomData("flag", QString::fromLocal8Bit("五星红旗"));
    pCountry->addCustomData(QString::fromLocal8Bit("国歌"), QString::fromLocal8Bit("义勇军进行曲"));

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
	QString strFileName = (bBinary?
							ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_18/country.dat"):
							ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_18/country.xml"));
	if (bBinary) {
		pCountry->serializeBinary(strFileName, NULL);
	}
	else {
		pCountry->serializeXML(strFileName, NULL);
	}

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
    QStringList lst;
    pCountry->getAllCustomDataName(lst);
    QStringList::iterator iteName = lst.begin();
    QVariant var;
    while (iteName != lst.end()) {
        var = pCountry->getCustomData(*iteName);
        cout << (*iteName).toLocal8Bit().data() << ":" << var.toString().toLocal8Bit().data() << endl;
        iteName++;
    }

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
* @brief 读取二进制，反序列化.
* @return void
*/
void example02(void) {
	CCountry* pCountry = new CCountry();
	QString strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_18/country.dat");
	pCountry->deSerializeBinary(strFileName, NULL);

	cout << "----------------------------------------" << endl;
	cout << "read file content:" << endl;

	// 打印输出
	print(pCountry);

}

/**
* @brief 读取XML，反序列化.
* @return void
*/
void example03(void) {
	CCountry* pCountry = new CCountry();
	QString strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_18/country.xml");
	pCountry->deSerializeXML(strFileName, NULL);

	cout << "----------------------------------------" << endl;
	cout << "read file content:" << endl;

	// 打印输出
	print(pCountry);

}