// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/THInteractiveWidgetBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
//#include "UI/Common/THImage.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Button.h"

void UTHInteractiveWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (!bText && Text_Item)
		Text_Item->RemoveFromParent();

	if (Btn && !bButton)
		Btn->RemoveFromParent();

	//// 1. NativeConstuct将在初始的RegisterUIComponent(即PostInitialiszeComp)之后调用;
	//// 2. Wrap.AddChild会重复调用NativeConstruct
	//if (bButton && Btn)
	//{
	//	Btn->OnClicked.AddUniqueDynamic(this, &UTHInteractiveWidgetBase::ExecuteOnClicked);
	//	Btn->OnPressed.AddUniqueDynamic(this, &UTHInteractiveWidgetBase::ExecuteOnPressed);
	//	Btn->OnReleased.AddUniqueDynamic(this, &UTHInteractiveWidgetBase::ExecuteOnReleased);
	//	Btn->OnHovered.AddUniqueDynamic(this, &UTHInteractiveWidgetBase::ExecuteOnHovered);
	//	Btn->OnUnhovered.AddUniqueDynamic(this, &UTHInteractiveWidgetBase::ExecuteOnUnhovered);
	//}
}

void UTHInteractiveWidgetBase::UpdateRadioSelected(bool InbSelections)
{
	if (bOpenRadioSelections)
		Super::UpdateRadioSelected(InbSelections);
}

