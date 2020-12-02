#include "UIWidget/BaseWidget/THNormalWrapBox.h"
#include "Components/PanelWidget.h"
#include "UIWidget/BaseWidget/THNormalListItem.h"

void UTHNormalWrapBox::Init()
{
	Clear();
}

void UTHNormalWrapBox::InitAllItemsWidgetInfo(const TArray<FNormalListItemInfo>& InArr_PropInfo)
{
	ClearItems();

	const int32 tnInfoNum = InArr_PropInfo.Num();
	const int32 tnNeedCreateWGNum = tnInfoNum - arr_PresetWidgetItems.Num();
	if (tnNeedCreateWGNum > 0)
		CreateDefaultWidget(tnNeedCreateWGNum);		// 若缺少备用Widget, 增加arr_PresetWidgetItems数量

	const int32 tnPresetWidgetNum = arr_PresetWidgetItems.Num();
	if (tnPresetWidgetNum < tnInfoNum)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHNormalListView::InitAllItemsWidgetInfo, tCacheWidgetNum < tnInfoNum, tCacheWidgetNum: [%d], tnInfoNum: [%d]"), tnPresetWidgetNum, tnInfoNum);
		return;
	}

	// 信息赋值
	for (int32 i = 0; i < tnInfoNum; ++i)
	{
		const FNormalListItemInfo& tItemInfo = InArr_PropInfo[i];
		class UTHNormalListItem*& tItemWidget = arr_PresetWidgetItems[i];
		if (!tItemWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("UTHNormalListView::InitAllItemsWidgetInfo, !tItemWidget, i: %d"), i);
			return;
		}
		
		tItemWidget->UpdateItemInfo(tItemInfo);
		tItemWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		map_ItemIDWidget.Emplace(tItemInfo.nID, tItemWidget);
	}

	// 多余隐藏
	for (int32 i = tnInfoNum; i < tnPresetWidgetNum; i++)
	{
		class UTHNormalListItem*& tItemWidget = arr_PresetWidgetItems[i];
		if (tItemWidget)
			tItemWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

bool UTHNormalWrapBox::CreateDefaultWidget(int32 InNum)
{
	UTHNormalListItem* tWidget = nullptr;
	for (int32 i = 0; i < InNum; ++i)
	{
		tWidget = nullptr;
		if (!CreateDefaultWidget(tWidget))
		{
			UE_LOG(LogTemp, Warning, TEXT("UTHNormalListView::CreateDefaultWidget, !tWidget"));
			return false;
		}
		
		InitItemWidget(tWidget);
	}

	return true;
}

bool UTHNormalWrapBox::CreateDefaultWidget(class UTHNormalListItem*& InItemWidget)
{
	InItemWidget = CreateWidget<UTHNormalListItem>(GetWorld(), ItemWidgetClass);
	if (!InItemWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHPropCards::CreatePropCardsItemWidget, tItem == nullptr"));
		return false;
	}

	return true;
}

void UTHNormalWrapBox::InitItemWidget(class UTHNormalListItem*& InItemWidget)
{
	if (!InItemWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHNormalListView::InitItemWidget, !InItemWidget"));
		return;
	}
	
	AddChild(InItemWidget);
	InItemWidget->Init();
	arr_PresetWidgetItems.Emplace(InItemWidget);
	//map_ItemIDWidget.Emplace(InItemWidget);
}

void UTHNormalWrapBox::ClearItems()
{
	map_ItemIDWidget.Empty();

	for (int32 i = 0; i < arr_PresetWidgetItems.Num(); ++i)
	{
		UTHNormalListItem*& tItem = arr_PresetWidgetItems[i];
		if (tItem)
			tItem->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UTHNormalWrapBox::Clear()
{
	ClearChildren();
	map_ItemIDWidget.Empty();
	arr_PresetWidgetItems.Empty();
}

void UTHNormalWrapBox::Show()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UTHNormalWrapBox::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
