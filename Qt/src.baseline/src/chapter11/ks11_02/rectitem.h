/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: rectitem.h
\brief 演示用头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8
*/

#ifndef RECTGRAPHITEM_H
#define RECTGRAPHITEM_H

#include "itembase.h"

class  CGraphRectItem : public CGraphItemBase
{
public:
    CGraphRectItem(QGraphicsItem * parent = 0);

    virtual int type() const { return QGraphicsItem::UserType+1; }

	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
	/**
		 * @brief boundingRect()获取外接矩形
		 * @return 外接矩形
	*/
	virtual QRectF  boundingRect() const;
    /**
    * @brief 获取几何矩形(图元坐标系)
    * @return 几何矩形
    */
    virtual QRectF  getItemRect() const;
    /**
		 * @brief 获取形状
		 * 用来进行碰撞检测
		 * @return 形状
	*/
	virtual QPainterPath  shape() const;
    /**
    * @brief setWidth重设置矩形宽
    *
    * @param[in] dW  宽
    */
    void setWidth(qreal dW) { m_width = dW; }
    /**
    * @brief getWidth() 获取矩形宽
    *
    * @return 宽
    */
    qreal getWidth() const { return m_width; }

    /**
    * @brief setHeight重设置矩形高
    *
    * @param dH  高
    */
    void setHeight(qreal dH) { m_height = dH; }
    /**
    * @brief getHeight() 获取矩形高
    *
    * @return 高
    */
    qreal getHeight() const { return m_height; }

protected:
	/// 析构函数
	virtual ~CGraphRectItem();
private:
    qreal m_width;
    qreal m_height;
};


#endif  // RECTGRAPHITEM_H
