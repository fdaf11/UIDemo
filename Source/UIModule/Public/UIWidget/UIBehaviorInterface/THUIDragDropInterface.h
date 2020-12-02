// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "THUIDragDropInterface.generated.h"

DECLARE_DELEGATE_OneParam(FOnDragDetectedEvent, int32)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHUIDragDropInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 拖拽接口
 */
class UIMODULE_API ITHUIDragDropInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class UTHDragDropOperation* CreateDragDropOp(class UObject* WorldContextObject);		// 【】TODO 待删; 目前通过获取PC当中的Config - DragDropOpClass自行创建.????【6】
	virtual int32 GetDragDropParam() = 0;
	
	virtual bool IsCanbeDragged() { return true; }
	
public:
	FOnDragDetectedEvent OnDragDetectedDelegate;

#pragma region FunctionDelegate
public:
	template<typename ClassType>
	void BindOnDragDetectedEvent(ClassType* Object, typename FOnDragDetectedEvent::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnDragDetectedEvent();
		OnDragDetectedDelegate.BindUObject(Object, Func);
	}
	void ClearOnDragDetectedEvent()
	{
		OnDragDetectedDelegate.Unbind();
	}

	UFUNCTION() virtual void ExecuteOnDragDetectedEvent();
#pragma endregion FunctionDelegate
};
