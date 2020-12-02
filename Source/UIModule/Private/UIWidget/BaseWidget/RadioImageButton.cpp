// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/RadioImageButton.h"
#include "Components/ButtonSlot.h"
#include "Components/Image.h"




void URadioImageButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	//MyImage = NewObject<UImage>(this, UImage::StaticClass(), NAME_None, RF_Transactional);
	MyImage = NewObject<UImage>();
	if (MyImage != nullptr)
	{
		MyImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		//MyImage->SetBrush(MainBrush);
		if (MainTexture != nullptr)
		{
			MyImage->SetBrushFromTexture(MainTexture, true);
		}
		AddChild(MyImage);
	}

}

void URadioImageButton::SetMainTexture(UTexture2D* Image)
{
	if (Image != nullptr )
	{
		if (MyImage)
		{
			MyImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			MainTexture = Image;
			MyImage->SetBrushFromTexture(MainTexture, true);
		}

	}
}