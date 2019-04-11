/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dll.cpp
\brief	
\author 女儿叫老白  星点分享: http://xingdianketang.cn/

\Date 2018/9 

*/
#include "config.h"

#include <QMutex>
#include <QMutexLocker>

///////////////////////////////////////////////////////////////////
CConfig CConfig::m_config;
CConfig& CConfig::instance() {
 //   QMutexLocker mtx(&g_mtx);
    return m_config;
}
void CConfig::setTeacherNumber(quint16 n) { 
    QMutexLocker mtx(&m_mtx);
    m_nTeacherNumber = n; 
}


quint16 CConfig::getTeacherNumber() { 
    QMutexLocker mtx(&m_mtx);
    return m_nTeacherNumber;
}

void CConfig::setStudentNumber(quint16 n) {
    QMutexLocker mtx(&m_mtx);
    m_nStudentNumber = n;
}


quint16 CConfig::getStudentNumber() { 
    QMutexLocker mtx(&m_mtx);
    return m_nStudentNumber;
}
