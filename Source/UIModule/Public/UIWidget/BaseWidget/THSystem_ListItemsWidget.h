// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "CommonMisc/THCommonVariableTypes.h"
#include "UIWidget/BaseWidget/THNormalListItem.h"
#include "THSystem_ListItemsWidget.generated.h"

/**
 * 仿ecs; 尝试将ItemsList的逻辑接到此处; 目前仅提供功能：一次性加载所有Item: InitAllItemsWidgetInfo
 * PanleWidget -> Component Widget（存储数据）; System（负责函数处理）
 * TODO: 也许应该提供一些回调给外部？
 * TODO1: CreateDefaultWidget重载函数,可赋初始值
 * By ZZQ 2020/09/06
 */
UCLASS()
class UIMODULE_API UTHSystem_ListItemsWidget : public UObject
{
	GENERATED_BODY()
public:
	// InPanelWidget - InComp的父组件
	UFUNCTION(BlueprintCallable) void Init(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp);
	UFUNCTION(BlueprintCallable) void InitAllItemsWidgetInfo(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp, const TArray<FNormalListItemInfo>& InArr_PropInfo);
	void ClearItems(class UTHComp_ListItemsWidget* InComp);											// 清空Items 并 隐藏所有缓存Widget
	void Clear(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp);			// 清除所有缓存

private:
	bool CreateDefaultWidget(class UTHComp_ListItemsWidget* InComp, class UTHNormalListItem*& InItemWidget);
	bool CreateDefaultWidget(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp, int32 InNum);
	void InitItemWidget(class UPanelWidget* InPanelWidget, class UTHComp_ListItemsWidget* InComp, class UTHNormalListItem*& InItemWidget);
};