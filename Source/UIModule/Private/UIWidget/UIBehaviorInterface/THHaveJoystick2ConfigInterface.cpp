#include "UIWidget/UIBehaviorInterface/THHaveJoystick2ConfigInterface.h"
#include "UIWidget/BaseWidget/THGameJoystick.h"

void ITHHaveJoystick2ConfigInterface::Init()
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::Init, tJoystick == nullptr"));
		return;
	}

	tJoystick->Init();
}

bool ITHHaveJoystick2ConfigInterface::GetJoystickControls(TArray<FJoystickControlInfo>& JoystickControlInfo)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::GetJoystickControls, tJoystick == nullptr"));
		return false;
	}

	JoystickControlInfo = tJoystick->GetJoystickControls();
	return true;
}

//bool ITHHaveJoystick2ConfigInterface::GetJoystickTickInfo(FJoystickTickInfo& JoystickTickInfo)
//{
//	UTHGameJoystick* tJoystick = GetJoystick();
//	if (!tJoystick)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::GetJoystickTickInfo, tJoystick == nullptr"));
//		return false;
//	}
//
//	JoystickTickInfo = tJoystick->GetJoystickTickInfo();
//	return true;
//}

const float ITHHaveJoystick2ConfigInterface::GetfJoystickScaleFactor()
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::GetfJoystickScaleFactor, tJoystick == nullptr"));
		return 1.f;
	}

	return tJoystick->GetfScaleFactor();
}

bool ITHHaveJoystick2ConfigInterface::GetJoystickThumbInfo(FThumbOrientationInfo& ThumbOrientationInfo)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::GetfJoystickThumbInfo, tJoystick == nullptr"));
		return false;
	}

	ThumbOrientationInfo = tJoystick->GetfThumbInfo();
	return true;
}

void ITHHaveJoystick2ConfigInterface::UpdateControlInfo(FControlConfig InControlInfo)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::UpdateControlInfo, tJoystick == nullptr"));
		return;
	}

	tJoystick->UpdateControlInfo(InControlInfo);
}

void ITHHaveJoystick2ConfigInterface::UpdateImg_JoystickThumb(FSlateBrush InJoystickThumb)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::UpdateImg_JoystickThumb, tJoystick == nullptr"));
		return;
	}

	tJoystick->UpdateImg_JoystickThumb(InJoystickThumb);
}

void ITHHaveJoystick2ConfigInterface::UpdateImg_JoystickBGI(FSlateBrush InJoystickBGI)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::UpdateImg_JoystickBGI, tJoystick == nullptr"));
		return;
	}

	tJoystick->UpdateImg_JoystickBGI(InJoystickBGI);
}

void ITHHaveJoystick2ConfigInterface::UpdatebPressedShowJoystickImg(bool InbNewState)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::UpdatebPressedShowJoystickImg, tJoystick == nullptr"));
		return;
	}

	tJoystick->UpdatebPressedShowJoystickImg(InbNewState);
}

void ITHHaveJoystick2ConfigInterface::ClearAllPlayerOperate()
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::ClearAllPlayerOperate, tJoystick == nullptr"));
		return;
	}

	tJoystick->ClearPlayerOperate();
}

bool ITHHaveJoystick2ConfigInterface::LimitJoystickPosOnNoPreventCenter(FVector2D InVec2_RecLeftUp, FVector2D InVec2_RecRightBottom, FVector2D& InVec2_ResultLoc)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::ClearAllPlayerOperate, tJoystick == nullptr"));
		return false;
	}

	const FJoystick_GlobalParameters& tGlobalParameters = tJoystick->GetGlobalParameters();
	if (tGlobalParameters.PreventRecenter)
		return false;

	InVec2_ResultLoc.X = FMath::Clamp(InVec2_ResultLoc.X, InVec2_RecLeftUp.X, InVec2_RecRightBottom.X);
	InVec2_ResultLoc.Y = FMath::Clamp(InVec2_ResultLoc.Y, InVec2_RecLeftUp.Y, InVec2_RecRightBottom.Y);
	return true;
}


#pragma region Refresh_UI

void ITHHaveJoystick2ConfigInterface::ShowJoystickTumbImg(bool InbShow)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::ShowJoystickTumbImg, tJoystick == nullptr"));
		return;
	}

	tJoystick->UpdatebShowJoystickThumb(InbShow);
}


void ITHHaveJoystick2ConfigInterface::ShowJoystickVisualBGI(bool InbShow)
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::GetJoystickControls, tJoystick == nullptr"));
		return;
	}

	tJoystick->UpdatebShowJoystickBG(InbShow);
}

void ITHHaveJoystick2ConfigInterface::RefreshUI_JoystickRepositionOrResize()
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::RefreshUI_JoystickRepositionOrResize, tJoystick == nullptr"));
		return;
	}

	tJoystick->RefreshUI_JoystickRepositionOrResize();
}

#pragma endregion Refresh_UI


void ITHHaveJoystick2ConfigInterface::RecoverFocusToJoystick()
{
	UTHGameJoystick* tJoystick = GetJoystick();
	if (!tJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveJoystick2ConfigInterface::RecoverFocusToJoystick, tJoystick == nullptr"));
		return;
	}

	tJoystick->RecoverFocusToJoystick();
}

#pragma region FunctionDelegate
void ITHHaveJoystick2ConfigInterface::ExecuteOnTouchStart(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale)
{
	Handler_OnTouchStart.ExecuteIfBound(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, ControlInfo, ThumbInfo, fDpiScale);
}

void ITHHaveJoystick2ConfigInterface::ExecuteOnTouchEnd(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale)
{
	Handler_OnTouchEnd.ExecuteIfBound(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, ControlInfo, ThumbInfo, fDpiScale);
}

void ITHHaveJoystick2ConfigInterface::ExecuteOnTouchMove(const EJoystickHandleTouchType& HandleTouchType, const int32& ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize, const FJoystickControlInfo& ControlInfo, const FThumbOrientationInfo& ThumbInfo, const float& fDpiScale)
{
	Handler_OnTouchMove.ExecuteIfBound(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, ControlInfo, ThumbInfo, fDpiScale);
}

void ITHHaveJoystick2ConfigInterface::ExecuteOnTouchTick(float xAxis, float yAxis, bool InbIsTouchEndedTick)
{
	Handler_OnTouchTick.ExecuteIfBound(xAxis, yAxis, InbIsTouchEndedTick);
}


#pragma endregion FunctionDelegate

