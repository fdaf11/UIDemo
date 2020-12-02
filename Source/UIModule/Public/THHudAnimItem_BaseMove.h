// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "THHudAnimItem_BaseMove.generated.h"


//DECLARE_DYNAMIC_DELEGATE_OneParam(FOnHudMoveAnimStart, int32, InID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnHudMoveAnimOver, int32, InID);

/**
 * 
 * By ZZQ 2020/10/26
 */
UCLASS(Abstract)
class UIMODULE_API UTHHudAnimItem_BaseMove : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (DisplayName = "Icon初始角度向量")) FVector2D IconOriginPivot = FVector2D(0.f, -1.f);
	UPROPERTY(meta = (BindWidget, OptionalWidget), BlueprintReadWrite) class UImage* IMG_Icon = nullptr;

	UPROPERTY(BlueprintReadWrite) int32 nID = 0;
	UPROPERTY(BlueprintReadWrite) FVector2D MoveStartPos = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadWrite) FVector2D MoveGoalPos = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadWrite) uint8 bIsWidgetPlayingAnim : 1;
	UPROPERTY(BlueprintReadWrite) float fInterpSpeed = 1.f;
	//UPROPERTY(BlueprintAssignable, BlueprintReadWrite) FOnHudMoveAnimStart Handle_OnHudMoveAnimStart;
	UPROPERTY(BlueprintReadWrite) FOnHudMoveAnimOver Handle_OnHudMoveAnimOver;
};