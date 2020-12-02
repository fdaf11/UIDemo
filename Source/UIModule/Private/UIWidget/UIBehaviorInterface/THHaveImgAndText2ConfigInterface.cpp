#include "UIWidget/UIBehaviorInterface/THHaveImgAndText2ConfigInterface.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void ITHHaveImgAndText2ConfigInterface::SetWidgetText(FString InData)
{
	UTextBlock* tText_Content = GetWidgetText();
	if (!tText_Content)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetText, tText_Content == nullptr"));
		return;
	}

	tText_Content->SetText(FText::FromString(InData));
}

void ITHHaveImgAndText2ConfigInterface::SetWidgetTextColorAndOpacity(const FSlateColor& InColor)
{
	UTextBlock* tText_Content = GetWidgetText();
	if (!tText_Content)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetTextColorAndOpacity, tText_Content == nullptr"));
		return;
	}

	tText_Content->SetColorAndOpacity(InColor);
}

void ITHHaveImgAndText2ConfigInterface::SetWidgetTextFont(const FSlateFontInfo& InFont)
{
	UTextBlock* tText_Content = GetWidgetText();
	if (!tText_Content)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetTextFont, tText_Content == nullptr"));
		return;
	}

	tText_Content->SetFont(InFont);
}

void ITHHaveImgAndText2ConfigInterface::SetWidgetTextSize(const int32& InSize)
{
	UTextBlock* tText_Content = GetWidgetText();
	if (!tText_Content)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetTextSize, tText_Content == nullptr"));
		return;
	}

	tText_Content->Font.Size = InSize > 0 ? InSize : 24.f;
	tText_Content->SetFont(tText_Content->Font);
}

void ITHHaveImgAndText2ConfigInterface::SetWidgetTextVisiblity(const ESlateVisibility& IneVisible)
{
	UTextBlock* tText_Content = GetWidgetText();
	if (!tText_Content)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetTextVisiblity, tText_Content == nullptr"));
		return;
	}

	tText_Content->SetVisibility(IneVisible);
}

void ITHHaveImgAndText2ConfigInterface::SetWidgetImgBrushFromTexture(class UTexture2D* Intex2_Icon, bool InbMatchSize /*= false*/)
{
	UImage* tIMG_Item = GetWidgetImage();
	if (!tIMG_Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetImgBrushFromTexture, tIMG_Item == nullptr"));
		return;
	}

	tIMG_Item->SetBrushFromTexture(Intex2_Icon, InbMatchSize);
}

void ITHHaveImgAndText2ConfigInterface::SetWidgetImgBrush(const FSlateBrush& InBrush)
{
	UImage* tIMG_Item = GetWidgetImage();
	if (!tIMG_Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetImgBrush, tIMG_Item == nullptr"));
		return;
	}

	tIMG_Item->SetBrush(InBrush);
}

void ITHHaveImgAndText2ConfigInterface::SetWidgetImgBrushTintColor(const FSlateColor& TintColor)
{
	UImage* tIMG_Item = GetWidgetImage();
	if (!tIMG_Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetImgBrushTintColor, tIMG_Item == nullptr"));
		return;
	}

	tIMG_Item->SetBrushTintColor(TintColor);
}

void ITHHaveImgAndText2ConfigInterface::SetWidgetImgVisiblity(const ESlateVisibility& IneVisible)
{
	UImage* tIMG_Item = GetWidgetImage();
	if (!tIMG_Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHHaveImgAndText2ConfigInterface::SetWidgetImgVisiblity, tIMG_Item == nullptr"));
		return;
	}

	tIMG_Item->SetVisibility(IneVisible);
}
