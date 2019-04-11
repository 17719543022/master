#include "dialog.h"


CDialog::CDialog(QWidget* pParent) : QDialog(pParent)
{
	setupUi(this);
	//m_pLabel2->setText(  tr("this is translated by source code.")   );
	m_pLabel2->setText( tr( "this is translated by source code." )  );
}

CDialog::~CDialog()
{
	
}
