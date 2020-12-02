#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommonMisc/THCommon_UI.h"
#include "../Joystick/THJoystick.h"
#include "THHaveJoystick2ConfigInterface.generated.h"

// 【】TODO 之后整理成Dynamic, 一层调一层，改起来也麻烦; 【】TODO 后续应当可以整理成一个接口，不必Joystick一个，Bind的一个
DECLARE_DELEGATE_ThreeParams(FHandlerOwnedJoystick_OnTouchTick, float, float, bool);
DECLARE_DELEGATE_SevenParams(FHandlerOwnedJoystick_OnTouchStart, const EJoystickHandleTouchType&, const int32&, const FVector2D&, const FVector2D&, const FJoystickControlInfo&, const FThumbOrientationInfo&, const float&);
DECLARE_DELEGATE_SevenParams(FHandlerOwnedJoystick_OnTouchEnd, const EJoystickHandleTouchType&, const int32&, const FVector2D&, const FVector2D&, const FJoystickControlInfo&, const FThumbOrientationInfo&, const float&);
DECLARE_DELEGATE_SevenParams(FHandlerOwnedJoystick_OnTouchMove, const EJoystickHandleTouchType&, const int32&, const FVector2D&, const FVector2D&, const FJoystickControlInfo&, const FThumbOrientationInfo&, const float&);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHHaveJoystick2ConfigInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 配置内含摇杆的Widget接口
 */
class UIMODULE_API ITHHaveJoystick2ConfigInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Init();			// 【】TODO 此Interface在前端，更换为设置“LayoutWidget"

	bool GetJoystickControls(TArray<FJoystickControlInfo>& JoystickControlInfo);
	const float GetfJoystickScaleFactor();						// DPI缩放倍率
	bool GetJoystickThumbInfo(FThumbOrientationInfo& ThumbOrientationInfo);
	//bool GetJoystickTickInfo(FJoystickTickInfo& JoystickTickInfo);

	virtual void UpdateControlInfo(FControlConfig InControlInfo);
	virtual void UpdateImg_JoystickThumb(FSlateBrush InJoystickThumb);
	virtual void UpdateImg_JoystickBGI(FSlateBrush InJoystickBGI);
	virtual void UpdatebPressedShowJoystickImg(bool InbNewState);

public:
	virtual void InitConfigStyle_OwnedJoystick() = 0;
	virtual void ClearAllPlayerOperate();

	// 非PreventCenter模式下，限制摇杆的出现位置在一个矩形范围内（坐标系与左上角固定锚点相同）
	virtual bool LimitJoystickPosOnNoPreventCenter(FVector2D InVec2_RecLeftUp, FVector2D InVec2_RecRightBottom, FVector2D& InVec2_ResultLoc);

protected:
	virtual class UTHGameJoystick* GetJoystick() = 0;
	virtual void InitRegisterOwnedJoystickBehavior2SelfCallback() = 0;		// 后续询问并改成AddDynamic

	UFUNCTION() virtual void ExecuteOnTouchStart(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale);
	UFUNCTION() virtual void ExecuteOnTouchEnd(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale);
	UFUNCTION() virtual void ExecuteOnTouchMove(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale);
	UFUNCTION() virtual void ExecuteOnTouchTick(float xAxis, float yAxis, bool InbIsTouchEndedTick);

public:
	//FUIBehaviorOneParam_OwnedBtnOnClicked_DynamicTest Handler_OwnedBtnOnClicked_dynamic;			// 【】TODO TEST
	FHandlerOwnedJoystick_OnTouchTick Handler_OnTouchTick;
	FHandlerOwnedJoystick_OnTouchStart Handler_OnTouchStart;
	FHandlerOwnedJoystick_OnTouchEnd Handler_OnTouchEnd;
	FHandlerOwnedJoystick_OnTouchMove Handler_OnTouchMove;

#pragma region RefreshUI
public:
	void ShowJoystickTumbImg(bool InbShow);
	void ShowJoystickVisualBGI(bool InbShow);
	virtual void RefreshUI_JoystickRepositionOrResize();	// Joystick修改大小/位置后刷新图像显示（不刷新将导致UI显示大小不对，感应区错误）
#pragma endregion RefreshUI

public:
	void RecoverFocusToJoystick();		// 恢复焦点

#pragma region >>> Function Delegate <<< 
public:
	template<typename ClassType>
	void BindOnTouchStart(ClassType* Object, typename FHandlerOwnedJoystick_OnTouchStart::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnTouchStart();
		Handler_OnTouchStart.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnTouchEnd(ClassType* Object, typename FHandlerOwnedJoystick_OnTouchEnd::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnTouchEnd();
		Handler_OnTouchEnd.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnTouchMove(ClassType* Object, typename FHandlerOwnedJoystick_OnTouchMove::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnTouchMove();
		Handler_OnTouchMove.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnTouchTick(ClassType* Object, typename FHandlerOwnedJoystick_OnTouchTick::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnTouchTick();
		Handler_OnTouchTick.BindUObject(Object, Func);
	}

	inline void ClearOnTouchStart()
	{
		Handler_OnTouchStart.Unbind();
	}
	void ClearOnTouchEnd()
	{
		Handler_OnTouchEnd.Unbind();
	}
	void ClearOnTouchMove()
	{
		Handler_OnTouchMove.Unbind();
	}
	void ClearOnTouchTick()
	{
		Handler_OnTouchTick.Unbind();
	}
#pragma endregion
};
