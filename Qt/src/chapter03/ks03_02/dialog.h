#ifndef DIALOG_H
#define DIALOG_H

#include "ui_dialogbase.h" // ͷ�ļ���������: dialogbase.ui  ---> ui_dialogbase.h


// ��һ���������������ui�ļ��жԻ��������������鿴���е�����
// �ڶ����������������ui�ļ��жԻ�����������(objeceName����)�� CDialogBase
class CDialog : public QDialog, public Ui::CDialogBase
{
	Q_OBJECT
public:
	CDialog(QWidget* pParent);
	~CDialog();

private Q_SLOTS:
	void onChecked(bool checked);
};

#endif