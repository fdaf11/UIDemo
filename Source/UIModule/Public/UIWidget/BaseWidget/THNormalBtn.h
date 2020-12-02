// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget/UIBehaviorInterface/THUIClickInterface_OneParam.h"
#include "UIWidget/UIBehaviorInterface/THHaveButton2ConfigInterface.h"
#include "Components/Button.h"

#include "THNormalBtn.generated.h"

/**
 * 常用Btn; 继承自UserWidget; 使用范围: 需动态赋值的Widget;
 * PS_1: 关于声音这一块，若觉得需便捷配置，可派生一个按钮供前端使用，提供默认的音效赋值(EMusicType); 普通情况下，应直接使用SoundBase进行配置即可.
 * PS_2:不同使用场景（即不同配置,相同功能）在"编辑器下用创建不同的用户蓝图组件进行表示"，不在程序当中设置太多的默认值; eg. 前端普通按钮统一按下音效, 创建一FrontendBtn即可
 */
UCLASS()
class UIMODULE_API UTHNormalBtn : public UUserWidget, public ITHUIClickInterface_OneParam, public ITHHaveButton2ConfigInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UButton* Btn;

	// 点击后的传参
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--") int32 nID;
	// 按钮三态
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Button") FButtonStyle TheButtonStyle;
	// 播放音乐
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "--CustomSettings--|Music") class USoundBase* ClickedPlaySound;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "--UIBehavior--") void OnWidgetClicked(int32 InID);

protected:
	virtual void NativeConstruct() override;
	virtual void OnWidgetRebuilt() override;
	virtual void InitConfigStyle_Button();

#if WITH_EDITOR
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#pragma region OverrideFunction
// ClickInterface
protected:
	virtual int32 GetClickParam() { return nID; };
	virtual void ExecuteOnClicked() override;
	class UButton* GetWidgetBtn() { return Btn; }
#pragma endregion OverrideFunction

};