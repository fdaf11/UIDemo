// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/Button.h"
#include "THUIRadioInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIBehaviorOneParam_OnRadioSelected_Dynamic, int32, nID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIBehaviorOneParam_OnNoRadioSelected_Dynamic, int32, nID);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHUIRadioInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 单选UI接口; 
 * 子类需调用RegisterUIOnClicked 注册UI被点击后触发单选那效果; 【】TODO 也需后续可取消接口，直接将功能扔进RadioBtn；待整理完毕后处理
 */
class UIMODULE_API ITHUIRadioInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FUIBehaviorOneParam_OnRadioSelected_Dynamic Handler_OnRadioSelected_Dynamic;
	FUIBehaviorOneParam_OnNoRadioSelected_Dynamic Handler_OnNoRadioSelected_Dynamic;

public:
	virtual void UpdateRadioSelected(bool InbSelections);
	virtual bool GetbRadioSelected() = 0;
	virtual int32 GetRadioSelectedParam() = 0;
protected:
	virtual void SetbRadioSelected(bool bSelect) = 0;
	virtual class UUserWidget* GetRadioWidget() = 0;			// 【】TODO 待改成回调，提供给外界，目前方式较耦合
	virtual void SelectedStyleShow() {};
	virtual void NoselectedStyleShow() {};

#pragma region FunctionDelegate
public:
#define MACRO_AddUIRadioSelectedDynamic( UIBehavior, UserObject, FuncName ) \
Handler_##UIBehavior##_Dynamic.AddDynamic(UserObject, FuncName); \

#pragma endregion FunctionDelegate
};
