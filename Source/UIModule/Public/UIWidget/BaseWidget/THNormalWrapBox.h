// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "CommonMisc/THCommonVariableTypes.h"
#include "Components/WrapBox.h"
#include "UIWidget/BaseWidget/THNormalListItem.h"
#include "THNormalWrapBox.generated.h"

/**
 * 不确定显示数量（动态创建Widget）时使用
 * TODO：缺少增删改查; 目前以功能为主；后续再派生子类
 * By ZZQ 2020/08/21
 */
UCLASS()
class UIMODULE_API UTHNormalWrapBox : public UWrapBox
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--", meta = (DisplayName = "Item蓝图类")) TSubclassOf<class UTHNormalListItem> ItemWidgetClass;
public:
	virtual void Init();
	UFUNCTION(BlueprintCallable) void InitAllItemsWidgetInfo(const TArray<FNormalListItemInfo>& InArr_PropInfo);	// 重置列表
	
	UFUNCTION(BlueprintCallable) virtual void Show();
	UFUNCTION(BlueprintCallable) virtual void Hide();

protected:
	// 【】TODO 多加个方法，可赋值初始值?
	bool CreateDefaultWidget(class UTHNormalListItem*& InItemWidget);
	bool CreateDefaultWidget(int32 InNum);
	void InitItemWidget(class UTHNormalListItem*& InItemWidget);

protected:
	UPROPERTY() TArray<class UTHNormalListItem*> arr_PresetWidgetItems;		// 缓存Widget
	UPROPERTY() TMap<int32, class UTHNormalListItem* > map_ItemIDWidget;	// 道具ID对应的道具插槽控件
private:
	void ClearItems();			// 清空Items
	void Clear();				// 清除所有缓存
};