// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "CommonMisc/THCommonVariableTypes.h"
#include "THNormalListItem.generated.h"

USTRUCT(BlueprintType)
struct FNormalItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 nID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 nNum = 0;
};


// ListItem基本信息
USTRUCT(BlueprintType)
struct FNormalListItemInfo : public FNormalItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) class UTexture2D* Icon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Str_1 = "";
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FString Str_2 = "";
};


/**
 * 不确定显示数量（动态创建Widget）时使用
 * By ZZQ 2020/08/21
 */
UCLASS(Abstract)
class UIMODULE_API UTHNormalListItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget, OptionalWidget), BlueprintReadWrite) class USizeBox* MySizeBox;
	UPROPERTY(Meta = (BindWidget, OptionalWidget), BlueprintReadWrite) class UCanvasPanel* MainCanvas = nullptr;
	UPROPERTY(Meta = (BindWidget, OptionalWidget), BlueprintReadWrite) class UTextBlock* Text_Num = nullptr;
	UPROPERTY(Meta = (BindWidget, OptionalWidget), BlueprintReadWrite) class UTHInteractiveWidgetBase* InteractBtn = nullptr;

public:
	virtual void Init();
	virtual void UpdateItemInfo(const FNormalListItemInfo& InItemInfo);
	UFUNCTION(BlueprintImplementableEvent, Category = "--ItemInfo--") void CallBP_ItemInfo(UPARAM(ref) const FNormalListItemInfo& InItemInfo);
	
	const int32& GetNormalItemID() { return nID; }

protected:
	int32 nID;
};