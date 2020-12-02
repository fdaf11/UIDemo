// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THCommonUserWidget.generated.h"

DECLARE_DELEGATE(FOnTHUserWidgetShow);
DECLARE_DELEGATE(FOnTHUserWidgetHide);

/**
 * 作为前端/战斗端"页面"（类似战斗端背包、前端等一页布局的页面）的父类
 * TODO: 待接入: FrontendUserWidget;
 * By ZZQ 2020/09/11
 */
UCLASS(Abstract)
class UIMODULE_API UTHCommonUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FOnTHUserWidgetShow Handle_OnTHUserWidgetShow;
	FOnTHUserWidgetHide Handle_OnTHUserWidgetHide;

public:
	UFUNCTION(BlueprintCallable) virtual void Show(float fDelateTime = 0.f); // 使用该函数显示界面可触发NativeShown 和 Shown 事件; 便于自定义回调函数/蓝图函数
	UFUNCTION(BlueprintCallable) virtual void Hide(float fDelateTime = 0.f);

	UFUNCTION(BlueprintImplementableEvent) void Shown(float fDelateTime);
	UFUNCTION(BlueprintImplementableEvent) void Hidden(float fDelateTime);

protected:
	virtual void NativeConstruct() override;
	virtual	void NativeShown(float fDelateTime) {}
	virtual	void NativeHidden(float fDelateTime) {}
};