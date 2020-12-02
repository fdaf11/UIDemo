// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIWidget/BaseWidget/THNormalBtn.h"
#include "UIWidget/UIBehaviorInterface/THHaveImgAndText2ConfigInterface.h"
#include "THNormalBtn_ImgText.generated.h"


/**
 * 按钮封装UserWidget（含Text/Image/Button）; 
 */
UCLASS()
class UIMODULE_API UTHNormalBtn_ImgText : public UTHNormalBtn, public ITHHaveImgAndText2ConfigInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UTextBlock* Text_Item;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UImage* IMG_Item;

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text") FString TextString = "";
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text") FSlateColor TextColorAndOpacity = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text") FSlateFontInfo TextFont;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Text") ESlateVisibility Visibility_Text = ESlateVisibility::SelfHitTestInvisible;

	// 图片配置
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Image") FSlateBrush Brush_Icon;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Image") ESlateVisibility Visibility_Image = ESlateVisibility::SelfHitTestInvisible;
	// 贴图-给材质赋值   // 【】TODO 更改为三态表现（后续可能改为材质参数）
	//UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Image|MaterialParam") class UTexture2D* Tex_Icon;

protected:
	virtual void OnWidgetRebuilt() override;

	virtual void InitConfigStyle_ImgAndText();

	virtual void ImageNormalStyleShow() {};			// Image表现模仿按钮三态; 【】TODO 利用材质较为合适
	virtual void ImagePressedStyleShow() {};
	virtual void ImageHoveredStyleShow() {};

#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#pragma region OverrideFunction
protected:
	virtual class UTextBlock* GetWidgetText() { return Text_Item; };
	virtual class UImage* GetWidgetImage() { return IMG_Item; };
#pragma endregion OverrideFunction

protected:
	//FName Name_ImageActive = FName(TEXT("ImageNormalColor"));		// 图片材质参数-激活后表现
	//FName Name_InactiveColor = FName(TEXT("ImagePressedColor"));	// 图片材质参数-无激活
	//FName Name_InactiveColor = FName(TEXT("ImageHoveredColor"));	// 图片材质参数-无激活
	//FName Name_InactiveColor = FName(TEXT("ImageDisableColor"));	// 图片材质参数-无激活

	UPROPERTY(Transient) class UMaterialInstanceDynamic* matIns_Icon = nullptr;
};