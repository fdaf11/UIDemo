// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget/BaseWidget/RadioButton.h"
#include "RadioImageButton.generated.h"

//DECLARE_DELEGATE_TwoParams(FBtnEventHandler_nID, int32, int32)
/**
* 继承Radiobutton，同一个父控件下最多只会有一个Radiobutton Selected
* 多加了一张图片
*/
UCLASS()
class UIMODULE_API URadioImageButton : public URadioButton
{
	GENERATED_BODY()
	
protected:
	virtual void OnWidgetRebuilt() override;
	//TSharedPtr<class UImage> MyImage;
	class UImage* MyImage;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		class UTexture2D* MainTexture;


public:
	UFUNCTION(BlueprintCallable, Category = "RadioImageButton|Appearance")
		void SetMainTexture(UTexture2D* Image);

};



