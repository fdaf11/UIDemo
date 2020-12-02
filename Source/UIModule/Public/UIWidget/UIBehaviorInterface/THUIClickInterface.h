// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "THUIClickInterface.generated.h"

DECLARE_DELEGATE(FUIBehavior_OnClicked);
DECLARE_DELEGATE(FUIBehavior_OnPressed);
DECLARE_DELEGATE(FUIBehavior_OnReleased);
DECLARE_DELEGATE(FUIBehavior_OnHovered);
DECLARE_DELEGATE(FUIBehavior_OnUnhovered);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHUIClickInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 按钮点击事件，无参
 * By ZhanZiqi 200227
 */
class UIMODULE_API ITHUIClickInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Function Delegate ---------------------------------
public:
	FUIBehavior_OnClicked Handler_OnClicked;
	FUIBehavior_OnPressed Handler_OnPressed;
	FUIBehavior_OnReleased Handler_OnReleased;
	FUIBehavior_OnHovered Handler_OnHovered;
	FUIBehavior_OnUnhovered Handler_OnUnhovered;

public:
	template<typename ClassType>
	void BindOnClicked(ClassType* Object, typename FUIBehavior_OnClicked::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnClicked();
		Handler_OnClicked.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnPressed(ClassType* Object, typename FUIBehavior_OnPressed::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnPressed();
		Handler_OnPressed.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnReleased(ClassType* Object, typename FUIBehavior_OnReleased::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnReleased();
		Handler_OnReleased.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnHovered(ClassType* Object, typename FUIBehavior_OnHovered::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnHovered();
		Handler_OnHovered.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnUnhovered(ClassType* Object, typename FUIBehavior_OnUnhovered::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnUnhovered();
		Handler_OnUnhovered.BindUObject(Object, Func);
	}

	void ClearOnClicked()
	{
		Handler_OnClicked.Unbind();
	}
	void ClearOnPressed()
	{
		Handler_OnPressed.Unbind();
	}
	void ClearOnReleased()
	{
		Handler_OnReleased.Unbind();
	}
	void ClearOnHovered()
	{
		Handler_OnHovered.Unbind();
	}
	void ClearOnUnhovered()
	{
		Handler_OnUnhovered.Unbind();
	}

	UFUNCTION() virtual void ExecuteOnClicked();
	UFUNCTION() virtual void ExecuteOnPressed();
	UFUNCTION() virtual void ExecuteOnReleased();
	UFUNCTION() virtual void ExecuteOnHovered();
	UFUNCTION() virtual void ExecuteOnUnhovered();
};
