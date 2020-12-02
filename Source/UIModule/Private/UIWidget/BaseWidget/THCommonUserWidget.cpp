#include "UIWidget/BaseWidget/THCommonUserWidget.h"


void UTHCommonUserWidget::Show(float fDelateTime)
{
	if (IsVisible())
		return;

	this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	NativeShown(fDelateTime);
	Shown(fDelateTime);
	Handle_OnTHUserWidgetShow.ExecuteIfBound();
}

void UTHCommonUserWidget::Hide(float fDelateTime)
{
	if (!IsVisible())
		return;

	NativeHidden(fDelateTime);
	Hidden(fDelateTime);
	this->SetVisibility(ESlateVisibility::Collapsed);
	Handle_OnTHUserWidgetHide.ExecuteIfBound();
}

void UTHCommonUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
