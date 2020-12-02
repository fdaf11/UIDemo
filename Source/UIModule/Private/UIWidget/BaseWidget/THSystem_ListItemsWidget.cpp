#include "UIWidget/BaseWidget/THSystem_ListItemsWidget.h"
#include "UIWidget/BaseWidget/THComp_ListItemsWidget.h"
#include "Components/PanelWidget.h"
#include "UIWidget/BaseWidget/THNormalListItem.h"

void UTHSystem_ListItemsWidget::Init(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp)
{
	Clear(InPanelWidget, InComp);
}

void UTHSystem_ListItemsWidget::InitAllItemsWidgetInfo(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp, const TArray<FNormalListItemInfo>& InArr_PropInfo)
{
	if (!InPanelWidget || !InComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHSystem_ListItemsWidget::InitAllItemsWidgetInfo, !InPanelWidget || !InComp"));
		return;
	}

	ClearItems(InComp);

	const int32 tnInfoNum = InArr_PropInfo.Num();
	const int32 tnNeedCreateWGNum = tnInfoNum - InComp->arr_PresetWidgetItems.Num();
	if (tnNeedCreateWGNum > 0)
		CreateDefaultWidget(InPanelWidget, InComp, tnNeedCreateWGNum);		// 若缺少备用Widget, 增加arr_PresetWidgetItems数量

	const int32 tnPresetWidgetNum = InComp->arr_PresetWidgetItems.Num();
	if (tnPresetWidgetNum < tnInfoNum)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHNormalListView::InitAllItemsWidgetInfo, tCacheWidgetNum < tnInfoNum, tCacheWidgetNum: [%d], tnInfoNum: [%d]"), tnPresetWidgetNum, tnInfoNum);
		return;
	}

	// 信息赋值
	for (int32 i = 0; i < tnInfoNum; ++i)
	{
		const FNormalListItemInfo& tItemInfo = InArr_PropInfo[i];
		class UTHNormalListItem*& tItemWidget = InComp->arr_PresetWidgetItems[i];
		if (!tItemWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("UTHNormalListView::InitAllItemsWidgetInfo, !tItemWidget, i: %d"), i);
			return;
		}

		tItemWidget->UpdateItemInfo(tItemInfo);
		tItemWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		InComp->map_ItemIDWidget.Emplace(tItemInfo.nID, tItemWidget);
	}

	// 多余隐藏
	for (int32 i = tnInfoNum; i < tnPresetWidgetNum; i++)
	{
		class UTHNormalListItem*& tItemWidget = InComp->arr_PresetWidgetItems[i];
		if (tItemWidget)
			tItemWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

bool UTHSystem_ListItemsWidget::CreateDefaultWidget(class UTHComp_ListItemsWidget* InComp, class UTHNormalListItem*& InItemWidget)
{
	if (!InComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHSystem_ListItemsWidget::CreateDefaultWidget, !InComp"));
		return false;
	}

	InItemWidget = CreateWidget<UTHNormalListItem>(GetWorld(), InComp->ItemWidgetClass);
	if (!InItemWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHPropCards::CreatePropCardsItemWidget, tItem == nullptr"));
		return false;
	}

	return true;
}

bool UTHSystem_ListItemsWidget::CreateDefaultWidget(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp, int32 InNum)
{
	UTHNormalListItem* tWidget = nullptr;
	for (int32 i = 0; i < InNum; ++i)
	{
		tWidget = nullptr;
		if (!CreateDefaultWidget(InComp, tWidget))
		{
			UE_LOG(LogTemp, Warning, TEXT("UTHNormalListView::CreateDefaultWidget, !tWidget"));
			return false;
		}

		InitItemWidget(InPanelWidget, InComp, tWidget);
	}

	return true;
}

void UTHSystem_ListItemsWidget::InitItemWidget(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp, class UTHNormalListItem*& InItemWidget)
{
	if (!InPanelWidget || !InItemWidget || !InComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHSystem_ListItemsWidget::InitItemWidget, !InPanelWidget || !InItemWidget || !InComp"));
		return;
	}
	
	InPanelWidget->AddChild(InItemWidget);
	InItemWidget->Init();
	InComp->arr_PresetWidgetItems.Emplace(InItemWidget);
	//map_ItemIDWidget.Emplace(InItemWidget);
}

void UTHSystem_ListItemsWidget::ClearItems(class UTHComp_ListItemsWidget* InComp)
{
	if (!InComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHSystem_ListItemsWidget::ClearItems, !InComp"));
		return;
	}

	InComp->map_ItemIDWidget.Empty();

	for (int32 i = 0; i < InComp->arr_PresetWidgetItems.Num(); ++i)
	{
		UTHNormalListItem*& tItem = InComp->arr_PresetWidgetItems[i];
		if (tItem)
			tItem->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UTHSystem_ListItemsWidget::Clear(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp)
{
	if (!InPanelWidget || !InComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHSystem_ListItemsWidget::Clear, !InPanelWidget || !InComp"));
		return;
	}

	InPanelWidget->ClearChildren();
	InComp->map_ItemIDWidget.Empty();
	InComp->arr_PresetWidgetItems.Empty();
}
