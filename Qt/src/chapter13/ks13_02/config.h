/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: config.h
\brief exe+dll编程示例，单体类的定义头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/3
* 
*/

#ifndef _KS12_03_CONFIG_H
#define _KS12_03_CONFIG_H

#include <qglobal.h>
#include <QMutex>

class CConfig {
public:
    /**
    * @brief  单体对象访问接口
    * @return 单体对象的引用
    */
    static CConfig& instance();
    /**
    * @brief  设置教师人数
    * @param[in] n  教师人数
    */
    void setTeacherNumber(quint16 n);
    /**
    * @brief  获取教师人数
    * @return 教师人数
    */
    quint16 getTeacherNumber();

    /**
    * @brief  设置学员人数
    * @param[in] n  学员人数
    */
    void setStudentNumber(quint16 n);
    /**
    * @brief  获取学员人数
    * @return 学员人数
    */
    quint16 getStudentNumber();
private:    
    /**
    * @brief  构造函数，定义为私有的目的是防止他人使用该类构造对象。
    * @return 无
    */
    CConfig():m_nTeacherNumber(0), m_nStudentNumber(0){}

    /**
    * @brief  拷贝构造函数，定义为私有的目的是防止编译器调用默认的拷贝构造
    *         函数隐式构造该类的对象。
    * @return 无
    */
    CConfig(const CConfig&);
    
    /**
    * @brief  析构造函数，定义为私有的目的是防止他人用delete语句删除单体对象。
    * @return 无
    */
    ~CConfig() {}


 private:
   static CConfig m_config;     /// 静态对象
   qint16 m_nTeacherNumber;     /// 教师人数
   qint16 m_nStudentNumber;     /// 学员人数
   QMutex m_mtx;                /// 保护锁

};


#endif  // _KS12_03_CONFIG_H