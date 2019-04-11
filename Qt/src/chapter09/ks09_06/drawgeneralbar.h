
#ifndef _DRAWGENERALBAR_H_
#define _DRAWGENERALBAR_H_

#include <QFrame>
#include <QMap>
#include <QProxyStyle>
#include <QStyleOption>
#include <QToolBar>

class QLabel;
class QLineEdit;
class QPushButton;


class CMyPushButton;
class CPageToggleButton;
class CToolBarContainer;

class CDrawGeneralBar : public QToolBar
{
	Q_OBJECT
public:
	CDrawGeneralBar(QWidget *parent = 0);
	virtual ~CDrawGeneralBar();
//	friend class CUiCreater;

public:
	//！设置标题内容
	void setTitle(const QString& title);
    
signals:

protected:
	virtual void resizeEvent(QResizeEvent * e);

private slots:
	void setToolCantainerShow();
	void onTogglePage(int index);
	void loseFocusCantainer();

private:
	void setCurrentPage(int index);

	//！设置标题栏标签
	void setTitleLable(QLabel* pTitleLable);

	//！设置主菜单按钮
	void setMainMenuBtn(CMyPushButton* pMainMenuBtn);
	CMyPushButton* getMainMenuBtn(void) const;

	//！添加功能区切换按钮
	void addPageToggleBtn(CPageToggleButton* pPageToggleBtn);

	//! 设置功能区消隐按钮
	void setToolContainerShowBtn(CMyPushButton* pToolContainerShow);

	//! 设置最大化按钮
	void setMaximizeBtn(CMyPushButton* pMaximizeBtn);

	//! 设置最小化按钮
	void setMinimizeBtn(CMyPushButton* pMinimizeBtn);

	//！设置关闭按钮
	void setCloseBtn(CMyPushButton* pCloseBtn);

	//! 设置功能区对象
	void setToolBarContainer(CToolBarContainer* pToolBarContainer);

	//! 主工具条初始化，初始化前需要建立各个控件
	void initInstance();

private:
	//是否使用背景图片
	bool m_bUseBackgroundPixmap;

	//！工具条的背景图片
	QPixmap m_backgroundPixmap;

	//！工具条的背景色
	QColor m_backgroundColor;

private:
	//! 主菜单按钮
	CMyPushButton* m_pMainMenuBtn;

	//！主窗口尺寸控制
	CMyPushButton* m_pMinimizeBtn;							//最小化按钮
	CMyPushButton* m_pMaximizeBtn;							//最大化按钮
	CMyPushButton* m_pCloseBtn;								//关闭按钮
	
	//! 主工具条功能区控制
	QMap<QString, CPageToggleButton*> m_pPageToggleBtns;	//功能区页面切换按钮
	CToolBarContainer* m_pToolBarContainer;					//工具条功能区对象
	CMyPushButton* m_pToolBarContainerShowBtn;				//功能区消隐按钮
	bool m_bToolContainerShowFlag;							//功能区显示标志

	//！主工具条布局框架
	QFrame* m_pGeneralBarFrame;

	//! 标题栏标签
	QLabel* m_pTitleLable;


private:
	class CStyle : public QProxyStyle
	{
	public:
		CStyle(CDrawGeneralBar* pOwner){ m_pOwner = pOwner; };
		~CStyle(){};

		virtual void drawControl(ControlElement element, const QStyleOption * opt, QPainter * p, const QWidget * widget) const;
	private:
		CDrawGeneralBar* m_pOwner;
	};
};

#endif // _GENERALBAR_H_
