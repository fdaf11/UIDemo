#include "UIWidget/UIBehaviorInterface/THHaveButton2ConfigInterface.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"

void ITHHaveButton2ConfigInterface::SetWidgetButtonStyleFromTexture(class UTexture2D* InTex_Item)
{
	if (!InTex_Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveButton2ConfigInterface::SetWidgetButtonStyleFromTexture, InTex_Item == nullptr"));
		return;
	}

	FButtonStyle tButtonStyle;
	FSlateBrush tBrush;
	tBrush.SetResourceObject(InTex_Item);
	tButtonStyle.Normal = tBrush;
	tButtonStyle.Pressed = tBrush;
	tButtonStyle.Hovered = tBrush;
	SetWidgetButtonStyle(tButtonStyle);
}

void ITHHaveButton2ConfigInterface::SetWidgetButtonStyle(const FButtonStyle& InBtnStyle)
{
	UButton* tBtn = GetWidgetBtn();
	if (!tBtn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveButton2ConfigInterface::SetWidgetButtonStyle, tBtn == nullptr"));
		return;
	}

	tBtn->SetStyle(InBtnStyle);
}

void ITHHaveButton2ConfigInterface::SetWidgetButtonVisibility(const ESlateVisibility& IneVisibility)
{
	UButton* tBtn = GetWidgetBtn();
	if (!tBtn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveButton2ConfigInterface::SetWidgetButtonVisibility, tBtn == nullptr"));
		return;
	}

	tBtn->SetVisibility(IneVisibility);
}

void ITHHaveButton2ConfigInterface::SetWidgetButtonBackgroundColor(const FLinearColor& InColor)
{
	UButton* tBtn = GetWidgetBtn();
	if (!tBtn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveButton2ConfigInterface::SetWidgetButtonTintColor, tBtn == nullptr"));
		return;
	}

	tBtn->SetBackgroundColor(InColor);
}
