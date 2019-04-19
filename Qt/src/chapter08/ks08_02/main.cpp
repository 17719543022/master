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

CCountry* createCountry(void);

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

	const int COLUMNCOUNT = 2;  // 列的个数
	QStandardItemModel model;
	QTreeView treeView;
	treeView.setModel(&model);
	treeView.setRootIsDecorated(true);
	//treeView.header()->setFirstSectionMovable(false);
	treeView.header()->setSectionsMovable(false);
	treeView.header()->setStretchLastSection(true);
	treeView.setWindowTitle(QObject::tr("Flat Tree View"));
	treeView.show();

	//model.setData(indexRoot, pCountry->getName());
	QStandardItem *pItemRoot = model.invisibleRootItem();
	QModelIndex indexRoot = pItemRoot->index();
	
	// 将 Country节点 添加到invisible根节点作为其子节点
	QStandardItem *pItemCountry = new QStandardItem(pCountry->getName());
	pItemRoot->appendRow(pItemCountry);
	QFont ft("宋体", 16);
	ft.setBold(true);
	pItemCountry->setData(ft, Qt::FontRole);
	pItemCountry->setData(QColor(Qt::red), Qt::TextColorRole);
	QImage img(":/images/china.png");	;
	pItemCountry->setData(img.scaled(QSize(24, 24)), Qt::DecorationRole);

	// 设置pItemRoot的列数以便显示省的个数
	pItemRoot->setColumnCount(COLUMNCOUNT);
	// 在Country节点所在的行的第1列显示省的个数
	model.setData(model.index(0, 1, indexRoot), lstProvinces.size());

	QStandardItem *pItemProvince = NULL;
	QStandardItem *pItemCity = NULL;
	int idProvince = 0;
	iteProvince = lstProvinces.begin();
	while (iteProvince != lstProvinces.end()) {
		pItemProvince = new QStandardItem((*iteProvince)->getName()); // 构建数据项:province
		pItemCountry->appendRow(pItemProvince); // 添加数据项: province
		
		// 设置pItemCountry的列数以便显示城市的个数
		pItemCountry->setColumnCount(COLUMNCOUNT);
		(*iteProvince)->getCities(lstCities);
		// 设置Province节点的第0列的文本颜色为蓝色
		model.setData(model.index(idProvince, 0, pItemCountry->index()), QColor(Qt::blue), Qt::TextColorRole);
		// 设置Country节点第1列数据为城市个数
		model.setData(model.index(idProvince++, 1, pItemCountry->index()), lstCities.size());
		
		// 遍历所有城市
		iteCity = lstCities.begin();
		while (iteCity != lstCities.end()) {
			// 构建数据项:city
			pItemCity = new QStandardItem((*iteCity)->getName());
			// 添加数据项: city
			pItemProvince->appendRow(pItemCity);
			iteCity++;
		}
		iteProvince++;
	}

	return app.exec();
}


/**
* @brief构建CCountry对象.
* @return CCountry对象指针
*/
CCountry* createCountry(void) {
	CProvince* pProvince = NULL;
	CCity* pCity = NULL;
	CCountry* pCountry = new CCountry(QString::fromLocal8Bit("中国"));
	if (NULL == pCountry) {
		return NULL;
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

		// add city
		pCity = new CCity();
		pCity->setName(QString::fromLocal8Bit("保定"));
		pCity->setProvince(pProvince);
		pProvince->addCity(pCity);
	}

	// 返回构建的CCountry对象
	return pCountry;
	
}
