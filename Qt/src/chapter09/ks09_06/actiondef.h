#ifndef _ACTIONDEF_H_
#define _ACTIONDEF_H_

#include <QObject>

class CActionenum : public QObject
{
	Q_OBJECT
public:
	CActionenum() {}

	enum EDrawAction
	{
		///////////////////////////////////////////////
		//ͼ��ƽ̨ACTion����
		EAction_New = 0,						// �½�
		EAction_Open,							// ��
		EAction_Save,							// ����
		EAction_SaveAs,							// ���Ϊ
		EAction_Exit,							// �˳�

		EAction_Cut,							// ����
		EAction_Copy,							// ����
		EAction_PasteEx,						// ����ҵ��ճ��
		EAction_Paste,							// ճ��
		EAction_Undo,							// ����
		EAction_Redo,							// ����

		EAction_Close,							// �ر�
		EAction_CloseAll,						// �ر����д���

		EAction_Tile,							// ƽ�̴���
		EAction_Cascade,						// �ص�����
		EAction_Next,							// �¸�����
		EAction_Previous,						// ǰһ����

		EAction_Separator,						// �����

		EAction_ResizeCanvas,					// ������ͼ��С

		EAction_RotateControl,					// ����Ƕ���ת
		EAction_RotateRight,					// ����90��
		EAction_RotateLeft,						// ����90��
		EAction_MirrorHorizon,					// ˮƽ����
		EAction_MirrorVertical,					// ��ֱ����
		EAction_ResetTransform,					// ���þ���		

		EAction_BringForward,					// ����һ��
		EAction_SendBackward,					// ����һ��
		EAction_Top,							// ָ�����ö�
		EAction_Bottom,							// ָ�����õ�

		EAction_Zoomin,							// �Ŵ�
		EAction_Zoomout,						// ��С
		EAction_Zoom,							// ԭʼ����
		EAction_SetZoomCoefRange,				// �������ű�����Χ
		EAction_SetRelativeZoomCoef,			// �����������ϵ��
		EAction_SetViewPortCenter,				// ���õ�ǰ�ӿ�����
		EAction_ElementCenter,					// ָ��ͼԪ�ƶ����ӿ�����

		EAction_CreateRect,						// ��������
		EAction_CreateLine,						// ����ֱ��
		EAction_CreatePath,						// ����path
		EAction_CreateBezier,					// ����bezier����
		EAction_CreateAnologClock,				// ��������ʱ��
		EAction_CreateDigitalClock,				// ����LEDʱ��
		EAction_CreateBeelineScale,				// ����ֱ�߿̶�ͼԪ
		EAction_CreateArcScale,					// ����Բ���̶�ͼԪ
		EAction_CreateGuage,					// �������ͼԪ
		EAction_CreateStick,					// ������ͼԪ
		EAction_CreateCircle,					// ����Բ				
		EAction_CreateEllipse,					// ������Բ
		EAction_CreateArc,						// ��������
		EAction_CreateChord,					// ������
		EAction_CreatePolygon,					// �����������
		EAction_CreatePolyLine,					// ��������
		EAction_CreateText,						// �����ı�
		EAction_CreatePlugin,					// �������
		EAction_CreatePie,						// ����pie
		EAction_CreateImg,						// ����ͼƬ
		EAction_CreateLinkLine,					// ����������
		EAction_CreateGif,						// ����gifͼƬ				
		EAction_CreateCurve,					// ��������ͼԪ
		EAction_CreateStaticTable,				// ������̬���

		EAction_Bold,							// ����
		EAction_Italic,							// б��
		EAction_Underline,						// �»���
		EAction_StrikeOut,						// �ᴩ��
		EAction_AdaptText,						// �ı�����Ӧ
		EAction_TextAlignTLeft,					// �ı����������
		EAction_TextAlignTRight,				// �ı������Ҷ���
		EAction_TextAlignTCenter,				// �ı����Ͼ��ж���
		EAction_TextAlignMLeft,					// �ı����������
		EAction_TextAlignMRight,				// �ı������Ҷ���
		EAction_TextAlignMCenter,				// �ı����ж���
		EAction_TextAlignBLeft,					// �ı����������
		EAction_TextAlignBRight,				// �ı������Ҷ���
		EAction_TextAlignBCenter,				// �ı����¾��ж���
		EAction_TextArrangHorizontal,			// �ı���������
		EAction_TextArrangeVerticalRL,			// �ı��������У�������
		EAction_TextArrangeVerticalLR,			// �ı��������У�������
		EAction_TextAsciiRotate,				// �ı���������ת
		EAction_TextShowLine,					// ��ʾ�ı��߿�
		EAction_TextShowBackground,				// ��ʾ�ı�ͼԪ����
		EAction_TextAnimate,					// �ı�����

		EAction_Combine,						// ���
		EAction_CancleCombine,					// ȡ�����		

		EAction_Lock,							// ����
		EAction_UnLock,							// ȡ������

		EAction_AlignLeft,						// ͼԪ�����
		EAction_AlignRight,						// ͼԪ�Ҷ���
		EAction_AlignCenterHorizontal,			// ͼԪˮƽ���ж���
		EAction_AlignTop,						// ͼԪ�϶���
		EAction_AlignBottom,					// ͼԪ�¶���
		EAction_AlignCenterVertical,			// ͼԪ��ֱ���ж���

		EAction_EnterItemBind,					// ����ͼԪ��״̬
		EAction_ExitItemBind,					// �˳�ͼԪ��״̬
		EAction_Bind,							// ��
		EAction_CancleBind,						// ȡ����

		EAction_SameWidth,						// �ȿ�
		EAction_SameHeight,						// �ȸ�
		EAction_SameSize,						// �ȳߴ�
		EAction_SameHInterval,					// ˮƽ�ȼ������
		EAction_SameVInterval,					// ��ֱ�ȼ������

		EAction_SetSelectMode,					// ������ѡ��ģʽ

		EAction_TerminalActivate,				// ���ö���
		EAction_TerminalInActivate,				// ���ö���
		EAction_AutoSetTerminalActivate,		// �Զ����ö��Ӽ���״
		EAction_Roaming,						// ������ѡ:�϶�����ģʽ
		EAction_LoopSelect,						// ѭ��ѡ��ͼԪ
		EAction_ParentSelect,					// ��ѡ�и�ͼԪ
		EAction_ChildSelect,					// ��ѡ����ͼԪ
		EAction_Straight,						// ƽֱ��

		///////////////////////////////////////////////////////////
		//�Զ���Action
		EAction_CustomNew,			//�½��ļ�
		EAction_CustomOpen,			//���ļ�
		EAction_CustomSave,			//�����ļ�
		EAction_CustomSaveAs,		//�ļ����Ϊ
		EAction_Print,				//��ӡ
		EAction_PrintPreview,		//��ӡԤ��
		EAction_Help,				//����
		EAction_About,				//����...
		EAction_AutoNaming,			//����Զ�����

		EAction_ShowTemplateBox,	//��ʾģ�幤����
		EAction_ShowPropertyBox,	//��ʾ��Դ���Դ�
		EAction_ShowDais,			//��ʾDais��ͼ
		EAction_ShowPropertyEdit,	//��ʾ���Ա༭��
		EAction_ShowLayer,			//��ʾͼ�㴰��
		EAction_ShowCustomBox,		//��ʾ�Զ������Դ�

		EAction_Aerial,				//�����ͼ
		EAction_EMS_DMS,			//EMS/DMS�л�

		EAction_CheckIn,			//ǩ��
		EAction_CheckOut,			//ǩ��
		EAction_Compare,			//�Ա�
		EAction_TmplImgMgr,			//ģ�塢ͼƬ����

		EAction_ChangeToCommon,		//�л������ù���ҳ
		EAction_ChangeToStart,		//�л�����ʼ����ҳ
		EAction_ChangeToView,		//�л�����ͼ����ҳ
		EAction_ChangeToModel,		//�л���ģ�͹���ҳ
		EAction_ChangeToPas,		//�л���Pas����ҳ
		EAction_ChangeToSystem,		//�л���ϵͳ����ҳ
		EAction_ChangeToFormat,		//�л�����ʽ����ҳ


		EAction_Login,				//��¼
		EAction_LogOut,				//ע��

		EAction_CalculateEdit,		//���㹫ʽ�༭
		EAction_SaveDesEdit,		//���������༭
		EAction_AnaLimitEdit,		//ģ������ֵ�༭
		EAction_AccLimitEdit,		//�ۼ�����ֵ�༭
		EAction_EventLevelConfig,	//���������
		EAction_SignalRuleEdit,		//�ź��������༭

		EAction_SceneBgColor,		//	��������ɫ
		EAction_SetSceneBgImage,	//	���ó�������ͼƬ
		EAction_UnsetSceneBgImage,	//	ȡ�����ó�������ͼƬ
		EAction_BgImageStretch,		//	����
		EAction_BgImageCenter,		//	����
		EAction_BgImageTile,		//	ƽ��
		EAction_SceneSize,			//	�����ߴ�

		EAction_ShowEntireGraph,	//	��ͼ��ʾ

		EAction_KeepPenWidth,		//	����ԭʼ�߿������ʾ

		EAction_DirectConnectShow,	//	ֱ����ʾװ�ε�
		EAction_BusConnectShow,		//	ĸ��ֱ����ʾװ�ε�
		EAction_TConnectShow,		//	T����ʾװ�ε�
		EAction_MultiConnectShow,	//	3����3��������������ʾװ�ε�
		EAction_SetTrimPtRadius,	//	����װ�ε�뾶
		EAction_HotPoint,			//	�༭�ȵ�
		EAction_DefaultMeas,		//	�༭Ĭ����ʾ����
		EAction_VersionQuery,		//	�汾��ѯ
		EAction_AssessCurveEdit,	//	�������߱༭
		EAction_GraphModelCheck,	//  ͼģ���
		EAction_Context,			//	�༭̬
		EAction_ImportantUsrEdit,	//	��Ҫ�û��༭��
		EAction_MonitSysEdit,		//	����ϵͳ�༭��
		EAction_DutyPersonEdit,		//	ֵ����Ա�༭��

		EAction_AutoDevice,			//	�����Զ�װ��
		EAction_SingleProtect,		//	�������ñ���
		EAction_BatchProtect,		//	�������ñ���
		EAction_SingleReclose,		//	���������غ�բ
		EAction_BatchReclose,		//	���������غ�բ
		EAction_UFLS,				//	���õ�Ƶ����
		EAction_UVLS,				//	���õ�ѹ����
		EAction_DeviceType,			//	���ñ���װ������

		EAction_CreatePieChart,		// ������ͼ
		EAction_CreateBarChart,		// ������ͼ
		EAction_CreateCurveChart,	// ��������ͼ
		EAction_CreateTablePlugin,	// ������̬���ͼԪ
		EAction_CreateMeterChart,	// �������ͼ
		EAction_CreateRadarChart,	// �����״�ͼ

		EAction_UpdateModel,		// ����ģ��
		EAction_ReloadModel,		// �ض�ģ��
	};

	enum EDrawWidget
	{
		// QToolButton
		EToolButton_Format = 0,					// ��ʽˢ
		EToolButton_PenColor,					// ������ɫ
		EToolButton_PenWidth,					// ���ʿ��
		EToolButton_PenStyle,					// ������ʽ
		EToolButton_PenCapStyle,				// �����߶���ʽ
		EToolButton_PenJoinStyle,				// ���ʹյ���ʽ
		EToolButton_BrushColor,					// ��ˢ��ɫ
		EToolButton_BrushStyle,					// ��ˢ��ʽ
		EToolButton_ViewGrid,					// ��������
		EToolButton_CoordinateAxis,				// ����������
		EToolButton_TextColor,					// �ı���ɫ
		EToolButton_TextDigits,					// �ı�С��λ��

		// QComboBox
		EComboBox_FontSize = 100,				// �����С
		EComboBox_Font, 						// ������
		EComboBox_TextFormatter,				// �ı���ʽ����
	};

	Q_ENUM(EDrawAction)
	Q_ENUM(EDrawWidget)
};

#endif