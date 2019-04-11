
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
	//�����ñ�������
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

	//�����ñ�������ǩ
	void setTitleLable(QLabel* pTitleLable);

	//���������˵���ť
	void setMainMenuBtn(CMyPushButton* pMainMenuBtn);
	CMyPushButton* getMainMenuBtn(void) const;

	//����ӹ������л���ť
	void addPageToggleBtn(CPageToggleButton* pPageToggleBtn);

	//! ���ù�����������ť
	void setToolContainerShowBtn(CMyPushButton* pToolContainerShow);

	//! ������󻯰�ť
	void setMaximizeBtn(CMyPushButton* pMaximizeBtn);

	//! ������С����ť
	void setMinimizeBtn(CMyPushButton* pMinimizeBtn);

	//�����ùرհ�ť
	void setCloseBtn(CMyPushButton* pCloseBtn);

	//! ���ù���������
	void setToolBarContainer(CToolBarContainer* pToolBarContainer);

	//! ����������ʼ������ʼ��ǰ��Ҫ���������ؼ�
	void initInstance();

private:
	//�Ƿ�ʹ�ñ���ͼƬ
	bool m_bUseBackgroundPixmap;

	//���������ı���ͼƬ
	QPixmap m_backgroundPixmap;

	//���������ı���ɫ
	QColor m_backgroundColor;

private:
	//! ���˵���ť
	CMyPushButton* m_pMainMenuBtn;

	//�������ڳߴ����
	CMyPushButton* m_pMinimizeBtn;							//��С����ť
	CMyPushButton* m_pMaximizeBtn;							//��󻯰�ť
	CMyPushButton* m_pCloseBtn;								//�رհ�ť
	
	//! ������������������
	QMap<QString, CPageToggleButton*> m_pPageToggleBtns;	//������ҳ���л���ť
	CToolBarContainer* m_pToolBarContainer;					//����������������
	CMyPushButton* m_pToolBarContainerShowBtn;				//������������ť
	bool m_bToolContainerShowFlag;							//��������ʾ��־

	//�������������ֿ��
	QFrame* m_pGeneralBarFrame;

	//! ��������ǩ
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
