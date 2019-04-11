/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: myclass.h
\brief exe+dll编程示例，单体类的定义头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 
* please import ks04_19_dll.dll
*/

#ifndef _KS19_CONFIG_DLL_H
#define _KS19_CONFIG_DLL_H


// 动态库导出宏定义
#ifdef WIN32		// windows platform
#	if defined __KS04_19_CONFIG_DLL_SOURCE__
#		define KS04_19_CONFIG_Export __declspec(dllexport)
#	else
#		define KS04_19_CONFIG_Export __declspec(dllimport)
#	endif

#else				// other platform
#  define KS04_19_CONFIG_Export
#endif // WIN32

#include <qglobal.h>

class KS04_19_CONFIG_Export CConfig {
public:
    /**
    * @brief  构造函数，定义为私有的目的是防止他人使用该类构造对象。
    * @return 无
    */
    CConfig(){}
    /**
    * @brief  析构造函数，定义为私有的目的是防止他人用delete语句删除单体对象。
    * @return 无
    */
	~CConfig(){}  
	/**
    * @brief  设置鼠标点选图元时的碰撞半径
    * @param[in] dR  半径
    */
    void setSelectRadius(qreal dR) { m_dSelectRadius = dR; }
    /**
    * @brief  获取鼠标点选图元时的碰撞半径
    * @return 半径
    */
    qreal getSelectRadius() const { return m_dSelectRadius; }
private:    
   


 private:
   static CConfig s_config;	    /// 配置对象实例
   qreal m_dSelectRadius;       /// 鼠标监测半径

};


#endif  // _KS19_CONFIG_DLL_H