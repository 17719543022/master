#ifndef _UITYPEDEF_H_
#define _UITYPEDEF_H_

#include <QObject>

//��UI�ؼ�ͼƬ��׺����
const QString SingleStateIcon = ".png";
const QString NormalIcon = "_norm.png";
const QString OverIcon = "_over.png";
const QString DownIcon = "_down.png";
const QString UnableIcon = "_dis.png";

//! UI�ؼ�����
enum eUiToolType
{
	e_SingleTool,		//�����߿ؼ�
	e_MultiTool,		//�๤��ѡ��ؼ�
};
//! UI�ؼ����Ͷ���
class CUiTypeenum : public QObject
{
	Q_OBJECT
public:
	CUiTypeenum() {}

	//�ؼ����Ͷ���
	enum EUiType
	{
		EMyPushButton,		//�������Զ��尴ť
		EMyCheckBox,		//�������Զ���checkbox
		EMyRadioButton,		//�������Զ���radioButton
		ELable_Qt,			//QLable
		EGPWidget,			//ͼ��ƽ̨ʹ��getWidget���صĹ��ߴ��壬Ϊ���⴦��

		EHSpaceItem_Qt,		//ˮƽ����
		EVSpaceItem_Qt,		//��ֱ����
		ESeparator,			//�������ָ�����

	};

	//�ؼ������Ͷ���
	enum EUiGroupType
	{
		EGroupBar_Qt=0,				//������
		EGroupMenu_Qt,				//�˵�
		EGroupGraUnitWidget,		//����ͼԪ���ڣ�Ϊ���⹦�ܴ���
	};

	Q_ENUM(EUiType)
	Q_ENUM(EUiGroupType)
};

////////////////////////////////////////////////////////////////
//��UI�ؼ�״̬
enum EUIState
{
	eState_SingleState=0,	//��һ״̬
	eState_Normal,			//����״̬
	eState_Over,			//����״̬
	eState_Down,				//����״̬
	eState_Unable,			//������״̬
};

#endif//_UITYPEDEF_H_