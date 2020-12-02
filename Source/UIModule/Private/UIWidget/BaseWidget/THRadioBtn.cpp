#include "UIWidget/BaseWidget/THRadioBtn.h"
#include "UIWidget/BaseWidget/THNormalBtn.h"
#include "Components/CanvasPanel.h"

void UTHRadioBtn::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	UpdateRadioSelected(bRadioSelected);
}

#if WITH_EDITOR
void UTHRadioBtn::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	UpdateRadioSelected(bRadioSelected);
}
#endif

void UTHRadioBtn::SelectedStyleShow()
{
	SelectedStyleShow_Button();
	CallBPSelectedStyleShown();
}

void UTHRadioBtn::NoselectedStyleShow()
{
	NoselectedStyleShow_Button();
	CallBPNoselectedStyleShown();
}

void UTHRadioBtn::SelectedStyleShow_Button()
{
	SetPadding(OverallPadding_RadioSelected);
	SetWidgetButtonStyle(BtnStyle_RadioSelected);
}

void UTHRadioBtn::NoselectedStyleShow_Button()
{
	SetPadding(OverallPadding_NoRadioSelected);
	SetWidgetButtonStyle(TheButtonStyle);
}

void UTHRadioBtn::ExecuteOnClicked()
{
	Super::ExecuteOnClicked();
	
	OnRadioBtnSelfOnClicked(GetClickParam());
}

void UTHRadioBtn::OnRadioBtnSelfOnClicked(int32 InID)
{
	UpdateRadioSelected(true);
}