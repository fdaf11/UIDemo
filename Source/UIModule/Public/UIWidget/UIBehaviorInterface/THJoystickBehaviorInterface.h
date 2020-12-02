// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommonMisc/THCommon_UI.h"
#include "THJoystickBehaviorInterface.generated.h"

DECLARE_DELEGATE_ThreeParams(FHandlerJoystick_OnTouchTick, float, float, bool);
DECLARE_DELEGATE_SevenParams(FHandlerJoystick_OnTouchStart, const EJoystickHandleTouchType&, const int32&, const FVector2D&, const FVector2D&, const FJoystickControlInfo&, const FThumbOrientationInfo&, const float&);
DECLARE_DELEGATE_SevenParams(FHandlerJoystick_OnTouchEnd, const EJoystickHandleTouchType&, const int32&, const FVector2D&, const FVector2D&, const FJoystickControlInfo&, const FThumbOrientationInfo&, const float&);
DECLARE_DELEGATE_SevenParams(FHandlerJoystick_OnTouchMove, const EJoystickHandleTouchType&, const int32&, const FVector2D&, const FVector2D&, const FJoystickControlInfo&, const FThumbOrientationInfo&, const float&);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHJoystickBehaviorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 摇杆交互事件接口
 * By ZhanZiqi 200422
 */
class UIMODULE_API ITHJoystickBehaviorInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	UFUNCTION() virtual void ExecuteOnTouchStart(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale);
	UFUNCTION() virtual void ExecuteOnTouchEnd(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale);
	UFUNCTION() virtual void ExecuteOnTouchMove(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale);
	UFUNCTION() virtual void ExecuteOnTouchTick(float xAxis, float yAxis, bool InbIsTouchEndedTick);

	FHandlerJoystick_OnTouchTick Handler_OnTouchTick;
	FHandlerJoystick_OnTouchStart Handler_OnTouchStart;
	FHandlerJoystick_OnTouchEnd Handler_OnTouchEnd;
	FHandlerJoystick_OnTouchMove Handler_OnTouchMove;

#pragma region >>> Function Delegate <<< 
public:
	template<typename ClassType>
	void BindOnTouchStart(ClassType* Object, typename FHandlerJoystick_OnTouchStart::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnTouchStart();
		Handler_OnTouchStart.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnTouchEnd(ClassType* Object, typename FHandlerJoystick_OnTouchEnd::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnTouchEnd();
		Handler_OnTouchEnd.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnTouchMove(ClassType* Object, typename FHandlerJoystick_OnTouchMove::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnTouchMove();
		Handler_OnTouchMove.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnTouchTick(ClassType* Object, typename FHandlerJoystick_OnTouchTick::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
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
