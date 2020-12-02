// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THComp_ListItemsWidget.generated.h"

/**
 * UTHSystem_ListItemsWidget 配合使用
 * By ZZQ 2020/09/06
 */
UCLASS(DefaultToInstanced, BlueprintType, Blueprintable/*, meta = (BlueprintSpawnableComponent, IgnoreCategoryKeywordsInSubclasses)*/)
class UIMODULE_API UTHComp_ListItemsWidget : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "--CustomSettings--", meta = (DisplayName = "Item蓝图类"))
	TSubclassOf<class UTHNormalListItem> ItemWidgetClass;

public:
	UPROPERTY() TArray<class UTHNormalListItem*> arr_PresetWidgetItems;		// 缓存Widget
	UPROPERTY() TMap<int32, class UTHNormalListItem* > map_ItemIDWidget;	// 道具ID对应的Item插槽控件
};