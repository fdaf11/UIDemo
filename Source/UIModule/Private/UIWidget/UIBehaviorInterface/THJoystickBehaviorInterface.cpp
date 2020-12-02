#include "UIWidget/UIBehaviorInterface/THJoystickBehaviorInterface.h"

void ITHJoystickBehaviorInterface::ExecuteOnTouchStart(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale)
{
	Handler_OnTouchStart.ExecuteIfBound(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, ControlInfo, ThumbInfo, fDpiScale);
}

void ITHJoystickBehaviorInterface::ExecuteOnTouchEnd(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale)
{
	Handler_OnTouchEnd.ExecuteIfBound(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, ControlInfo, ThumbInfo, fDpiScale);
}

void ITHJoystickBehaviorInterface::ExecuteOnTouchMove(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale)
{
	Handler_OnTouchMove.ExecuteIfBound(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, ControlInfo, ThumbInfo, fDpiScale);
}

void ITHJoystickBehaviorInterface::ExecuteOnTouchTick(float xAxis, float yAxis, bool InbIsTouchEndedTick)
{
	Handler_OnTouchTick.ExecuteIfBound(xAxis, yAxis, InbIsTouchEndedTick);
}
