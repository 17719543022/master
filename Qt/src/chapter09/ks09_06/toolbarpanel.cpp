
#include <QResizeEvent>

#include "toolbarpanel.h"

CToolBarPanel::CToolBarPanel(QWidget * parent,int id)
:QWidget(parent),m_id(id)
{
}

CToolBarPanel::~CToolBarPanel()
{

}

void CToolBarPanel::resizeEvent(QResizeEvent * e)
{
	resize(e->size().width(), height());
	QWidget::resizeEvent(e);
}