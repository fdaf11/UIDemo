// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "THDragDropOperation.generated.h"

DECLARE_DELEGATE_TwoParams(FOnWidgetDragged, const FPointerEvent&, UTHDragDropOperation*);

/**
 * 作为C++统一拖拽op; 仅增加了广播参数PointerEvent
 * By ZhanZiqi 202003
 */
UCLASS()
class UIMODULE_API UTHDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	//Widget拖拽时C++回调
	UFUNCTION(BlueprintCallable, Category = "--Drag--") void BpCallOnDragged(const FPointerEvent& PointerEvent);

#pragma region BindFunction
protected:
	void ExecuteOnDragged(const FPointerEvent& PointerEvent);

protected:
	FOnWidgetDragged Handler_OnDragged;
public:
	template<typename ClassType>
	void BindOnDragged(ClassType* Object, typename FOnWidgetDragged::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnDragged();
		Handler_OnDragged.BindUObject(Object, Func);
	}
	void ClearOnDragged()
	{
		Handler_OnDragged.Unbind();
	}
#pragma endregion BindFunction
};
