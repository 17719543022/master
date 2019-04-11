/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief  CDialog

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#include <QLabel>
#include "dialog.h"
#include "recvthread.h"
#include "sendthread.h"
#include "customevent.h"


CDialog::CDialog(QWidget* pParent) : QDialog(pParent),m_pRecvThread(new CRecvThread),m_pSendThread(new  CSendThread) {
	ui.setupUi(this);
	
    m_pSendThread->setDialog(this);
	connect(ui.btnStartThread, SIGNAL(clicked()), this, SLOT(on_startthread()));
}

CDialog::~CDialog(){
	
}

void CDialog::on_startthread()
{
    m_pRecvThread->start();
    m_pSendThread->start();
}

void CDialog::customEvent(QEvent *event) {
    QString str;
    CCustomEvent* pEvent = NULL;
    switch (event->type()) {
    case (QEvent::User + 1): {
        pEvent = dynamic_cast<CCustomEvent*>(event);
        if (NULL != pEvent) {
            str = QString("teacher:%1, ").arg(pEvent->getTeacherNumber());
            str += QString("student:%1\n").arg(pEvent->getStudentNumber());
            ui.textLabel->setText(str);
        }
    }
        break;
    default:
        break;
    }
}