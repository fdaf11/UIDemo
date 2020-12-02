// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/NormalobjButton.h"
#include "Components/ButtonSlot.h"

TSharedRef<SWidget> UNormalobjButton::RebuildWidget()
{
	//Super::RebuildWidget();  

	MyButton = SNew(SButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, NormalobjButtonSlateHandleClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
		.OnHovered_UObject(this, &ThisClass::SlateHandleHovered)
		.OnUnhovered_UObject(this, &ThisClass::SlateHandleUnhovered)
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.IsFocusable(IsFocusable)
		;

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}

	return MyButton.ToSharedRef();
}

FReply UNormalobjButton::NormalobjButtonSlateHandleClicked()
{
	OnClicked.Broadcast();

	if (NormalButtonOnClickDelegate.IsBound())
	{
		NormalButtonOnClickDelegate.Execute(this);
	}

	return FReply::Handled();
}

