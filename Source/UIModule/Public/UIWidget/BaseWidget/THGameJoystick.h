// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget/UIBehaviorInterface/THJoystickBehaviorInterface.h"
#include "UIWidget/Joystick/STHJoystick.h"
#include "UIWidget/Joystick/THJoystick.h"
#include "THGameJoystick.generated.h"

/**
 * 摇杆UserWidget封装，参考VirtualJoystick; 【】TODO 后续增加对拓展Widget的分辨率变化情况处理; // 【】TODO 待改名; 应当并非为"游戏中"可用
 */
UCLASS()
class UIMODULE_API UTHGameJoystick : public UUserWidget, public ITHJoystickBehaviorInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UTHJoystick* Joystick;

public:
	// 【】TODO InnerProperties没办法对BindWidget进行配置，后续可研究其他方式; 这样传递配置太过麻烦
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "显示拇指按钮")) uint8 bShowJoystickThumb : 1;
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "显示摇杆背景")) uint8 bShowJoystickBG : 1;
	// 【】TODO 摇杆以及Thumb应该分开
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "手指按下时方才显示摇杆及拇指")) uint8 bPressedShowJoystickImg : 1;
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "摇杆位置、大小"))	FControlConfig ControlInfo;
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "拇指图片"))	FSlateBrush JoystickThumb;
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "背景图片"))	FSlateBrush JoystickBGI;
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "摇杆可选参数设置"))	FJoystick_GlobalParameters GlobalParameter;
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "PreventCenter模式下摇杆显示限制矩形范围_左上"))	FVector2D LimitShowRectanglePos_LeftUp;
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "PreventCenter模式下摇杆显示限制矩形范围_左上"))	FVector2D LimitShowRectanglePos_RightBottom;

public:
	virtual void Init();
	virtual void UpdateControlInfo(FControlConfig InControlInfo);
	virtual void UpdateImg_JoystickThumb(FSlateBrush InJoystickThumb);
	virtual void UpdateImg_JoystickBGI(FSlateBrush InJoystickBGI);
	virtual void UpdateSTHJoystickInfos();
	virtual void ClearPlayerOperate();
	
	const TArray<FJoystickControlInfo>& GetJoystickControls() { return JoystickControls; } 		// 当前手指操作信息（位置、大小等）
	//const FJoystickTickInfo& GetJoystickTickInfo()const { return JoystickTickInfo; }
	const float& GetfScaleFactor() const { return fScaleFactor; };						// DPI缩放倍率
	const FThumbOrientationInfo& GetfThumbInfo() const { return ThumbInfo; };			// 当前手指操作信息（详细数据：角度、线段）
	void SetGlobalParameter(const FJoystick_GlobalParameters InGlobalParameter);
	const FJoystick_GlobalParameters& GetGlobalParameters() const { return GlobalParameter; }

protected:
	virtual void NativeConstruct() override;
	FVector2D GetSelfCentreLocalPos();						// 此UserWidget.Geometry的中心点LocalPos
	float UpdateDPIScaleFactor();							// DPI缩放倍率更新 // 【】TODO 待改进; 窗口大小变化时，再进行更改
	int32 ResolveRelativePosition(float Position, float RelativeTo, float ScaleFactor);	// 将配置大小/位置 转换成实际大小/位置; 可传（设计LocalPos/ 百分比设计比例/ 负数）
	void InitConfigStyle_GameJoystick();
	virtual void OnWidgetRebuilt() override;

#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


#pragma region TouchCallback
protected:
// Basic
	// 拇指于摇杆上开始接触、移动、松开事件回调; Tick时，即持续按压摇杆时（包含按压不动情况）;  摇杆圆盘(BG)左上 -> 右下 (-1,-1) -> (1,1); 角色前进 -1; 摄像头向上偏转 1
	UFUNCTION() virtual void OnJoystickTouch(EJoystickHandleTouchType HandleTouchType, int32 ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize);
	virtual void ExecuteOnTouchTick(float xAxis, float yAxis, bool InbIsTouchEndedTick) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "--JoystickTouch--") void CallBPOnJoystickTouch(const EJoystickHandleTouchType& InHandleTouchType, const int32& InControlIndex, const FVector2D& InLocalCoord, const FVector2D& InScreenSize, const FJoystickControlInfo& InControlInfo, const FThumbOrientationInfo& InThumbInfo, const float& InfDpiScale);

	UFUNCTION(BlueprintImplementableEvent, Category = "--JoystickTouch--") void CallBPOnTouchTick(float xAxis, float yAxis, bool InbIsTouchEndedTick);
	UFUNCTION() virtual void OnJoystickInitPropertyUpdate();

	UFUNCTION(BlueprintImplementableEvent) void CallBPJoystickInitPropertyUpdate();

	/*UFUNCTION() virtual void OnMoveJoystickTouchTick(float xAxis, float yAxis) PURE_VIRTUAL(UTHGameJoystick::OnMoveJoystickTouchTick, );
	virtual void OnEmptyAreaTouchEnd() PURE_VIRTUAL(UTHGameJoystick::OnEmptyAreaTouchEnd, );
	virtual void OnTouchStart() PURE_VIRTUAL(UTHGameJoystick::OnTouchStart, );*/

#pragma endregion TouchCallback

#pragma region RefreshUI
public:
	void UpdatebShowJoystickThumb(bool InbShow);
	void UpdatebShowJoystickBG(bool InbShow);
	void UpdatebPressedShowJoystickImg(bool InbNewState);
	virtual void RefreshUI_JoystickRepositionOrResize();	// Joystick修改大小/位置后刷新图像显示（不刷新将导致UI显示大小不对，感应区错误）
#pragma endregion RefreshUI

public:
	int8 nCurrentSelectExpandWidgetIndex;					// 当前所选中的ExpandWidget	
	float fThumb2CentreDistSqr;								// 拇指当前位置距离摇杆中心点实际距离（LocalPos, 窗口缩放影响后）

	UPROPERTY(BlueprintReadWrite) float fScaleFactor;										// 当前缩放倍率
	UPROPERTY(BlueprintReadWrite) TArray<FJoystickControlInfo> JoystickControls;			// Joystick 操作信息
	UPROPERTY(BlueprintReadWrite) FThumbOrientationInfo ThumbInfo;							// 拇指当前位置信息（角度、当前位置直线延伸至椭圆边界）
	//UPROPERTY(BlueprintReadOnly) FJoystickTickInfo JoystickTickInfo;			// 【】TODO 已无用，目前这个就是Tick 的X,y 传值

public:
	// 恢复焦点
	void RecoverFocusToJoystick();
};
