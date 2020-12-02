// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget/BaseWidget/THNormalBtn_ImgText.h"
//#include "UIWidget/UIBehaviorInterface/THUIRadioInterface_ImgText.h"
#include "UIWidget/BaseWidget/THRadioBtn.h"
#include "UIWidget/UIBehaviorInterface/THHaveImgAndText2ConfigInterface.h"
#include "THRadioBtn_ImgText.generated.h"


/**
 * 单选按钮封装（含Image/Text）
 * RadioBtn_ImgText当中的图片和文字由自身配置 以及存储
 */
UCLASS()
class UIMODULE_API UTHRadioBtn_ImgText : public UTHRadioBtn, public ITHHaveImgAndText2ConfigInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UTextBlock* Text_Item;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UImage* IMG_Item;
	// Text
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text") FString TextString = "";
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text") FSlateFontInfo TextFont;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text") ESlateVisibility Visibility_Text = ESlateVisibility::HitTestInvisible;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text") FSlateColor TextColorAndOpacity = FSlateColor(FLinearColor(1.f, 1.f, 1.f));

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text|Radio") FSlateFontInfo TextFont_RadioSelected; 
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text|Radio") FSlateColor TextColorAndOpacity_RadioSelected = FSlateColor(FLinearColor(1.f, 1.f, 1.f));

	// Img
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Image") ESlateVisibility Visibility_Image = ESlateVisibility::HitTestInvisible;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Image") FSlateBrush ImgBrush;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Image|Radio") FSlateBrush ImgBrush_RadioSelected;

protected:
	virtual void OnWidgetRebuilt() override;
	virtual void InitConfigStyle_ImgAndText();
	virtual void SelectedStyleShow() override;
	virtual void NoselectedStyleShow() override;

#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#pragma region RadioSelected
protected:
	virtual void SelectedStyleShow_Text();			
	virtual void NoselectedStyleShow_Text();
	virtual void SelectedStyleShow_Image();
	virtual void NoselectedStyleShow_Image();
#pragma endregion RadioSelected

#pragma region OverrideFunction
protected:
	virtual class UTextBlock* GetWidgetText() { return Text_Item; }
	virtual class UImage* GetWidgetImage() { return IMG_Item; }
#pragma endregion OverrideFunction
};
