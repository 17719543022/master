/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: myclass.h
\brief exe+dll���ʾ����������Ķ���ͷ�ļ�
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/9 
* please import ks04_02_dll.dll
*/

#ifndef _MYCLASS_DLL_H
#define _MYCLASS_DLL_H

#include "ks04_02_export.h"

namespace ns_ks04_02 {

    class KS04_02_Export CPrint {
    public:
        CPrint() {}
        ~CPrint() {}
    public:
        void printOnScreen(const char*);
    };

    KS04_02_Export int func1();
    KS04_02_Export int func2(int, float);

}
#endif  // _MYCLASS_DLL_H