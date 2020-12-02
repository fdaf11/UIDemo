// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THHudAnimItem_BaseMove.h"
#include "THHudAnimItem_MoveCurve.generated.h"

/**
 * 
 * By ZZQ 2020/10/26
 */
UCLASS(Abstract)
class UIMODULE_API UTHHudAnimItem_MoveCurve : public UTHHudAnimItem_BaseMove
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite) FTimerHandle AnimOverTimerHandle;					// OverTimeHandle
	UPROPERTY(BlueprintReadWrite) FVector2D SumDistance = FVector2D::ZeroVector;	// 总路程
	UPROPERTY(BlueprintReadWrite) float AccumulatedTimeSecdons = 0.f;				// 累积时间
	UPROPERTY(BlueprintReadWrite) class UCurveFloat* mCurveFloat = nullptr;			// 速度曲线
	
	//UPROPERTY(BlueprintReadOnly) FVector2D Rotation = FVector2D::ZeroVector;
};