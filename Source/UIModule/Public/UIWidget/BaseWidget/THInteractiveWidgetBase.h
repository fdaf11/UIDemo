// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget/UIBehaviorInterface/THUIClickInterface_OneParam.h"
#include "Styling/SlateTypes.h"
#include "UIWidget/UIBehaviorInterface/THUIDragDropInterface.h"
#include "UIWidget/BaseWidget/THRadioBtn_ImgText.h"
#include "THInteractiveWidgetBase.generated.h"

/**
 * 常用按钮、IMG相结合的UserWidget默认信息封装（作为用户UI交互组件基类）
 * Img和Btn两者都启用时按钮Style将设置为None（防止点击被图片拦截）
 * 不使用按钮时（即仅使用图片时），需主动调用ExecuteUIBehavior; 适用情况：拖拽操作
 * // 【】TODO 正在处理：改成继承自“RadioBtn_ImgText"，并增加“拖拽相关”逻辑
 * TODO_1: bool bXXX 好像没有必要存在，若真要使用时……继承下来一个就可以了.
 * PS_1: 若需拖拽，请将bButton = false; 否则按钮会将拖拽事件捕捉，导致DragDropOp.OnDragged无法触发.
 */
UCLASS()
class UIMODULE_API UTHInteractiveWidgetBase : public UTHRadioBtn_ImgText, public ITHUIDragDropInterface
{
	GENERATED_BODY()

public:
	// 启用单选
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--") uint8 bOpenRadioSelections : 1;
	// 启用拖拽
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--") uint8 bCanBeDragged : 1;
	// 启用图片
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--|Image") uint8 bImage : 1;
	// 启用按钮
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--|Button") uint8 bButton : 1;
	// 启用文字
	UPROPERTY(EditInstanceOnly, Category = "--CustomSettings--|Text") uint8 bText : 1;

public:
	virtual void UpdateRadioSelected(bool InbSelections) override;

protected:
	virtual void NativeConstruct() override;

#pragma region OverrideFunction
public:
	virtual int32 GetDragDropParam() { return nID; };
#pragma endregion OverrideFunction
};
