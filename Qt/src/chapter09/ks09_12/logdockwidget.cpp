/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: logdockwidget.cpp
\brief 日志窗口类实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/01
*/

#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>

#include "logdockwidget.h"
#include "logevt.h"


const int maxLogNum = 1000;	// 日志窗口显示的最大日志数目

/**
* @brief 构造函数
* @param[in] title	日志悬浮窗的标题
* @param[in] parent 日志悬浮窗的父对象
* @param[in] flags	日志悬浮窗的标志
*/
CLogDockWidget::CLogDockWidget(const QString &title, QWidget *parent/* = 0*/, Qt::WindowFlags flags/* = 0*/) : QDockWidget(title, parent, flags), m_pTableWidget(NULL)
{
	Q_UNUSED(title);
	Q_UNUSED(parent);
	Q_UNUSED(flags);
	m_pTableWidget = new QTableWidget(this);
	m_pTableWidget->setColumnCount(3);
	QFont font = m_pTableWidget->horizontalHeader()->font();	// 设置表头字体加粗
	font.setBold(true);
	m_pTableWidget->horizontalHeader()->setFont(font);
	m_pTableWidget->horizontalHeader()->setFixedHeight(25); //设置表头的高度
	m_pTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	m_pTableWidget->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("级别") << QString::fromLocal8Bit("时间") << QString::fromLocal8Bit("内容"));
	m_pTableWidget->setColumnWidth(0, 100);
	m_pTableWidget->setColumnWidth(1, 100);
	m_pTableWidget->horizontalHeader()->setStretchLastSection(true);
	m_pTableWidget->setShowGrid(false); //设置不显示格子线
	m_pTableWidget->verticalHeader()->setHidden(true);	// 设置垂直表头不可见
	m_pTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	setWidget(m_pTableWidget);
}

//! 析构函数
CLogDockWidget::~CLogDockWidget()
{

}

/**
* @brief 在日志悬浮窗中显示日志
* @param[in] QEvent	日志事件
*/
void CLogDockWidget::customEvent(QEvent* e)
{
	CLogEvt* pLogEvt = dynamic_cast<CLogEvt*>(e);
	
	if (NULL != pLogEvt)
	{
		SLog log = pLogEvt->getLog();

		int rowIndex = m_pTableWidget->rowCount();
		while (rowIndex >= maxLogNum)
		{//删除最后的
			m_pTableWidget->removeRow(rowIndex - 1);
			rowIndex--;
		}		
		//新增的永远加到最前面
		m_pTableWidget->insertRow(0);
		m_pTableWidget->setItem(0, 0, new QTableWidgetItem(SLog::translateLevel(log.level)));
		m_pTableWidget->setItem(0, 1, new QTableWidgetItem(log.time.toString()));
		m_pTableWidget->setItem(0, 2, new QTableWidgetItem(log.msg));
	}
}