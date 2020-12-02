// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget/BaseWidget/THNormalBtn.h"
#include "UIWidget/UIBehaviorInterface/THUIRadioInterface.h"
#include "UIWidget/UIBehaviorInterface/THHaveInteractiveWidget2ConfigInterface.h"
#include "UIWidget/BaseWidget/THNormalBtn.h"
#include "Components/Button.h"
#include "THRadioBtn.generated.h"


/**
 * 通用RadioBtn，同一个父控件下最多只会有一个Radiobutton Selected; ;
 * 选择继承NormalButton的原因，减少一层配置
 */
UCLASS()
class UIMODULE_API UTHRadioBtn : public UTHNormalBtn, public ITHUIRadioInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly) class UCanvasPanel* MainCanvas;

	// 选中状态
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--") uint8 bRadioSelected : 1;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--") FMargin OverallPadding_RadioSelected;		// 不等于Button当中的按下缩放，= “整体UserWidget的Padding改变”; 【】TODO 貌似作用相反????
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--") FMargin OverallPadding_NoRadioSelected;
	// 按钮Padding，不过测试后没什么效果.【】TODO 可能后续还是得用缩小SizeBox进行尝试 
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Button|Radio") FButtonStyle BtnStyle_RadioSelected;

protected:
	//virtual void NativeConstruct() override;
	virtual void OnWidgetRebuilt() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#pragma region RadioSelected
public:
	virtual bool GetbRadioSelected() { return bRadioSelected; };
	virtual int32 GetRadioSelectedParam() { return nID; };

protected:
	virtual void SelectedStyleShow() override;
	virtual void NoselectedStyleShow() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "--Radio--") void CallBPSelectedStyleShown();
	UFUNCTION(BlueprintImplementableEvent, Category = "--Radio--") void CallBPNoselectedStyleShown();
	virtual void SetbRadioSelected(bool bSelect) { bRadioSelected = bSelect; };
	virtual class UUserWidget* GetRadioWidget() { return this; };
	virtual void OnRadioBtnSelfOnClicked(int32 InID);				// 被选中后自身回调事件

	// Button
	virtual void SelectedStyleShow_Button();
	virtual void NoselectedStyleShow_Button();
#pragma endregion RadioSelected

#pragma region OverrideFunction
protected:
	virtual void ExecuteOnClicked() override;
#pragma endregion OverrideFunction
};