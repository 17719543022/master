/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: graphview.h
\brief 演示用头文件
  
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8 
*/

#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

class CGraphView : public QGraphicsView
{
	Q_OBJECT
public:
	CGraphView(QWidget* parent, const QString& strFileName="");
    ~CGraphView();

public:
    QPointF getMousePressPoint() { return m_ptView; }///获取鼠标单击点的坐标
    void addEllipse();
    void addRect();
    bool isValid();
    QString getFileName() const;

public slots:
 #ifndef QT_NO_CLIPBOARD
    void cut();     /// 剪切
    void copy();    /// 拷贝
    void paste();   /// 黏贴
#endif

Q_SIGNALS:
    void viewMouseMove(const QPointF&);
    void viewClose(QWidget*);		/// 请在收到本信号后，调用disconnect相关的signal解除。
protected:
    void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    /**
    * @brief 视图关闭事项处理。
    * 这是重载的父类函数。用于通知属性窗等进行相应处理。
    * @param event 视图关闭事项。
    */
    virtual void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    void 	createActions();

#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif

Q_SIGNALS:

private:
    void copyItems(QList<QGraphicsItem*>&);    /// 拷贝图元
private:
#ifndef QT_NO_CLIPBOARD
    QAction *m_pCutAct;         /// 剪切
    QAction *m_pCopyAct;		/// 复制
    QAction *m_pPasteAct;		/// 黏贴
#endif
    QPointF m_ptView;
    QPointF m_ptScene;
    QString m_strFileName;
};

#endif // TEXTEDIT_H