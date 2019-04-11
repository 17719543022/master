/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: mdiarea.cpp
\brief 演示用头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8
*/
#include <QAction>
#include <QFileInfo>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QToolBar>

#include "mdiarea.h"
#include "graphview.h"
#include "textedit.h"

CEditMdiArea::CEditMdiArea(QMainWindow* pMainWindow) : QMdiArea(pMainWindow), m_pLastActivatedMdiChild(NULL), m_pMainWindow(pMainWindow)
{
    setViewMode(QMdiArea::TabbedView);
    createActions();
    createToolBars();
    connect(this, SIGNAL(subWindowActivated(QMdiSubWindow*)),
        this, SLOT(onSubWindowActivate(QMdiSubWindow*)));
    onSubWindowActivate(NULL);

}

CEditMdiArea::~CEditMdiArea()
{

}

bool CEditMdiArea::openFileByGraphview(const QString &fileName, QString* pError)
{
    bool succeeded = false;
    if (!fileName.isEmpty())  {
        QMdiSubWindow *existing = findGraphViewMdiChild(fileName);
        if (existing)   {
            setActiveSubWindow(existing);
            return true;
        }
        CGraphView* child = createGraphViewMdiChild(fileName, pError);
        succeeded = child->isValid();
        if (succeeded)  {
            child->showMaximized();
        }
        else  {
            if (NULL != child->parent())   {
                QMdiSubWindow* pSubWindow = dynamic_cast<QMdiSubWindow*>(child->parent());
                (NULL != pSubWindow) ? pSubWindow->close() : child->close();
            }
            else  {
                child->close();
            }
        }
    }
    else  {
        if (NULL != pError)  {
            *pError = tr("filename is empty");
        }
    }
    return succeeded;
}
void CEditMdiArea::onSubWindowActivate(QMdiSubWindow *pMdiChild)
{
    bool hasMdiChild = (pMdiChild == NULL) ? false : true;
    QWidget* pWidget = NULL;
    CGraphView* pView = NULL;
    if (hasMdiChild)   {
        if (pMdiChild != m_pLastActivatedMdiChild)   {
            if (m_pLastActivatedMdiChild != NULL)  {
                pWidget = getActiveEditView(m_pLastActivatedMdiChild);
                pView = dynamic_cast<CGraphView*>(pWidget);
                if (NULL != pView)   {
                    // 需要把槽函数跟旧视图解绑，防止旧视图信号继续触发槽函数
                    disconnectEditViewWithSlot_whenInActivate(pView);
                }
            }
            pWidget = getActiveEditView(pMdiChild);
            pView = dynamic_cast<CGraphView*>(pWidget);
            if (NULL != pView)   {
                // 将编辑视图挂接到多窗口区域的槽函数
                connectEditViewWithSlot(pView);
            }
            emit editViewChanged(pView); // 发出信号
            m_pLastActivatedMdiChild = pMdiChild;
        }
    }
   
#ifndef QT_NO_CLIPBOARD
    m_pPasteAct->setEnabled(hasMdiChild);
#endif
}
QMainWindow* CEditMdiArea::getMainWindow()
{
    return m_pMainWindow;
}

QWidget * CEditMdiArea::activeMdiChild()
{
    QWidget* pWidget = NULL;
    QMdiSubWindow *tActiveSubWindow = activeSubWindow();
    if (NULL == tActiveSubWindow)   {
        tActiveSubWindow = m_pLastActivatedMdiChild;
    }
    if (NULL != tActiveSubWindow)   {
        pWidget = getActiveEditView(tActiveSubWindow);         
    }
    return pWidget;
}

CTextEdit* CEditMdiArea::createTexteditMdiChild(const QString& fileName, QString* pError)
{
    Q_UNUSED(pError);
    CTextEdit* pTextEdit = new CTextEdit(this);
    if ((NULL != pTextEdit))   {
        if (fileName.length() > 0)  {
            pTextEdit->openFile(fileName);
        }
        QMdiSubWindow *subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(pTextEdit);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        addSubWindow(subWindow1);
        pTextEdit->setParent(subWindow1);
    }
    return pTextEdit;
}

CGraphView* CEditMdiArea::createGraphViewMdiChild(const QString& fileName, QString* /*pError*/)
{
    QGraphicsScene* pScene = new QGraphicsScene(this);
    CGraphView* pView = new CGraphView(this);
    pView->setScene(pScene);
    QRectF rct(0, 0, 400,400);
    pScene->setSceneRect(rct);
    if (fileName.length() > 0)  {
       //pView->openFile(fileName);
    }
    if ((NULL != pView) && pView->isValid())
    {
        QMdiSubWindow *subWindow1 = new QMdiSubWindow;
        subWindow1->setWidget(pView);
        subWindow1->setAttribute(Qt::WA_DeleteOnClose);
        addSubWindow(subWindow1);
        pView->setParent(subWindow1);
    }
    return pView;
}
QMdiSubWindow *CEditMdiArea::findGraphViewMdiChild(const QString &fileName)
{
    QString strFileName = QFileInfo(fileName).fileName();
    QWidget* pWidget = NULL;
    foreach(QMdiSubWindow *window, subWindowList())
    {
        pWidget = getActiveEditView(window);
        if (NULL == pWidget) {
            continue;
        }
        CGraphView* pView = dynamic_cast<CGraphView*>(pWidget);
        if (NULL != pView && pView->getFileName() == strFileName)
        {
            return window;
        }
    }
    return 0;
}
QMdiSubWindow *CEditMdiArea::findTexteditMdiChild(const QString &fileName)
{
    QString strFileName = QFileInfo(fileName).fileName();
    QWidget* pWidget = NULL;
    foreach(QMdiSubWindow *window, subWindowList())   {
        pWidget = getActiveEditView(window);
        if (NULL == pWidget) {
            continue;
        }
        CTextEdit* pView = dynamic_cast<CTextEdit*>(pWidget);
        if (NULL != pView && pView->windowTitle() == strFileName)   {
            return window;
        }
    }
    return 0;
}
QWidget* CEditMdiArea::getActiveEditView(QMdiSubWindow* pMdiChild)
{
    if (NULL == pMdiChild)   {
        return NULL;
    }

    return pMdiChild->widget();
}

void CEditMdiArea::slot_new()
{
    CGraphView* child = createGraphViewMdiChild("");
    if (NULL == child)
    {
        return;
    }
    bool succeeded = child->isValid();
    if (succeeded)
    {
        child->showMaximized();
    }
    else
    {
        child->close();
    }
}

bool CEditMdiArea::openFileByTextview(const QString& fileName, QString* pError)
{
    bool succeeded = false;
    if (!fileName.isEmpty()) {
        QMdiSubWindow *existing = findTexteditMdiChild(fileName);
        if (existing) {
            setActiveSubWindow(existing);
            return true;
        }
        CTextEdit* child = createTexteditMdiChild(fileName, pError);
        if (NULL != child) {
            child->showMaximized();
        }
        else {
            if (NULL != child->parent()) {
                QMdiSubWindow* pSubWindow = dynamic_cast<QMdiSubWindow*>(child->parent());
                (NULL != pSubWindow) ? pSubWindow->close() : child->close();
            }
            else {
                child->close();
            }
        }
    }
    else {
        if (NULL != pError) {
            *pError = tr("filename is empty");
        }
    }
    return succeeded;
}
void CEditMdiArea::slot_openTextGraphFile(const QString& fileName)
{
    openFileByTextview(fileName, NULL);
}
void CEditMdiArea::onViewClose(QWidget* pChild)
{
    if (pChild == NULL)
    {
        return;
    }

    CGraphView* pView = dynamic_cast<CGraphView*>(pChild);
    if (NULL != pView)   {
        disconnectEditViewWithSlot(pView); // 将编辑视图与多窗口区域的槽函数断开连接
    }
    m_pLastActivatedMdiChild = NULL;

    emit editViewClose(pChild);
    m_pLastActivatedMdiChild = NULL; // 防止应用层对于 editViewClose 信号的处理导致触发activeSubWindow从而使m_pLastActivatedMdiChild重新被赋值（为已关闭的窗口）

}

void CEditMdiArea::connectEditViewWithSlot(CGraphView* pView)
{
    connect(pView, SIGNAL(viewMouseMove(QMouseEvent*)), 
        this, SIGNAL(viewMouseMove(QMouseEvent*)));
    connect(pView, SIGNAL(viewClose(QWidget*)), 
        this, SLOT(onViewClose(QWidget*)));
    connect(pView, SIGNAL(openGraphFile(const QString&)),
        this, SLOT(slot_openTextGraphFile(const QString&)));
}

void CEditMdiArea::disconnectEditViewWithSlot(CGraphView* pView)
{
    disconnectEditViewWithSlot_whenInActivate(pView);
    disconnect(pView, SIGNAL(viewClose(QWidget*)), 
        this, SLOT(onViewClose(QWidget*)));
}

void CEditMdiArea::disconnectEditViewWithSlot_whenInActivate(CGraphView* pView)
{
    disconnect(pView, SIGNAL(viewMouseMove(QMouseEvent*)),
        this, SIGNAL(viewMouseMove(QMouseEvent*)));
    disconnect(pView, SIGNAL(openGraphFile(const QString&)),
        this, SLOT(slot_openTextGraphFile(const QString&)));
}

void CEditMdiArea::createActions()
{
    m_pNewAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    m_pNewAct->setShortcuts(QKeySequence::New);
    m_pNewAct->setStatusTip(tr("New File"));
    connect(m_pNewAct, &QAction::triggered, this, &CEditMdiArea::slot_new);

    m_pOpenAct = new QAction(QIcon(":/images/open.png"), tr("&New"), this);
    m_pOpenAct->setShortcuts(QKeySequence::Open);
    m_pOpenAct->setStatusTip(tr("Open File"));
    connect(m_pOpenAct, &QAction::triggered, this, &CEditMdiArea::slot_open);

#ifndef QT_NO_CLIPBOARD
    m_pCutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    m_pCutAct->setShortcuts(QKeySequence::Cut);
    m_pCutAct->setStatusTip(tr("Cut the current selection's contents to the "
        "clipboard"));
    connect(m_pCutAct, &QAction::triggered, this, &CEditMdiArea::slot_cut);

    m_pCopyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    m_pCopyAct->setShortcuts(QKeySequence::Copy);
    m_pCopyAct->setStatusTip(tr("Copy the current selection's contents to the "
        "clipboard"));
    connect(m_pCopyAct, &QAction::triggered, this, &CEditMdiArea::slot_copy);

    m_pPasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    m_pPasteAct->setShortcuts(QKeySequence::Paste);
    m_pPasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
        "selection"));
    connect(m_pPasteAct, &QAction::triggered, this, &CEditMdiArea::slot_paste);
#endif

    m_pRectAct = new QAction(tr("addRect"), this);
    m_pRectAct->setStatusTip(tr("add rect to view"));
    connect(m_pRectAct, &QAction::triggered, this, &CEditMdiArea::slot_addRect);

    m_pEllipseAct = new QAction(tr("addEllipse"), this);
    m_pEllipseAct->setStatusTip(tr("add ellipse to view"));
    connect(m_pEllipseAct, &QAction::triggered, this, &CEditMdiArea::slot_addEllipse);

}

void CEditMdiArea::createToolBars()
{
    m_pEditToolBar = m_pMainWindow->addToolBar(tr("edit tool bar"));
    m_pEditToolBar->setObjectName("edit tool bar");
    m_pEditToolBar->addAction(m_pNewAct);
    m_pEditToolBar->addAction(m_pOpenAct);
#ifndef QT_NO_CLIPBOARD
    m_pEditToolBar->addAction(m_pCutAct);
    m_pEditToolBar->addAction(m_pCopyAct);
    m_pEditToolBar->addAction(m_pPasteAct);
#endif

    m_pEditToolBar->addAction(m_pRectAct);
    m_pEditToolBar->addAction(m_pEllipseAct);

}

void CEditMdiArea::slot_open()
{
    openFileByGraphview("");
}

#ifndef QT_NO_CLIPBOARD
void CEditMdiArea::slot_cut()
{
    QWidget* pWidget = activeMdiChild();;
     if (NULL == pWidget)
        return;
    CGraphView* pView = dynamic_cast<CGraphView*>(pWidget);
    if (NULL == pView)
        return;
    pView->cut();
}

void CEditMdiArea::slot_copy()
{
    QWidget* pWidget = activeMdiChild();;
    if (NULL == pWidget)
        return;
    CGraphView* pView = dynamic_cast<CGraphView*>(pWidget);
    if (NULL == pView)
        return;
    pView->copy();
}

void CEditMdiArea::slot_paste()
{
    QWidget* pWidget = activeMdiChild();;
    if (NULL == pWidget)
        return;
    CGraphView* pView = dynamic_cast<CGraphView*>(pWidget);
    if (NULL == pView)
        return;
    pView->paste();
}
#endif

void CEditMdiArea::slot_addRect()
{
    QWidget* pWidget = activeMdiChild();;
    if (NULL == pWidget)
        return;
    CGraphView* pView = dynamic_cast<CGraphView*>(pWidget);
    if (NULL == pView)
        return;
    pView->addRect();
}

void CEditMdiArea::slot_addEllipse()
{
    QWidget* pWidget = activeMdiChild();;
    if (NULL == pWidget)
        return;
    CGraphView* pView = dynamic_cast<CGraphView*>(pWidget);
    if (NULL == pView)
        return;
    pView->addEllipse();
}
