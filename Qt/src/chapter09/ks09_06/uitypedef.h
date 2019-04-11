#ifndef _UITYPEDEF_H_
#define _UITYPEDEF_H_

#include <QObject>

//！UI控件图片后缀定义
const QString SingleStateIcon = ".png";
const QString NormalIcon = "_norm.png";
const QString OverIcon = "_over.png";
const QString DownIcon = "_down.png";
const QString UnableIcon = "_dis.png";

//! UI控件类型
enum eUiToolType
{
	e_SingleTool,		//单工具控件
	e_MultiTool,		//多工具选项控件
};
//! UI控件类型定义
class CUiTypeenum : public QObject
{
	Q_OBJECT
public:
	CUiTypeenum() {}

	//控件类型定义
	enum EUiType
	{
		EMyPushButton,		//工具栏自定义按钮
		EMyCheckBox,		//工具栏自定义checkbox
		EMyRadioButton,		//工具栏自定义radioButton
		ELable_Qt,			//QLable
		EGPWidget,			//图形平台使用getWidget返回的工具窗体，为特殊处理

		EHSpaceItem_Qt,		//水平弹簧
		EVSpaceItem_Qt,		//垂直弹簧
		ESeparator,			//工具栏分隔工具

	};

	//控件组类型定义
	enum EUiGroupType
	{
		EGroupBar_Qt=0,				//工具条
		EGroupMenu_Qt,				//菜单
		EGroupGraUnitWidget,		//基本图元窗口，为特殊功能窗体
	};

	Q_ENUM(EUiType)
	Q_ENUM(EUiGroupType)
};

////////////////////////////////////////////////////////////////
//！UI控件状态
enum EUIState
{
	eState_SingleState=0,	//单一状态
	eState_Normal,			//正常状态
	eState_Over,			//焦点状态
	eState_Down,				//按下状态
	eState_Unable,			//不可用状态
};

#endif//_UITYPEDEF_H_