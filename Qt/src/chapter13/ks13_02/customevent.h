
/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customevent.h
\brief  CCustomEvent

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#pragma once
#include <QEvent>
#include <QString>

class CCustomEvent : public QEvent {
public:
	CCustomEvent() :QEvent(QEvent::Type(QEvent::User+1)){ ; }
	~CCustomEvent() { ; }

    /**
    * @brief  设置教师人数
    * @param[in] n  教师人数
    */
    void setTeacherNumber(quint16 n) {
        m_nTeacherNumber = n;
    }
    /**
    * @brief  获取教师人数
    * @return 教师人数
    */
    quint16 getTeacherNumber() const { 
        return m_nTeacherNumber; 
    }

    /**
    * @brief  设置学员人数
    * @param[in] n  学员人数
    */
    void setStudentNumber(quint16 n) { 
        m_nStudentNumber = n; 
    }
    /**
    * @brief  获取学员人数
    * @return 学员人数
    */
    quint16 getStudentNumber() const { return m_nStudentNumber; }

private:
    qint16 m_nTeacherNumber;     /// 教师人数
    qint16 m_nStudentNumber;     /// 学员人数
};