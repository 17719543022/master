/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: main.cpp
\brief mian()������ʵ���ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/8
*/

#include "qglobal.h"
#include <iostream>

#include "config.h"

#include "myclass.h"


using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

    CModel model;
    model.initialize();

    qreal r = 0.f;// todo������CConfig��getSelectRadius()�ӿ�����ȡ���ò�����
    cout << "r = " << r << endl;
	return 0;
}
