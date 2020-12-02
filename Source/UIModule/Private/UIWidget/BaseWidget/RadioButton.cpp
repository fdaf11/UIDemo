// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/RadioButton.h"
#include "Components/ButtonSlot.h"
#include "Components/Image.h"
#include "UObject/PropertyPortFlags.h"
//#include "MusicManager.h"
//#include "CommonMisc/THCommonFunctionLibrary.h"
//#include "Controller/THPlayerControllerBase.h"



TSharedRef<SWidget> URadioButton::RebuildWidget()
{
	//Super::RebuildWidget();  

	MyButton = SNew(SButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, RadioButtonSlateHandleClicked))
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


void URadioButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	SelectedStyle = WidgetStyle;
	SelectedStyle.Normal = SelectBrush;
	SelectedStyle.Hovered = SelectBrush;
	SelectedStyle.Pressed = SelectBrush;

	if (bSelected)
	{
		SelectStyle();
	}
	else
	{
		NormalStyle();
	}	

}

void URadioButton::SelectStyle()
{

	if (MyButton.IsValid())
	{
		MyButton->SetButtonStyle(&SelectedStyle);
	}
}

void URadioButton::NormalStyle()
{
	if (MyButton.IsValid())
	{
		MyButton->SetButtonStyle(&WidgetStyle);
	}
}

void URadioButton::SetSelected(bool bInSelected)
{
	bSelected = bInSelected;

	if (bSelected)
	{
		SelectStyle();
		//执行Selecte事件
		if (RadioButtonOnSelectedDelegate.IsBound())
		{
			RadioButtonOnSelectedDelegate.Execute(nID);
		}

		//其他按钮还原
		UPanelWidget* Parent = GetParent();
		if (Parent != nullptr)
		{
			int32 nCount = Parent->GetChildrenCount();
			for (int32 i = 0; i < nCount; ++i)
			{
				UWidget* child = Parent->GetChildAt(i);
				if (child != nullptr)
				{
					URadioButton* radiobutton = Cast<URadioButton>(child);
					if (radiobutton != nullptr)
					{
						if (child != this)
						{
							if(radiobutton->bSelected)
							{ 
								radiobutton->bSelected = false;
								radiobutton->NormalStyle();
							}
						}
					}
				}
			}

		}
	}
	else
	{
		NormalStyle();
	}
	
}

FReply URadioButton::RadioButtonSlateHandleClicked()
{
	OnClicked.Broadcast();
	//执行Click事件
	if (RadioButtonOnClickDelegate.IsBound())
	{
		RadioButtonOnClickDelegate.Execute(nID);
	}
	//UWorld* tWorld = GetWorld();
	//if (tWorld)
	//{
	//	ATHPlayerControllerBase* tPC = Cast<ATHPlayerControllerBase>(tWorld->GetFirstPlayerController());
	//	if (!tPC)
	//		return FReply::Handled();

	//	/*if (bUseCommonMusic)
	//		UTHCommonFunctionLibrary::PlaySound2D(tPC->LocalMusicManager, EMusicType::CommonUIButtonClick_Frontend);
	//	else
	//		UTHCommonFunctionLibrary::PlaySound2D(tPC->LocalMusicManager, EMusicType::SoundEffect_Divider, ClickedSound);*/
	//}
	SetSelected(true);
	return FReply::Handled();
}