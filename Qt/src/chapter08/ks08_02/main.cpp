/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: main.cpp
\brief mian()������ʵ���ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/9
*/

#include <QApplication>
#include <QHeaderView>
#include <QList>
#include <QStandardItemModel>
#include <QTreeView>
#include <iostream>
#include "base/basedll/baseapi.h"
#include "qglobal.h"
#include "country.h"
#include "province.h"
#include "city.h"

using std::cout;
using std::endl;
using std::cin;

/**
* @brief����CCountry����.
* @return CCountry����ָ��
*/
CCountry* createCountry(void) {
	CProvince* pProvince = NULL;
	CCity* pCity = NULL;
	CCountry* pCountry = new CCountry(QString::fromLocal8Bit("�й�"));
	if (NULL == pCountry) {
		return NULL;
	}
	// add province
	{
		pProvince = new CProvince();
		pCountry->addProvince(pProvince);
		pProvince->setCountry(pCountry);
		pProvince->setName(QString::fromLocal8Bit("ɽ��"));
		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("����"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("�ൺ"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}
	// add province
	{
		pProvince = new CProvince();
		pCountry->addProvince(pProvince);
		pProvince->setCountry(pCountry);
		pProvince->setName(QString::fromLocal8Bit("�ӱ�"));
		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("������"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("�żҿ�"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("����"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}

	// ���ع�����CCountry����
	return pCountry;
}

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QApplication app(argc, argv);

	CCountry* pCountry = createCountry();
	if (NULL == pCountry)
		return 1;

	QList<CProvince*> lstProvinces;
	QList<CProvince*>::iterator iteProvince;
	QList<CCity*> lstCities;
	QList<CCity*>::iterator iteCity;

	pCountry->getProvinces(lstProvinces);

	QStandardItemModel model;
	QTreeView treeView;
	treeView.setModel(&model);
	treeView.setRootIsDecorated(true);
	treeView.header()->setSectionsMovable(false);
	treeView.header()->setStretchLastSection(true);
	treeView.setWindowTitle(QObject::tr("Flat Tree View"));
	treeView.show();
	
	// �� Country�ڵ� ��ӵ�invisible���ڵ���Ϊ���ӽڵ�
	QStandardItem *pItemCountry = new QStandardItem(pCountry->getName());
	QStandardItem *pItemRoot = model.invisibleRootItem();
	pItemRoot->appendRow(pItemCountry);
	
	QStandardItem *pItemProvince = NULL;
	QStandardItem *pItemCity = NULL;
	iteProvince = lstProvinces.begin();
	while (iteProvince != lstProvinces.end()) {
		pItemProvince = new QStandardItem((*iteProvince)->getName()); // ����������:province
		pItemCountry->appendRow(pItemProvince); // ���������: province
		
		(*iteProvince)->getCities(lstCities);
		iteCity = lstCities.begin();
		while (iteCity != lstCities.end()) {
			// ����������:city
			pItemCity = new QStandardItem((*iteCity)->getName());
			// ���������: city
			pItemProvince->appendRow(pItemCity);
			iteCity++;
		}
		iteProvince++;
	}
	
	return app.exec();
}

