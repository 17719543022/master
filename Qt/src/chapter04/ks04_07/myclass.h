/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。


\file: myclass.h
\brief exe+dll编程示例，引出类的定义头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 
*/

#ifndef _MYCLASS_DLL_H
#define _MYCLASS_DLL_H

#include <QString>

class CMyClass
{
public:
	// 构造函数
	CMyClass(): m_id(0), m_pStrName(NULL){}
	// 构造函数
	CMyClass(int id, const QString& name): m_id(id), m_pStrName(new QString(name)){}

	// 拷贝构造函数
	CMyClass(const CMyClass& right);

	// 析构函数
	~CMyClass();

	// 重载操作符operator<
	bool operator<(const CMyClass& right) const;

	/**
	* @brief  设置id
	* @param[in] id id
	*/
	void setId(int id) { m_id = id; }
	/**
	* @brief  获取id
	* @return id
	*/
	int getId() const { return m_id; }

	/**
	* @brief  设置名字
	* @param[in] name 名字
	*/
	void setName(const QString& str);
	/**
	* @brief  获取名字
	* @return 名字
	*/
	QString getName() const;
private:
	/// 初始化数据区
	void 	initial();

	int m_id;
	QString* m_pStrName;
};


#endif  // _MYCLASS_DLL_H