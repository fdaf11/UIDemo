// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/NormalButton.h"
#include "Components/ButtonSlot.h"
#include "Sound/SlateSound.h"
//#include "CommonMisc/THCommonFunctionLibrary.h"
//#include "THMusicPlugin/Public/THMusicPluginLibrary.h"


#define LOCTEXT_NAMESPACE "UMG"

TSharedRef<SWidget> UNormalButton::RebuildWidget()
{
	//Super::RebuildWidget();  
	MyButton = SNew(SButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, ExecuteOnClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, ExecuteOnPressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, ExecuteOnReleased))
		.OnHovered_UObject(this, &ThisClass::ExecuteOnHovered)
		.OnUnhovered_UObject(this, &ThisClass::ExecuteOnUnhovered)
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.PressMethod(PressMethod)
		.IsFocusable(IsFocusable)
		;

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}

	return MyButton.ToSharedRef();
}

FReply UNormalButton::ExecuteOnClicked()
{
	OnClicked.Broadcast();

	if (Handler_OnClicked.IsBound())
	{
		Handler_OnClicked.Execute(nID);
	}

	//if (bUseCommonMusic)
	//	UTHFrontendFunctionLibrary::PlaySound2D(this, EMusicType::CommonUIButtonClick_Frontend);		// 拿不到FrontendFuc
	//else
	//	UTHFrontendFunctionLibrary::PlaySound2D(this, EMusicType::None, nullptr, ClickedWwiseEventName);

	return FReply::Handled();
}

void UNormalButton::ExecuteOnPressed()
{
	OnPressed.Broadcast();
	if (Handler_OnPressed.IsBound())
	{
		Handler_OnPressed.Execute(nID);
	}
}
void UNormalButton::ExecuteOnReleased()
{
	OnReleased.Broadcast();

	if (Handler_OnReleased.IsBound())
	{
		Handler_OnReleased.Execute(nID);
	}
}
void UNormalButton::ExecuteOnHovered()
{
	OnHovered.Broadcast();

	if (Handler_OnHovered.IsBound())
	{
		Handler_OnHovered.Execute(nID);
	}
}
void UNormalButton::ExecuteOnUnhovered()
{
	OnUnhovered.Broadcast();

	if (Handler_OnUnhovered.IsBound())
	{
		Handler_OnUnhovered.Execute(nID);
	}
}
#undef LOCTEXT_NAMESPACE