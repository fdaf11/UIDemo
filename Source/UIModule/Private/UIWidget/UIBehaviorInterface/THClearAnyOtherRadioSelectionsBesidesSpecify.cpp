#include "UIWidget/UIBehaviorInterface/THClearAnyOtherRadioSelectionsBesidesSpecify.h"
#include "Components/PanelWidget.h"
#include "UIWidget/UIBehaviorInterface/THUIRadioInterface.h"


void ITHClearAnyOtherRadioSelectionsBesidesSpecify::ClearAnyOtherRadioSelectionsBesidesSpecify(class UPanelWidget* PanelWidget, int32 nSpecifiedID)
{
	if (!PanelWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHClearAnyOtherRadioSelectionsBesidesSpecify::ClearAnyOtherRadioSelectionsBesidesSpecify, PanelWidget == nullptr"));
		return;
	}

	//其他同层级控件设置为非选中
	if (PanelWidget != nullptr)
	{
		int32 tnCount = PanelWidget->GetChildrenCount();
		for (int32 i = 0; i < tnCount; ++i)
		{
			UWidget* tChildWidget = PanelWidget->GetChildAt(i);
			if (tChildWidget != nullptr)
			{
				ITHUIRadioInterface* tRadioItem = Cast<ITHUIRadioInterface>(tChildWidget);
				if (tRadioItem != nullptr && tRadioItem->GetRadioSelectedParam() != nSpecifiedID)
					tRadioItem->UpdateRadioSelected(false);
			}
		}
	}
}
