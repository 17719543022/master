/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���
\file: dialog.h
\brief mian()������ʵ���ļ�


\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/8
*/
#include <QApplication>

#include "ctrlwindow.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
	CCtrlWindow ctrlWindow;
	ctrlWindow.show();
    return app.exec();
}
