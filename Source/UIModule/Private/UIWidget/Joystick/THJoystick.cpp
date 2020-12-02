// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/Joystick/THJoystick.h"
#include "UMG.h"
#include "UMGStyle.h"
//#include "Characters/THPlayerCharacter.h"
//#include "Controllers/THPlayerController.h"
//#include "Vehicles/THVehicle4WBase.h"
#include "ObjectEditorUtils.h"

UTHJoystick::UTHJoystick()
{
	bIsVariable = true;
}

void UTHJoystick::Init(FJoystick_GlobalParameters InGlobalParameter)
{
	SetGlobalParameter(InGlobalParameter);
	SynchronizeProperties();
}

#if WITH_EDITOR
const FText UTHJoystick::GetPaletteCategory()
{
	return NSLOCTEXT("WLWidget", "WLCustom", "WLCustom");
}
#endif

void UTHJoystick::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TAttribute<const FSlateBrush*> JoystickThumbBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, JoystickThumb, const FSlateBrush*, ConvertJoystickThumb);
	TAttribute<const FSlateBrush*> JoystickBGIBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, JoystickBGI, const FSlateBrush*, ConvertJoystickBGI);
	TAttribute<const FSlateBrush*> FastRunArrowBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, FastRunArrow, const FSlateBrush*, ConvertFastRunArrow);
	TAttribute<const FSlateBrush*> FastRunBtnBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, FastRunBtn, const FSlateBrush*, ConvertFastRunBtn);
	TAttribute<const FSlateBrush*> FastRunActiveBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, FastRunActive, const FSlateBrush*, ConvertFastRunActive);
	TAttribute<const FSlateBrush*> AutoRunThumbBinding = OPTIONAL_BINDING_CONVERT(FSlateBrush, AutoRunThumb, const FSlateBrush*, ConvertAutoRunThumb);
	TAttribute<const FControlConfig*> ControlInfoBinding = OPTIONAL_BINDING_CONVERT(FControlConfig, ControlInfo, const FControlConfig*, ConvertControlInfo);

	if (SJoystick.IsValid())
	{
		// Brush
		SJoystick->SetJoystickThumbImage(JoystickThumbBinding);
		SJoystick->SetJoystickBGI(JoystickBGIBinding);
		SJoystick->SetFastRunArrowImage(FastRunArrowBinding);
		SJoystick->SetFastRunButtonImage(FastRunBtnBinding);
		SJoystick->SetFastRunActiveImage(FastRunActiveBinding);
		SJoystick->SetAutoRunThumbImage(AutoRunThumbBinding);
		SJoystick->SetFastRunButtonImageOffsetY(OffsetY);

		// Control Info
		FJoystickControlInfo Info;
		const FControlConfig* pConfig = ControlInfoBinding.Get();
		if (pConfig)
		{
			Info.Center = pConfig->Center;
			Info.VisualSize = pConfig->VisualSize;
			Info.ThumbSize = pConfig->ThumbSize;
			Info.InteractionSize = pConfig->InteractionSize;
			Info.InputScale = pConfig->InputScale;
		}
		SJoystick->ClearControls();
		SJoystick->AddControl(Info);

		// GlobalParameters
		/*float ActiveOpacity = 1.f;
		float InactiveOpacity = 0.2f;
		float TimeUntilDeactive = 0.5f;
		float TimeUntilReset = 2.0f;
		float ActivationDelay = 0;
		bool PreventRecenter = true;
		float StartupDelay = 0;*/

		SJoystick->SetGlobalParameters(GlobalParameter.ActiveOpacity, GlobalParameter.InactiveOpacity, GlobalParameter.TimeUntilDeactive, GlobalParameter.TimeUntilReset, GlobalParameter.ActivationDelay, GlobalParameter.PreventRecenter, GlobalParameter.StartupDelay);
	}
}

void UTHJoystick::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	SJoystick.Reset();
}

TSharedRef<SWidget> UTHJoystick::RebuildWidget()
{
	SJoystick = SNew(STHJoystick);
	if (SJoystick.IsValid())
	{
		SJoystick->UMG = this;
	}

	return SJoystick.ToSharedRef();
}

void UTHJoystick::SetAllowFastRun(bool flag)
{
	if (SJoystick.IsValid())
	{
		SJoystick->SetAllowFastRun(flag);
	}
}

//ATHPlayerCharacter* UTHJoystick::GetTHPlayerPawn()
//{
//	if (!LocalPawn)
//	{
//		if (ATHPlayerController* THPC = GetTHPC())
//		{
//			if (APawn* CtrlPawn = THPC->GetPawn())
//			{
//				if (CtrlPawn->IsA(ATHPlayerCharacter::StaticClass()))
//				{
//					LocalPawn = Cast<ATHPlayerCharacter>(CtrlPawn);
//				}
//				else if (CtrlPawn->IsA(ATHVehicle4WBase::StaticClass()))
//				{
//					ATHVehicle4WBase* Vehicle = Cast<ATHVehicle4WBase>(CtrlPawn);
//					if (Vehicle && Vehicle->Driver && Vehicle->Driver->IsA(ATHPlayerCharacter::StaticClass()))
//					{
//						LocalPawn = Cast<ATHPlayerCharacter>(Vehicle->Driver);
//					}
//				}
//			}
//		}
//	}
//	return LocalPawn;
//}
//
//ATHPlayerController* UTHJoystick::GetTHPC()
//{
//	if (!LocalPC)
//	{
//		if (GetWorld())
//		{
//			LocalPC = Cast<ATHPlayerController>(GetWorld()->GetFirstPlayerController());
//		}
//	}
//	return LocalPC;
//}

#pragma region Delegate

void UTHJoystick::HandleJoystickTouch(EJoystickHandleTouchType HandleTouchType, int32 ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize)
{
	switch (HandleTouchType)
	{
	case EJoystickHandleTouchType::Touch_Start:
		if (OnJoystickTouchStartDelegate.IsBound())
			OnJoystickTouchStartDelegate.Broadcast(HandleTouchType, ControlIndex, LocalCoord, ScreenSize);
		return;
	case EJoystickHandleTouchType::Touch_Move:
		if (OnJoystickTouchMoveDelegate.IsBound())
			OnJoystickTouchMoveDelegate.Broadcast(HandleTouchType, ControlIndex, LocalCoord, ScreenSize);
		return;
	case EJoystickHandleTouchType::Touch_End:
		if (OnJoystickTouchEndDelegate.IsBound())
			OnJoystickTouchEndDelegate.Broadcast(HandleTouchType, ControlIndex, LocalCoord, ScreenSize);
		return;
	case EJoystickHandleTouchType::Touch_Tick:	// OnJoystickTumbMoveTickDelegate已封装回调以及传入的属性；
		return;
	default:
		break;
	}
}

void UTHJoystick::ThumbOffsetTickDelegate(const float xAxis, const float yAxis, const bool InbIsTouchEndedTick)
{
	if (OnJoystickTumbMoveTickDelegate.IsBound())
		OnJoystickTumbMoveTickDelegate.Broadcast(xAxis, yAxis, InbIsTouchEndedTick);
}

void UTHJoystick::OnJoystickInitPropertyUpdateDelegate()
{
	if (OnJoystickInitPropertyUpdate.IsBound())
		OnJoystickInitPropertyUpdate.Broadcast();
}

bool UTHJoystick::GetJoystickControlsAndThumbOrientation(TArray<FJoystickControlInfo>& InJoystickControls, FThumbOrientationInfo& InThumbInfo)
{
	if (SJoystick.IsValid())
	{
		InJoystickControls = SJoystick->Controls;
		InThumbInfo = SJoystick->ThumbOrienInfo;
		//InJoystickTickInfo = SJoystick->JoystickTickInfo;
		return true;
	}

	return false;
}

void UTHJoystick::SetGlobalParameter(const FJoystick_GlobalParameters InGlobalParameter)
{
	GlobalParameter = InGlobalParameter;
	SynchronizeProperties();
}

#pragma endregion Delegate


// ConvertFunction --------------------------------------------------------------------------------------------
const FControlConfig* UTHJoystick::ConvertControlInfo(TAttribute<FControlConfig> InControlConfig) const
{
	UTHJoystick* MutableThis = const_cast<UTHJoystick*>(this);
	MutableThis->ControlInfo = InControlConfig.Get();

	return &ControlInfo;
}
const FSlateBrush* UTHJoystick::ConvertJoystickThumb(TAttribute<FSlateBrush> InImageAsset) const
{
	UTHJoystick* MutableThis = const_cast<UTHJoystick*>(this);
	MutableThis->JoystickThumb = InImageAsset.Get();

	return &JoystickThumb;
}
const FSlateBrush* UTHJoystick::ConvertJoystickBGI(TAttribute<FSlateBrush> InImageAsset) const
{
	UTHJoystick* MutableThis = const_cast<UTHJoystick*>(this);
	MutableThis->JoystickBGI = InImageAsset.Get();

	return &JoystickBGI;
}
const FSlateBrush* UTHJoystick::ConvertFastRunArrow(TAttribute<FSlateBrush> InImageAsset) const
{
	UTHJoystick* MutableThis = const_cast<UTHJoystick*>(this);
	MutableThis->FastRunArrow = InImageAsset.Get();

	return &FastRunArrow;
}
const FSlateBrush* UTHJoystick::ConvertFastRunBtn(TAttribute<FSlateBrush> InImageAsset) const
{
	UTHJoystick* MutableThis = const_cast<UTHJoystick*>(this);
	MutableThis->FastRunBtn = InImageAsset.Get();

	return &FastRunBtn;
}
const FSlateBrush* UTHJoystick::ConvertFastRunActive(TAttribute<FSlateBrush> InImageAsset) const
{
	UTHJoystick* MutableThis = const_cast<UTHJoystick*>(this);
	MutableThis->FastRunActive = InImageAsset.Get();

	return &FastRunActive;
}
const FSlateBrush* UTHJoystick::ConvertAutoRunThumb(TAttribute<FSlateBrush> InImageAsset) const
{
	UTHJoystick* MutableThis = const_cast<UTHJoystick*>(this);
	MutableThis->AutoRunThumb = InImageAsset.Get();

	return &AutoRunThumb;
}