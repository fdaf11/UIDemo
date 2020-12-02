#include "UIWidget/BaseWidget/THNormalBtn_ImgText.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTHNormalBtn_ImgText::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	
	InitConfigStyle_ImgAndText();
}

void UTHNormalBtn_ImgText::InitConfigStyle_ImgAndText()
{
	SetWidgetImgBrush(Brush_Icon);
	SetWidgetText(TextString);
	SetWidgetTextFont(TextFont);
	SetWidgetTextColorAndOpacity(TextColorAndOpacity);
	SetWidgetTextVisiblity(Visibility_Text);			// OnWidgetRebuilt当中设置Visibility会导致"眼睛"图标不可使用, By ZZQ
	SetWidgetImgVisiblity(Visibility_Image);
}

#if WITH_EDITOR
void UTHNormalBtn_ImgText::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	InitConfigStyle_ImgAndText();
}
#endif

