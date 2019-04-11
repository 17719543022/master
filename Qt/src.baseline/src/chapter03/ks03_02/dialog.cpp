#include "dialog.h"


CDialog::CDialog(QWidget* pParent) : QDialog(pParent)
{
	setupUi(this);
	m_pLabel2->setText(tr("i like text file!"));
}

CDialog::~CDialog()
{
	
}
