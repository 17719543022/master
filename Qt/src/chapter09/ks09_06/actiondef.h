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
		//图形平台ACTion定义
		EAction_New = 0,						// 新建
		EAction_Open,							// 打开
		EAction_Save,							// 保存
		EAction_SaveAs,							// 另存为
		EAction_Exit,							// 退出

		EAction_Cut,							// 剪切
		EAction_Copy,							// 复制
		EAction_PasteEx,						// 不含业务粘贴
		EAction_Paste,							// 粘贴
		EAction_Undo,							// 撤销
		EAction_Redo,							// 重做

		EAction_Close,							// 关闭
		EAction_CloseAll,						// 关闭所有窗口

		EAction_Tile,							// 平铺窗口
		EAction_Cascade,						// 重叠窗口
		EAction_Next,							// 下个窗口
		EAction_Previous,						// 前一窗口

		EAction_Separator,						// 间隔器

		EAction_ResizeCanvas,					// 重设视图大小

		EAction_RotateControl,					// 任意角度旋转
		EAction_RotateRight,					// 右旋90度
		EAction_RotateLeft,						// 左旋90度
		EAction_MirrorHorizon,					// 水平镜像
		EAction_MirrorVertical,					// 垂直镜像
		EAction_ResetTransform,					// 重置矩阵		

		EAction_BringForward,					// 上移一层
		EAction_SendBackward,					// 下移一层
		EAction_Top,							// 指定层置顶
		EAction_Bottom,							// 指定层置底

		EAction_Zoomin,							// 放大
		EAction_Zoomout,						// 缩小
		EAction_Zoom,							// 原始比例
		EAction_SetZoomCoefRange,				// 设置缩放比例范围
		EAction_SetRelativeZoomCoef,			// 设置相对缩放系数
		EAction_SetViewPortCenter,				// 设置当前视口中心
		EAction_ElementCenter,					// 指定图元移动至视口中心

		EAction_CreateRect,						// 创建矩形
		EAction_CreateLine,						// 创建直线
		EAction_CreatePath,						// 创建path
		EAction_CreateBezier,					// 创建bezier曲线
		EAction_CreateAnologClock,				// 创建表盘时钟
		EAction_CreateDigitalClock,				// 创建LED时钟
		EAction_CreateBeelineScale,				// 创建直线刻度图元
		EAction_CreateArcScale,					// 创建圆弧刻度图元
		EAction_CreateGuage,					// 创建标尺图元
		EAction_CreateStick,					// 创建棒图元
		EAction_CreateCircle,					// 创建圆				
		EAction_CreateEllipse,					// 创建椭圆
		EAction_CreateArc,						// 创建弧线
		EAction_CreateChord,					// 创建弦
		EAction_CreatePolygon,					// 创建封闭折线
		EAction_CreatePolyLine,					// 创建折线
		EAction_CreateText,						// 创建文本
		EAction_CreatePlugin,					// 创建插件
		EAction_CreatePie,						// 创建pie
		EAction_CreateImg,						// 创建图片
		EAction_CreateLinkLine,					// 创建连接线
		EAction_CreateGif,						// 创建gif图片				
		EAction_CreateCurve,					// 创建曲线图元
		EAction_CreateStaticTable,				// 创建静态表格

		EAction_Bold,							// 粗体
		EAction_Italic,							// 斜体
		EAction_Underline,						// 下划线
		EAction_StrikeOut,						// 横穿线
		EAction_AdaptText,						// 文本自适应
		EAction_TextAlignTLeft,					// 文本向上左对齐
		EAction_TextAlignTRight,				// 文本向上右对齐
		EAction_TextAlignTCenter,				// 文本向上居中对齐
		EAction_TextAlignMLeft,					// 文本居中左对齐
		EAction_TextAlignMRight,				// 文本居中右对齐
		EAction_TextAlignMCenter,				// 文本居中对齐
		EAction_TextAlignBLeft,					// 文本向下左对齐
		EAction_TextAlignBRight,				// 文本向下右对齐
		EAction_TextAlignBCenter,				// 文本向下居中对齐
		EAction_TextArrangHorizontal,			// 文本按行排列
		EAction_TextArrangeVerticalRL,			// 文本按列排列，右向左
		EAction_TextArrangeVerticalLR,			// 文本按列排列，左向右
		EAction_TextAsciiRotate,				// 文本非中文旋转
		EAction_TextShowLine,					// 显示文本边框
		EAction_TextShowBackground,				// 显示文本图元背景
		EAction_TextAnimate,					// 文本动画

		EAction_Combine,						// 组合
		EAction_CancleCombine,					// 取消组合		

		EAction_Lock,							// 锁定
		EAction_UnLock,							// 取消锁定

		EAction_AlignLeft,						// 图元左对齐
		EAction_AlignRight,						// 图元右对齐
		EAction_AlignCenterHorizontal,			// 图元水平居中对齐
		EAction_AlignTop,						// 图元上对齐
		EAction_AlignBottom,					// 图元下对齐
		EAction_AlignCenterVertical,			// 图元垂直居中对齐

		EAction_EnterItemBind,					// 进入图元绑定状态
		EAction_ExitItemBind,					// 退出图元绑定状态
		EAction_Bind,							// 绑定
		EAction_CancleBind,						// 取消绑定

		EAction_SameWidth,						// 等宽
		EAction_SameHeight,						// 等高
		EAction_SameSize,						// 等尺寸
		EAction_SameHInterval,					// 水平等间距排列
		EAction_SameVInterval,					// 竖直等间距排列

		EAction_SetSelectMode,					// 鼠标进入选择模式

		EAction_TerminalActivate,				// 启用端子
		EAction_TerminalInActivate,				// 禁用端子
		EAction_AutoSetTerminalActivate,		// 自动设置端子激活状
		EAction_Roaming,						// 鼠标进入选:拖动画布模式
		EAction_LoopSelect,						// 循环选中图元
		EAction_ParentSelect,					// 仅选中父图元
		EAction_ChildSelect,					// 仅选中子图元
		EAction_Straight,						// 平直化

		///////////////////////////////////////////////////////////
		//自定义Action
		EAction_CustomNew,			//新建文件
		EAction_CustomOpen,			//打开文件
		EAction_CustomSave,			//保存文件
		EAction_CustomSaveAs,		//文件另存为
		EAction_Print,				//打印
		EAction_PrintPreview,		//打印预览
		EAction_Help,				//帮助
		EAction_About,				//关于...
		EAction_AutoNaming,			//间隔自动命名

		EAction_ShowTemplateBox,	//显示模板工具箱
		EAction_ShowPropertyBox,	//显示资源属性窗
		EAction_ShowDais,			//显示Dais视图
		EAction_ShowPropertyEdit,	//显示属性编辑窗
		EAction_ShowLayer,			//显示图层窗口
		EAction_ShowCustomBox,		//显示自定义属性窗

		EAction_Aerial,				//打开鸟瞰图
		EAction_EMS_DMS,			//EMS/DMS切换

		EAction_CheckIn,			//签入
		EAction_CheckOut,			//签出
		EAction_Compare,			//对比
		EAction_TmplImgMgr,			//模板、图片管理

		EAction_ChangeToCommon,		//切换到常用工具页
		EAction_ChangeToStart,		//切换到开始工具页
		EAction_ChangeToView,		//切换到视图工具页
		EAction_ChangeToModel,		//切换到模型工具页
		EAction_ChangeToPas,		//切换到Pas工具页
		EAction_ChangeToSystem,		//切换到系统工具页
		EAction_ChangeToFormat,		//切换到格式工具页


		EAction_Login,				//登录
		EAction_LogOut,				//注销

		EAction_CalculateEdit,		//计算公式编辑
		EAction_SaveDesEdit,		//存盘描述编辑
		EAction_AnaLimitEdit,		//模拟量限值编辑
		EAction_AccLimitEdit,		//累加量限值编辑
		EAction_EventLevelConfig,	//事项级别配置
		EAction_SignalRuleEdit,		//信号推理规则编辑

		EAction_SceneBgColor,		//	场景背景色
		EAction_SetSceneBgImage,	//	设置场景背景图片
		EAction_UnsetSceneBgImage,	//	取消设置场景背景图片
		EAction_BgImageStretch,		//	拉伸
		EAction_BgImageCenter,		//	居中
		EAction_BgImageTile,		//	平铺
		EAction_SceneSize,			//	场景尺寸

		EAction_ShowEntireGraph,	//	整图显示

		EAction_KeepPenWidth,		//	保持原始线宽进行显示

		EAction_DirectConnectShow,	//	直连显示装饰点
		EAction_BusConnectShow,		//	母线直连显示装饰点
		EAction_TConnectShow,		//	T接显示装饰点
		EAction_MultiConnectShow,	//	3条及3条以上连接线显示装饰点
		EAction_SetTrimPtRadius,	//	设置装饰点半径
		EAction_HotPoint,			//	编辑热点
		EAction_DefaultMeas,		//	编辑默认显示量测
		EAction_VersionQuery,		//	版本查询
		EAction_AssessCurveEdit,	//	考核曲线编辑
		EAction_GraphModelCheck,	//  图模检查
		EAction_Context,			//	编辑态
		EAction_ImportantUsrEdit,	//	重要用户编辑器
		EAction_MonitSysEdit,		//	监视系统编辑器
		EAction_DutyPersonEdit,		//	值班人员编辑器

		EAction_AutoDevice,			//	配置自动装置
		EAction_SingleProtect,		//	单个配置保护
		EAction_BatchProtect,		//	批量配置保护
		EAction_SingleReclose,		//	单个配置重合闸
		EAction_BatchReclose,		//	批量配置重合闸
		EAction_UFLS,				//	配置低频减载
		EAction_UVLS,				//	配置低压减载
		EAction_DeviceType,			//	配置保护装置类型

		EAction_CreatePieChart,		// 创建饼图
		EAction_CreateBarChart,		// 创建棒图
		EAction_CreateCurveChart,	// 创建曲线图
		EAction_CreateTablePlugin,	// 创建动态表格图元
		EAction_CreateMeterChart,	// 创建表记图
		EAction_CreateRadarChart,	// 创建雷达图

		EAction_UpdateModel,		// 更新模型
		EAction_ReloadModel,		// 重读模型
	};

	enum EDrawWidget
	{
		// QToolButton
		EToolButton_Format = 0,					// 格式刷
		EToolButton_PenColor,					// 画笔颜色
		EToolButton_PenWidth,					// 画笔宽度
		EToolButton_PenStyle,					// 画笔样式
		EToolButton_PenCapStyle,				// 画笔线端样式
		EToolButton_PenJoinStyle,				// 画笔拐点样式
		EToolButton_BrushColor,					// 画刷颜色
		EToolButton_BrushStyle,					// 画刷样式
		EToolButton_ViewGrid,					// 网格设置
		EToolButton_CoordinateAxis,				// 坐标轴设置
		EToolButton_TextColor,					// 文本颜色
		EToolButton_TextDigits,					// 文本小数位数

		// QComboBox
		EComboBox_FontSize = 100,				// 字体大小
		EComboBox_Font, 						// 字体族
		EComboBox_TextFormatter,				// 文本格式化器
	};

	Q_ENUM(EDrawAction)
	Q_ENUM(EDrawWidget)
};

#endif