// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget/BaseWidget/THRetainerBox.h"
#include "THRetainerBox_CurveHud.generated.h"

/**
 * EffectMaterial为曲面HUD材质实例
 * By ZZQ 2020/08/19
 */
UCLASS()
class UIMODULE_API UTHRetainerBox_CurveHud : public UTHRetainerBox
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "--CustomSettings--", meta = (DisplayName = "曲面倾斜度", ClampMax = 1.f, ClampMin = 0.1f, UIMax = 1.f, UIMin = 0.1f)) float fCurveFloat = 0.2f;

#if WITH_EDITORONLY_DATA
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "--CustomSettings--", meta = (DisplayName = "使用默认配置")) uint8 bUsePresetConfig : 1;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "--CustomSettings--", meta = (DisplayName = "实时渲染（不想卡死则必看ToolTip）", ToolTip = "将UI缩放至全屏可见，并将所有UI上锁，只能通过CanvasSlot调整UI大小、位置（除非是程序，且使用调试运行编辑器，而且需放大到一定程度才能使用拖拽调整大小，使用结束需取消勾选")) uint8 bRealTimeRendering : 1;
#endif

#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void UpdatePresetConfig();
#endif

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnWidgetRebuilt() override;
	void UpdateCurveHudValue();
};