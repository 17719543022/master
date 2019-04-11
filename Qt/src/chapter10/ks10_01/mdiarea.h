/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: mdiarea.h
\brief 演示用头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8
*/

#ifndef MDIAREA_H
#define MDIAREA_H

#include <QMdiArea>

QT_BEGIN_NAMESPACE
class QMdiSubWindow;
class QMainWindow;
class QGraphicsScene;
class QAction;
class QToolBar;

QT_END_NAMESPACE

class CGraphView;
class CEditMdiArea : public QMdiArea
{
    Q_OBJECT

public:
/**
	* @brief			构造函数
	* @param[in] pMainWindow	父窗口
	*/
    CEditMdiArea(QMainWindow* pMainWindow);
	/// 析构函数
    virtual ~CEditMdiArea();

public:
	/**
	* @brief 获取主窗口
	* @return 主窗口
	*/
    QMainWindow* getMainWindow();
	/**
	* @brief 获取当前活动视图
	* @return 当前活动视图
	*/
    CGraphView *activeMdiChild();
    /**
    * @brief 获取当前活动编辑视图
    * @param[in] pMdiChild subwindow对象
    * @return 当前活动编辑视图
    */
    CGraphView* getActiveEditView(QMdiSubWindow* pMdiChild);

	/**
	* @brief 根据文件创建视图
	* @param[in] fileName 文件名
	* @param[in] pError 错误码
	* @return 视图对象，如果创建的模板类型不正确则返回NULL
	*/
	virtual CGraphView* createMdiChild(const QString& fileName, QString* pError = NULL);
    /**
    * @brief 查找名字为filename的子窗口对象
    * @param[in] fileName 文件名
    * return 子窗口对象
    */
    virtual QMdiSubWindow *findMdiChild(const QString &fileName);
    
    /**
    * @brief 构建菜单项对应的QAction
    * return void
    */
    void createActions();		
    
    /**
    * @brief 构建工具条
    * return void
    */
   void createToolBars();		
	/**
	* @brief 打开指定文件
	* @param[in] fileName 文件所在路径名
	* @param[in] pError 错误码
	* @retval true 打开文件成功
	* @retval true 打开文件失败
	*/
	bool openFile(const QString &fileName, QString* pError = NULL);
   
private slots:
    void slot_new();
    void slot_open();

    void slot_addRect();
    void slot_addEllipse(); 

#ifndef QT_NO_CLIPBOARD
	/// 剪切
    void slot_cut();
	/// 拷贝
    void slot_copy();
 	/// 黏贴
   void slot_paste();
#endif
    /**
	*	@brief				视图关闭的槽函数
	*	@param[in] pView	视图指针
	*/
	virtual void onViewClose(QWidget*);

    /**
    * @brief 窗口激活消息处理
    * @param[in] pMdiChild 窗口指针
    */
    virtual void onSubWindowActivate(QMdiSubWindow *pMdiChild);

Q_SIGNALS:
    void viewMouseMove(const QPointF&);
    void editViewChanged(QWidget*);
    void editViewClose(QWidget*);
private:
    /**
    * @brief 将编辑视图挂接到多窗口区域的槽函数
    * @param[in] pView 编辑视图
    */
    void connectEditViewWithSlot(CGraphView* pView);
    /**
    * @brief 当编辑视图变为非激活状态时,将编辑视图与多窗口区域的槽函数断开连接
    * @param[in] pView 编辑视图
    */
    void disconnectEditViewWithSlot_whenInActivate(CGraphView* pView);
    /**
    * @brief 将编辑视图与多窗口区域的槽函数断开连接
    * @param[in] pView 编辑视图
    */
    void disconnectEditViewWithSlot(CGraphView* pView);
private:
	QMdiSubWindow *m_pLastActivatedMdiChild; /// 上个激活的窗口(焦点窗口)
	QMainWindow* m_pMainWindow;	// 主窗口指针
    QToolBar *m_pEditToolBar;	/// 编辑工具条
    QAction *m_pNewAct;			/// 新建
    QAction *m_pOpenAct;		/// 打开文件

#ifndef QT_NO_CLIPBOARD
    QAction *m_pCutAct;			/// 剪切
    QAction *m_pCopyAct;		/// 复制
    QAction *m_pPasteAct;		/// 黏贴
#endif
    QAction *m_pRectAct;        /// 添加矩形
    QAction *m_pEllipseAct;     /// 添加椭圆
};

#endif // MDIAREA_H
