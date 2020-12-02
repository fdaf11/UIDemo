#include "UIWidget/BaseWidget/THRadioBtn_ImgText.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTHRadioBtn_ImgText::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	
	InitConfigStyle_ImgAndText();
}

void UTHRadioBtn_ImgText::InitConfigStyle_ImgAndText()
{
	SetWidgetImgBrush(ImgBrush);
	SetWidgetText(TextString);
	SetWidgetTextFont(TextFont);
	SetWidgetTextVisiblity(Visibility_Text);			// OnWidgetRebuilt当中设置Visibility会导致"眼睛"图标不可使用; PostEditChg当中设置Visibility会被OnWidgetRebuilt还原, By ZZQ
	SetWidgetImgVisiblity(Visibility_Image);
}

void UTHRadioBtn_ImgText::SelectedStyleShow()
{
	Super::SelectedStyleShow();
	
	SelectedStyleShow_Text();
	SelectedStyleShow_Image();
}

void UTHRadioBtn_ImgText::NoselectedStyleShow()
{
	Super::NoselectedStyleShow();

	NoselectedStyleShow_Text();
	NoselectedStyleShow_Image();
}

#if WITH_EDITOR
void UTHRadioBtn_ImgText::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	InitConfigStyle_ImgAndText();
}
#endif

#pragma region RadioSelected
void UTHRadioBtn_ImgText::SelectedStyleShow_Text()
{
	SetWidgetTextFont(TextFont_RadioSelected);
	SetWidgetTextColorAndOpacity(TextColorAndOpacity_RadioSelected);
}

void UTHRadioBtn_ImgText::NoselectedStyleShow_Text()
{
	SetWidgetTextFont(TextFont);
	SetWidgetTextColorAndOpacity(TextColorAndOpacity);
}

void UTHRadioBtn_ImgText::SelectedStyleShow_Image()
{
	SetWidgetImgBrush(ImgBrush_RadioSelected);
}

void UTHRadioBtn_ImgText::NoselectedStyleShow_Image()
{
	SetWidgetImgBrush(ImgBrush);
}
#pragma endregion RadioSelected

