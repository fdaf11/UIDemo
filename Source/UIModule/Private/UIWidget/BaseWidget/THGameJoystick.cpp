// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/THGameJoystick.h"
#include "UIWidget/Joystick/THJoystick.h"
#include "Components/Image.h"
#include "CommonMisc/THFunctionLibrary_UI.h"


void UTHGameJoystick::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Joystick)
	{
		Joystick->OnJoystickTumbMoveTickDelegate.AddDynamic(this, &UTHGameJoystick::ExecuteOnTouchTick);
		Joystick->OnJoystickTouchStartDelegate.AddDynamic(this, &UTHGameJoystick::OnJoystickTouch);		// 统一调用同一函数，当中根据参数参数，调用不同的Execute
		Joystick->OnJoystickTouchMoveDelegate.AddDynamic(this, &UTHGameJoystick::OnJoystickTouch);
		Joystick->OnJoystickTouchEndDelegate.AddDynamic(this, &UTHGameJoystick::OnJoystickTouch);
		Joystick->OnJoystickInitPropertyUpdate.AddDynamic(this, &UTHGameJoystick::OnJoystickInitPropertyUpdate);
		Joystick->Init(GlobalParameter);
	}
}

#if WITH_EDITOR
void UTHGameJoystick::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	InitConfigStyle_GameJoystick();
}
#endif

void UTHGameJoystick::InitConfigStyle_GameJoystick()
{
	UpdatebShowJoystickBG(bShowJoystickBG);
	UpdatebShowJoystickThumb(bShowJoystickThumb);

	if (Joystick && Joystick->SJoystick)
	{
		Joystick->ControlInfo = ControlInfo;

		// 复制STHJoystick当中的Control信息，并更新显示
		TArray<FJoystickControlInfo> tArr_JoystickControlConfigs;
		FJoystickControlInfo tJoystickControlInfo;
		tJoystickControlInfo.Center = ControlInfo.Center;
		tJoystickControlInfo.InputScale = ControlInfo.InputScale;
		tJoystickControlInfo.InteractionSize = ControlInfo.InteractionSize;
		tJoystickControlInfo.ThumbSize = ControlInfo.ThumbSize;
		tJoystickControlInfo.VisualSize = ControlInfo.VisualSize;
		tArr_JoystickControlConfigs.Emplace(tJoystickControlInfo);
		Joystick->SJoystick->SetControls(tArr_JoystickControlConfigs);	// 【】TODO 直接修改STHJoystick，不走THJOystick，后续会逐步删除THJOystick配置方面的内容，更多的去开发接口

		// 图片更新
		Joystick->JoystickThumb = JoystickThumb;
		Joystick->JoystickBGI = JoystickBGI;
		RefreshUI_JoystickRepositionOrResize();
	}
}

void UTHGameJoystick::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

#if WITH_EDITOR
	InitConfigStyle_GameJoystick();
#endif
}


void UTHGameJoystick::Init()
{
	UpdateSTHJoystickInfos();
}

void UTHGameJoystick::UpdateControlInfo(FControlConfig InControlInfo)
{
	if (!Joystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHGameJoystick::UpdateControlInfo, Joystick == nullptr"));
		return;
	}

	ControlInfo = InControlInfo;
	InitConfigStyle_GameJoystick();
}

void UTHGameJoystick::UpdateImg_JoystickThumb(FSlateBrush InJoystickThumb)
{
	if (!Joystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHGameJoystick::UpdateImg_JoystickThumb, Joystick == nullptr"));
		return;
	}

	JoystickThumb = InJoystickThumb;
	InitConfigStyle_GameJoystick();
}

void UTHGameJoystick::UpdateImg_JoystickBGI(FSlateBrush InJoystickBGI)
{
	if (!Joystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHGameJoystick::UpdateImg_JoystickBGI, Joystick == nullptr"));
		return;
	}

	JoystickBGI = InJoystickBGI;
	InitConfigStyle_GameJoystick();
}

void UTHGameJoystick::UpdateSTHJoystickInfos()
{
	if (Joystick)
		Joystick->GetJoystickControlsAndThumbOrientation(JoystickControls, ThumbInfo);
}

void UTHGameJoystick::ClearPlayerOperate()
{
	if (!Joystick || !Joystick->SJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHGameJoystick::ClearPlayerOperate, Joystick || Joystick->SJoystick == nullptr"));
		return;
	}

	Joystick->SJoystick->ClearAllPlayerOperate();

	UpdateSTHJoystickInfos();
}

void UTHGameJoystick::SetGlobalParameter(const FJoystick_GlobalParameters InGlobalParameter)
{
	GlobalParameter = InGlobalParameter;
	if (Joystick)
		Joystick->SetGlobalParameter(GlobalParameter);
}

float UTHGameJoystick::UpdateDPIScaleFactor()
{
	fScaleFactor = UTHFunctionLibrary_UI::GetDPIScaleFactor(this->GetCachedGeometry());
	return fScaleFactor;
}


void UTHGameJoystick::UpdatebShowJoystickThumb(bool InbShow)
{
	bShowJoystickThumb = InbShow;

	if (Joystick && Joystick->SJoystick)
		Joystick->SJoystick->ShowTumbImg(InbShow);
}

void UTHGameJoystick::UpdatebShowJoystickBG(bool InbShow)
{
	bShowJoystickBG = InbShow;

	if (Joystick && Joystick->SJoystick)
		Joystick->SJoystick->ShowVisualBGI(InbShow);
}

void UTHGameJoystick::UpdatebPressedShowJoystickImg(bool InbNewState)
{
	bPressedShowJoystickImg = InbNewState;
}

int32 UTHGameJoystick::ResolveRelativePosition(float Position, float RelativeTo, float ScaleFactor)
{
	// absolute from edge
	if (Position < -1.0f)
		return RelativeTo + Position * ScaleFactor;

	// relative from edge
	else if (Position < 0.0f)
		return RelativeTo + Position * RelativeTo;

	// relative from 0
	else if (Position <= 1.0f)
		return Position * RelativeTo;

	// absolute from 0
	else
		return Position * ScaleFactor;
}

void UTHGameJoystick::RefreshUI_JoystickRepositionOrResize()
{
	if (!Joystick || !Joystick->SJoystick)
		return;

	Joystick->SJoystick->RefreshUI_RepositionOrResize();
}

void UTHGameJoystick::RecoverFocusToJoystick()
{
	if (!Joystick || !Joystick->SJoystick)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHGameJoystick::RecoverFocusToJoystick, !Joystick || !Joystick->SJoystic"));
		return;
	}

	Joystick->SJoystick->RecoverFocusToJoystick();
}


FVector2D UTHGameJoystick::GetSelfCentreLocalPos()
{
	const FGeometry& tGeometry = GetCachedGeometry();
	return tGeometry.Position + tGeometry.Size / 2.f;
}

void UTHGameJoystick::OnJoystickTouch(EJoystickHandleTouchType HandleTouchType, int32 ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize)
{
	if (!Joystick)
		return;

	UpdateSTHJoystickInfos();
	UpdateDPIScaleFactor();
	fThumb2CentreDistSqr = ThumbInfo.ThumbOffset.SizeSquared();

	// Player
	if (ControlIndex == 0)
	{
		const FJoystickControlInfo& tControlInfo = JoystickControls[ControlIndex];
		if (EJoystickHandleTouchType::Touch_Start == HandleTouchType)
		{
			if (bPressedShowJoystickImg)
			{
				UpdatebShowJoystickBG(true);
				UpdatebShowJoystickThumb(true);
			}

			ExecuteOnTouchStart(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, tControlInfo, ThumbInfo, fScaleFactor);
		}
		else if (EJoystickHandleTouchType::Touch_End == HandleTouchType)
		{
			if (bPressedShowJoystickImg)
			{
				UpdatebShowJoystickBG(false);
				UpdatebShowJoystickThumb(false);
			}

			ExecuteOnTouchEnd(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, tControlInfo, ThumbInfo, fScaleFactor);
		}
		else
			ExecuteOnTouchMove(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, tControlInfo, ThumbInfo, fScaleFactor);

		CallBPOnJoystickTouch(HandleTouchType, ControlIndex, LocalCoord, ScreenSize, tControlInfo, ThumbInfo, fScaleFactor);
	}
}

void UTHGameJoystick::ExecuteOnTouchTick(float xAxis, float yAxis, bool InbIsTouchEndedTick)
{
	UpdateSTHJoystickInfos();

	ITHJoystickBehaviorInterface::ExecuteOnTouchTick(xAxis, yAxis, InbIsTouchEndedTick);
	
	CallBPOnTouchTick(xAxis, yAxis, InbIsTouchEndedTick);
}

void UTHGameJoystick::OnJoystickInitPropertyUpdate()
{
	UpdateSTHJoystickInfos();

	CallBPJoystickInitPropertyUpdate();	// 【】TODO 暂时无用，后续可删
}

