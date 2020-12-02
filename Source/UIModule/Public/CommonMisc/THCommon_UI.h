#pragma once

#include "EngineMinimal.h"
#include "Engine/EngineTypes.h"
#include "Engine/DataTable.h"
#include "Components/CanvasPanelSlot.h"
#include "THCommon_UI.generated.h"

#pragma region Operator UILayout
UENUM(BlueprintType)
enum class EOperatorWidgetType : uint8
{
	None,
	LeftAttack,		// 左侧攻击
	RightAttack,	// 右侧攻击
	Jump,			// 跳跃
	Bag,			// 背包
	AreaMap,		// 局部地图
	FullMap,		// 全展开地图
	MoveJoystick,	// 移动摇杆
	FastRun,		// 快跑
	RoleState,		// 角色状态
	Setting,		// 设置
	AutoFire,		// 自动开火
	Skill_1,		// 技能1
	Skill_2,		// 技能2
	Skill_3,		// 技能3
	Skill_4,		// 技能4
	Signal,			// 信号
	Interact,		// 交互
	InterruptInteraction,	// 中断 操作(/交互)

	Max				UMETA(Hidden)
};

static const char* StrEnumOperatorWidgetType[] =
{
	"Other",
	"LeftAttack",
	"RightAttack",
	"Jump",
	"Bag",
	"AreaMap",
	"FullMap",
	"MoveJoystick",
	"FastRun",
	"RoleState",
	"Setting",
	"AutoFire",
	"Skill_1",
	"Skill_2",
	"Skill_3",
	"Skill_4",
	"Signal",
	"Interact",
	"InterruptInteraction",
};
#pragma endregion Operator UILayout

#pragma region Custom UILayout
// 表层组件信息
USTRUCT(BlueprintType)
struct FCustomWidgetInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) FGeometry PreEditGeometry;
	UPROPERTY(BlueprintReadWrite) FAnchorData PreEditLayoutData;

	UPROPERTY(BlueprintReadWrite) FVector2D WidgetSize;
	UPROPERTY(BlueprintReadWrite) FVector2D WidgetLocalPos;

public:
	FCustomWidgetInfo() {}
	FCustomWidgetInfo(FGeometry InPreEditGeometry, FAnchorData InPreEditLayoutData) : PreEditGeometry(InPreEditGeometry), PreEditLayoutData(InPreEditLayoutData) {}
};

// 次层面组件信息
USTRUCT(BlueprintType)
struct FCustomExpandWidgetInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) FVector2D Offset;
	UPROPERTY(BlueprintReadWrite) FVector2D Size;
	UPROPERTY(BlueprintReadWrite) FVector2D Opacity;
};

// 混杂组件（包含多个CustomSecWidget）信息
USTRUCT(BlueprintType)
struct FCustomMiscWidgetInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) FVector2D AnchorPos = { 0.f, 0.f };
	UPROPERTY(BlueprintReadWrite) FVector2D AnchorMinimum = { 0.f, 0.f };
};

USTRUCT(BlueprintType)
struct FHeroLevelExpInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Exp;
};

// 存档结构体
USTRUCT(BlueprintType)
struct FCustomWidgetSaveInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) EOperatorWidgetType Type = EOperatorWidgetType::None;
	UPROPERTY(BlueprintReadWrite) FVector2D AnchorPos = { 0.f, 0.f };		// 锚点位置;
	UPROPERTY(BlueprintReadWrite) FVector2D AnchorMinimum = { 0.f, 0.f };	// 锚点百分比位置(0,0) -> (1,1)
	UPROPERTY(BlueprintReadWrite) FVector2D Size = { 0.f, 0.f };			// 绘制大小
	UPROPERTY(BlueprintReadWrite) float Opacity = 1.f;						// 不透明度
	UPROPERTY(BlueprintReadWrite) FCustomWidgetInfo WidgetInfo;				// Widget的为遏制、大小，锚点相关信息（HUD Widget情况下存储）//【】TODO 于HUD绘制尚有用，后续修改
	UPROPERTY(BlueprintReadWrite) FCustomExpandWidgetInfo ExpandWidgetInfo;	// 拓展组件（按下拓展展示图片信息）
	UPROPERTY(BlueprintReadWrite) FCustomMiscWidgetInfo MiscWidgetInfo;		// 混杂组件信息; 暂时无用（目前以主组件坐标、大小替代Misc属性）
	
	FCustomWidgetSaveInfo() {}
	FCustomWidgetSaveInfo(const EOperatorWidgetType& InType, const FVector2D& InStartLoc, const FVector2D& InSize) : Type(InType), AnchorPos(InStartLoc), Size(InSize) {}
};
#pragma endregion Custom UILayout

#pragma region Joystick
UENUM(BlueprintType)
enum class EJoystickHandleTouchType : uint8
{
	Touch_Start,
	Touch_Move,
	Touch_End,
	Touch_Tick,		// 当不触发Tick，却需要继续传输参数时使用；持续性表现：跑步
};

USTRUCT(BlueprintType)
struct FThumbOrientationInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D ThumbOffset = FVector2D::ZeroVector;	// 拇指偏移原点（中心位置）坐标
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D LocalCoord = FVector2D::ZeroVector;	// 拇指LocalPos（鼠标事件Abs->Local)
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float Angle = 0.f;			// 以原点为中心的角度
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float CosAngle = 0.f;		// 左上右下  -1 0 1 0
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float SinAngle = 0.f;		// 左上右下  0 -1 0 1
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float XTerm = 0.f;			// 线段（起点->拇指位置->椭圆边界）X轴;  X 不是这个意思。【】TODO 后续研究
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float YTerm = 0.f;			// 线段（起点->拇指位置->椭圆边界）Y轴； X 不是这个意思。【】TODO 后续研究
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float DistanceToEdge = 0.f;	// 即以上线段（中点沿拇指位置方向至椭圆边界的线段）长度
};

// The settings and current state of each zone we render; 用户摇杆控制信息; 下层回调给上层的信息; 【】TODO 应该分开才对
USTRUCT(BlueprintType)
struct FJoystickControlInfo
{
	GENERATED_BODY()

public:
	/** The actual center of the control; 配置的中点位置（目前为Widget百分比位置） */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D Center = FVector2D(0.18f, 0.73f);

	/** The size of a joystick that can be re-centered within InteractionSize area; Cfg: BG大小 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D VisualSize = FVector2D(155.f, 155.f);

	/** The size of the thumb that can be re-centered within InteractionSize area; Cfg: Thumb大小 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D ThumbSize = FVector2D(68.f, 68.f);

	/** The size of a the interactable area around Center; Cfg: 交互区域 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D InteractionSize = FVector2D(155.f, 155.f);

	/** The scale for control input */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D InputScale = FVector2D(1.f, 1.f);

	/** The input to send from this control (for sticks, this is the horizontal/X input) 【】TODO 暂且无用*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FKey MainInputKey = EKeys::Gamepad_LeftX;

	/** The secondary input (for sticks, this is the vertical/Y input, unused for buttons) 【】TODO 暂且无用*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FKey AltInputKey = EKeys::Gamepad_LeftY;

	friend class STHJoystick;

	/**
	* Reset the control to a centered/inactive state
	*/
	void Reset() { VisualCenter = CorrectedCenter; }

	// Current state

	/** The position of the thumb, in relation to the VisualCenter; 输入：目前Touch位置 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D ThumbPosition = FVector2D::ZeroVector;

	/** For recentered joysticks, this is the re-center location; 经过校验后（PreventCenter）的最终中点坐标LocalPos */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D VisualCenter = FVector2D::ZeroVector;

	/** The corrected actual center of the control; 父层Geometry中点位置 | 中点距左上角绘制起始位置距离; 【】TODO 从某种角度来说，现在已经使用UMG进行封装，这个中点意义不大; 主要是针对TouchSize/AttackSize这样的大面积使用，确定摇杆的显示范围 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D CorrectedCenter = FVector2D::ZeroVector;

	/** The corrected size of a joystick that can be re-centered within InteractionSize area */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D CorrectedVisualSize = FVector2D::ZeroVector;

	/** The corrected size of the thumb that can be re-centered within InteractionSize area */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D CorrectedThumbSize = FVector2D::ZeroVector;

	/** The corrected size of a the interactable area around Center */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D CorrectedInteractionSize = FVector2D::ZeroVector;

	/** The corrected scale for control input */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D CorrectedInputScale = FVector2D::ZeroVector;

	/** Which pointer index is interacting with this control right now, or -1 if not interacting */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int32 CapturedPointerIndex = -1;

	/** Time to activate joystick **/
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float ElapsedTime = 0.f;

	/** Visual center to be updated */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) FVector2D NextCenter = FVector2D::ZeroVector;

	/** Whether or not to send one last "release" event next tick; 将在Released时，再次调用一次Tick，STHJoystcik用于居中Thumb图标; 【】TODO 可能废弃, 避免多增加一次无（Touch/接触）的无用Tick */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool bSendOneMoreEvent = false;

	/** Whether or not we need position the control against the geometry */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool bHasBeenPositioned = false;

	/** Whether or not to update center position */
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool bNeedUpdatedCenter = false;
};
#pragma endregion Joystick

#pragma region Backpack
// 背包区域
UENUM(BlueprintType)
enum class EBackPackParts : uint8
{
	All,
	BriefInfo,
	PropCards,
	InitiativeProp,
};

#pragma endregion Backpack

//#pragma region NormalListView
//USTRUCT(BlueprintType)
//struct FNormalItemInfo
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 nID = 0;
//	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 nNum = 0;
//};
//
//
//// ListItem基本信息
//USTRUCT(BlueprintType)
//struct FNormalListItemInfo : public FNormalItemInfo
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadOnly) class UTexture2D* Icon = nullptr;
//	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Str_1 = "";
//	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Str_2 = "";
//};
//
//
//#pragma endregion NormalListView

#pragma region HudDraw
// Hud绘制信息
// 【】TODO TEST【6】FSlateBrush不能承受USTRUCT()?
//USTRUCT(BlueprintType)
struct FHudDrawInfo
{
	//GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite) FVector2D DrawStartPos = FVector2D::ZeroVector;		// 绘制初始位置; 坐标点(0,0)位于UserWidget起始点; 目前为默认值
	UPROPERTY(BlueprintReadWrite) FVector2D DrawSize = FVector2D::ZeroVector;			// 绘制大小	/** Image to draw */
	FSlateBrush Brush;
};

#pragma endregion HudDraw

#pragma region Misc
UENUM(BlueprintType)
enum class EDragRatePivot : uint8
{
	ENormalVertical,
	ENormalHorizontal,
	EAttackVertical,
	EAttackHorizontal,
	Max					UMETA(Hidden)
};


USTRUCT(BlueprintType)
struct FTHGameSettingConfig
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 4/*, DisplayName = "画质调节"*/))
		int32 QualityLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 120/*, DisplayName = "帧数限制"*/))
		int32 MaxFPSLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 120/*, DisplayName = "帧数设置"*/))
		int32 MaxFPS_Low = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 120/*, DisplayName = "帧数设置"*/))
		int32 MaxFPS_High = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1/*, DisplayName = "音量开关"*/))
		uint8 VolumeSwitch = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 100/*, DisplayName = "BGM"*/))
		int32 BGMVolume = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 100/*, DisplayName = "音效"*/))
		int32 SoundEffectVolume = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 100/*, DisplayName = "角色语音"*/))
		int32 CharacterVolume = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 100/*, DisplayName = "玩家语音"*/))
		int32 PlayerVolume = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 100/*, DisplayName = "玩家话筒"*/))
		int32 PlayerMICVolume = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1/*, DisplayName = "辅助瞄准"*/))
		uint8 AimHelperSwitch : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1/*, DisplayName = "操作选择方案"*/))
		int32 LayoutProgramIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1/*, DisplayName = "当前分页"*/))
		int32 CurPaginationIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1/*, DisplayName = "屏幕拖拽速率"*/))
		TMap<EDragRatePivot, float> mapDragRate;

	FTHGameSettingConfig& operator=(const FTHGameSettingConfig& other)
	{

		QualityLevel = other.QualityLevel;
		MaxFPSLevel = other.MaxFPSLevel;
		VolumeSwitch = other.VolumeSwitch;
		SoundEffectVolume = other.SoundEffectVolume;
		BGMVolume = other.BGMVolume;
		CharacterVolume = other.CharacterVolume;
		PlayerVolume = other.PlayerVolume;
		PlayerMICVolume = other.PlayerMICVolume;
		AimHelperSwitch = other.AimHelperSwitch;
		MaxFPS_Low = other.MaxFPS_Low;
		MaxFPS_High = other.MaxFPS_High;
		LayoutProgramIndex = other.LayoutProgramIndex;
		CurPaginationIndex = other.CurPaginationIndex;
		mapDragRate = other.mapDragRate;

		return *this;
	}
};

#pragma endregion Misc