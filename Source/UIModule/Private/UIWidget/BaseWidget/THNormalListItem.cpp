#include "UIWidget/BaseWidget/THNormalListItem.h"
#include "UIWidget/UIBehaviorInterface/THHaveButton2ConfigInterface.h"
#include "Components/TextBlock.h"
#include "UIWidget/BaseWidget/THInteractiveWidgetBase.h"

void UTHNormalListItem::Init()
{

}

void UTHNormalListItem::UpdateItemInfo(const FNormalListItemInfo& InItemInfo)
{
	nID = InItemInfo.nID;

	if (InteractBtn)
		InteractBtn->SetWidgetButtonStyleFromTexture(InItemInfo.Icon);

	if (Text_Num)
		Text_Num->SetText(FText::AsNumber(InItemInfo.nNum));

	CallBP_ItemInfo(InItemInfo);
}
