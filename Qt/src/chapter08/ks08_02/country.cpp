/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: country.cpp
\brief 国家类实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
*/
#include <QDir>

#include "country.h"
#include "province.h"
#include "base/basedll/baseapi.h"

CCountry::CCountry() {
	;
}

CCountry::~CCountry() {
	QList<CProvince*>::iterator iteLst = m_lstProvinces.begin();
	while (iteLst != m_lstProvinces.end()) {
		if (NULL != *iteLst) {
			delete *iteLst;
		}
		iteLst++;
	}

	m_lstProvinces.clear();
}

int CCountry::addProvince(CProvince* pProvince) {
	if ((NULL == pProvince) || (m_lstProvinces.contains(pProvince))) {
		return m_lstProvinces.size();
	}

	m_lstProvinces.push_back(pProvince);
	return m_lstProvinces.size();
}
