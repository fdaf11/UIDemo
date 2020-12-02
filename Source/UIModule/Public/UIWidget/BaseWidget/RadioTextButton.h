// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget/BaseWidget/RadioButton.h"
#include "RadioTextButton.generated.h"

/**
 * 
 */
UCLASS()
class UIMODULE_API URadioTextButton : public URadioButton
{
	GENERATED_BODY()

protected:
	virtual void OnWidgetRebuilt() override;
	class UTextBlock* MyText;
	bool bInit;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		FString TextString;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		FSlateColor TextColorAndOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		FSlateColor SelectedTextColorAndOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		FSlateFontInfo TextFont;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		int32 FontSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		int32 SelectedFontSize;
	
public:
	UFUNCTION(BlueprintCallable, Category = "RadioTextButton|Appearance")
		void Init();
	UFUNCTION(BlueprintCallable, Category = "RadioTextButton|Appearance")
		void SelectTextStyle();
	UFUNCTION(BlueprintCallable, Category = "RadioTextButton|Appearance")
		void NormalTextStyle();
	//UFUNCTION(BlueprintCallable, Category = "RadioTextButton|Appearance")
		void SetSelected(bool bInSelected);
	UFUNCTION(BlueprintCallable, Category = "RadioImageButton|Appearance")
		void SetTextString(const FString & s_String);
};
