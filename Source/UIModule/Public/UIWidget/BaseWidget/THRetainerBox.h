// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RetainerBox.h"
#include "THRetainerBox.generated.h"

/**
 * 
 * 问题1：任何在CurveHud当中的Visible控件，经材质渲染后，点击区域会出现在最上层; 
 * By ZZQ 2020/08/19
 */
UCLASS()
class UIMODULE_API UTHRetainerBox : public URetainerBox
{
	GENERATED_BODY()

protected:
	virtual void OnWidgetRebuilt() override;
	virtual void SetVisibleWidget2HitTestWhenBeCovered() {}
};