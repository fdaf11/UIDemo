// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "Input/Reply.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Styling/SlateBrush.h"
#include "Widgets/SLeafWidget.h"
#include "CommonMisc/THCommon_UI.h"

UENUM()
enum class THJoystickType : uint8
{
	/** 基础 */
	Default,

	/** 跑酷 */
	Packour,
};

/**
* A virtual joystsick;
* TODO: HandleTouch(End)事件后，调用的FReplay.CancelMouseCapture出现无效情况，暂以ThumbPos = 0处理
*/
class UIMODULE_API STHJoystick : public SLeafWidget
{

public:
	SLATE_BEGIN_ARGS(STHJoystick)
	{}
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);

	/**
	* Static function to return if external users should create/activate/etc a touch interface
	* Note that this function is also used internally, so even if this returns false but an SVirtualJoystick
	* is created, it won't actually show any controls
	*/
	static bool ShouldDisplayTouchInterface();

	void RecoverFocusToJoystick();

	/**
	* Shows or hides the controls (for instance during cinematics
	*/
	void SetJoystickVisibility(const bool bVisible, const bool bFade);

	void AddControl(const FJoystickControlInfo& Control)
	{
		Controls.Add(Control);
	}

	void ClearControls()
	{
		Controls.Empty();
	}

	void SetControls(const TArray<FJoystickControlInfo>& InControls)
	{
		Controls = InControls;
	}

	const TArray<FJoystickControlInfo>& GetControls() { return Controls; }

	const FThumbOrientationInfo& GetThumbOrientationInfo() { return ThumbOrienInfo; }

	/**
	* Sets parameters that control all controls
	*/
	void SetGlobalParameters(float InActiveOpacity, float InInactiveOpacity, float InTimeUntilDeactive, float InTimeUntilReset, float InActivationDelay, bool InbPreventReCenter, float InStartupDelay);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	virtual FVector2D ComputeDesiredSize(float) const override;

	virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& Event) override;
	virtual FReply OnTouchMoved(const FGeometry& MyGeometry, const FPointerEvent& Event) override;
	virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& Event) override;

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	virtual bool SupportsKeyboardFocus() const override;

	virtual void ClearAllPlayerOperate();		// 清空用户操作数据，通常用于隐藏UI时，中断用户的操作，防止摇杆卡在那儿; 目前仅清空操作Control[0]

protected:
	/** Callback for handling display metrics changes. */
	virtual void HandleDisplayMetricsChanged(const FDisplayMetrics& NewDisplayMetric);

	// 边界校正，保持在屏幕当中; 暂时无法使用 PS: 最初的ScreenSize的为此SWidget本身Geometry大小（全屏大小），后封装成UserWidget, 大小不为全屏.
	void AlignBoxIntoScreen(FVector2D& Position, const FVector2D& Size, const FVector2D& ScreenSize);

	/**
	* Process a touch event (on movement and possibly on initial touch)
	*	HandleTouchType: 0 TouchStart, 1 TouchMove, 2 Other
	*
	* @return true if the touch was successful
	*/
	virtual bool HandleTouch(EJoystickHandleTouchType HandleTouchType, int32 ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize);

	/**
	* Return the target opacity to lerp to given the current state
	*/
	float GetBaseOpacity();

	/** List of controls set by the UTouchInterface */
	TArray<FJoystickControlInfo> Controls;

	/** Global settings from the UTouchInterface */
	float ActiveOpacity;
	float InactiveOpacity;
	float TimeUntilDeactive;
	float TimeUntilReset;
	float ActivationDelay;
	float StartupDelay;

	enum EVirtualJoystickState
	{
		State_Active,
		State_CountingDownToInactive,
		State_CountingDownToReset,
		State_Inactive,
		State_WaitForStart,
		State_CountingDownToStart,
	};

	/** The current state of all controls */
	EVirtualJoystickState State;
	/** True if the joystick should be visible */
	uint32 bVisible : 1;
	/** If true, this zone will have it's "center" set when you touch it, otherwise the center will be set to the center of the zone */
	uint32 bCenterOnEvent : 1;
	/** If true, ignore re-centering */
	uint32 bPreventReCenter : 1;
	/** Target opacity */
	float CurrentOpacity;
	/* Countdown until next state change */
	float Countdown;

	// Set Resource
public:
	// 摇杆图标
	TAttribute< const FSlateBrush* > JoystickThumbImage;
	void SetJoystickThumbImage(TAttribute<const FSlateBrush*> InImage);
	// 摇杆背景图
	TAttribute< const FSlateBrush* > JoystickBGI;
	void SetJoystickBGI(TAttribute<const FSlateBrush*> InImage);
	// 自动奔跑特效		// 【】TODO 待删
	TAttribute< const FSlateBrush* > FastRunArrowImage;
	void SetFastRunArrowImage(TAttribute<const FSlateBrush*> InImage);
	// 自动奔跑按钮		// 【】TODO 待删
	TAttribute< const FSlateBrush* > FastRunButtonImage;
	void SetFastRunButtonImage(TAttribute<const FSlateBrush*> InImage);
	// 自动奔跑按钮激活特效		// 【】TODO 待删
	TAttribute< const FSlateBrush* > FastRunActiveImage;
	void SetFastRunActiveImage(TAttribute<const FSlateBrush*> InImage);
	// 自动奔跑图片		// 【】TODO 待删
	TAttribute< const FSlateBrush* > AutoRunThumbImage;
	void SetAutoRunThumbImage(TAttribute<const FSlateBrush*> InImage);

	void SetFastRunButtonImageOffsetY(float InOffsetY) { FastRunButtonImageOffsetY = InOffsetY; }		// 【】TODO 待删
	void SetAllowFastRun(bool flag) { bAllowFastRun = flag; }		// 【】TODO 待删

public:
	class UTHJoystick* UMG = nullptr;

private:		// 【】TODO 待删
	float FastRunButtonImageOffsetY = 0;
	bool bAllowFastRun = true;

#pragma region TestJoystickWidget
public:
	// BG 大小计算；需要：原配置VisualSize（√）, "AllottedGeometry"LocalSize/ Scale/ DrawSIze.GetMax()
	// FVector2D(ResolveRelativePosition(Control.VisualSize.X, AllottedGeometry.GetLocalSize().X, ScaleFactor), ResolveRelativePosition(Control.VisualSize.Y, AllottedGeometry.GetLocalSize().Y, ScaleFactor));   

	void RefreshUI_RepositionOrResize();

	void ShowTumbImg(bool InbShow);
	void ShowVisualBGI(bool InbShow);

	friend class UTHJoystick;
	friend class UTHGameJoystick;

protected:
	FThumbOrientationInfo ThumbOrienInfo;
	//FJoystickTickInfo JoystickTickInfo;
	uint8 bShowThumbImg : 1;
	uint8 bShowVisualBGI : 1;


#pragma endregion TestJoystickWidget

};
