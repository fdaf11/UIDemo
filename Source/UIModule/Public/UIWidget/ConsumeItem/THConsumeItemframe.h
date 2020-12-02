// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/DelegateCombinations.h"
#include "THConsumeItemframe.generated.h"

/**
 * 
 */
UCLASS()
class UIMODULE_API UTHConsumeItemframe : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UNormalButton* NorBT_Add;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UTextBlock* Text_HaveNum;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UTextBlock* Text_NeedAfford;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UImage* IMG_Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSlateColor EnoughColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FSlateColor NotEnoughColor;

public:
	void SetItemInfo(int32 ItemType, int32 InHaveNum, int32 InDemandNum, class UTexture2D* ItemTex);
	UFUNCTION(BlueprintImplementableEvent) void CallBP_Enough2Afford(bool IsEnough2Afford, int32 InHaveNum, int32 InDemandNum);
};
