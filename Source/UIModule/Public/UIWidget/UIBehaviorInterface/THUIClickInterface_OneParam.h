// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "THUIClickInterface_OneParam.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIBehaviorOneParam_OnClicked_Dynamic, int32, nID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIBehaviorOneParam_OnPressed_Dynamic, int32, nID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIBehaviorOneParam_OnReleased_Dynamic, int32, nID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIBehaviorOneParam_OnHovered_Dynamic, int32, nID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIBehaviorOneParam_OnUnhovered_Dynamic, int32, nID);

//DECLARE_DELEGATE_OneParam(FUIBehaviorOneParam_OnClicked, int32);
//DECLARE_DELEGATE_OneParam(FUIBehaviorOneParam_OnPressed, int32);
//DECLARE_DELEGATE_OneParam(FUIBehaviorOneParam_OnReleased, int32);
//DECLARE_DELEGATE_OneParam(FUIBehaviorOneParam_OnHovered, int32);
//DECLARE_DELEGATE_OneParam(FUIBehaviorOneParam_OnUnhovered, int32);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHUIClickInterface_OneParam : public UInterface
{
	GENERATED_BODY()
};

/**
 * 按钮点击事件，单参int32，重写GetClickParam回调实现；需要自行对Button绑定/Or 调用 Execute;
 * 【】TODO 待研究：能否在此基础上再抽出一种情况，专门处理参数的问题，多参情况很麻烦
 * By ZhanZiqi 200227
 */
class UIMODULE_API ITHUIClickInterface_OneParam
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FUIBehaviorOneParam_OnClicked_Dynamic Handler_OnClicked_Dynamic;
	FUIBehaviorOneParam_OnPressed_Dynamic Handler_OnPressed_Dynamic;
	FUIBehaviorOneParam_OnReleased_Dynamic Handler_OnReleased_Dynamic;
	FUIBehaviorOneParam_OnHovered_Dynamic Handler_OnHovered_Dynamic;
	FUIBehaviorOneParam_OnUnhovered_Dynamic Handler_OnUnhovered_Dynamic;

protected:
	UFUNCTION() virtual void ExecuteOnClicked();
	UFUNCTION() virtual void ExecuteOnPressed();
	UFUNCTION() virtual void ExecuteOnReleased();
	UFUNCTION() virtual void ExecuteOnHovered();
	UFUNCTION() virtual void ExecuteOnUnhovered();

	//UFUNCTION() virtual void ExecuteOnClicked_Dynamic();

	// 回调传参
	virtual int32 GetClickParam() = 0;

#pragma region >>> Function Delegate <<< 
// BIndUobject改为AddDynamic操作; 	原因： 以源码为准, 统一修改为AddDyanmic; PS： AddDynamic有做检测，必须“直接传入函数 &Class::Method()，不能间接传递（即参数传给内层，内层再传最内层），内部有做ToString判断是否含有操作分隔符"::"，故，使用define的形式将原表达式扔进去.
public:
#define MACRO_AddUIBehaviorDynamic( UIBehavior, UserObject, FuncName ) \
Handler_##UIBehavior##_Dynamic.AddDynamic(UserObject, FuncName); \


//public:
//	template<typename ClassType>
//	//void BindOnClicked(ClassType* Object, typename FUIBehaviorOneParam_OnClicked::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
//	void BindOnClicked(ClassType* Object, void (ClassType::*Func)(int32 nID))
//	{
//		ClearOnClicked();
//		Handler_OnClicked.BindUObject(Object, Func);
//	}
//	template<typename ClassType>
//	void BindOnPressed(ClassType* Object, typename FUIBehaviorOneParam_OnPressed::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
//	{
//		ClearOnPressed();
//		Handler_OnPressed.BindUObject(Object, Func);
//	}
//	template<typename ClassType>
//	void BindOnReleased(ClassType* Object, typename FUIBehaviorOneParam_OnReleased::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
//	{
//		ClearOnReleased();
//		Handler_OnReleased.BindUObject(Object, Func);
//	}
//	template<typename ClassType>
//	void BindOnHovered(ClassType* Object, typename FUIBehaviorOneParam_OnHovered::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
//	{
//		ClearOnHovered();
//		Handler_OnHovered.BindUObject(Object, Func);
//	}
//	template<typename ClassType>
//	void BindOnUnhovered(ClassType* Object, typename FUIBehaviorOneParam_OnUnhovered::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
//	{
//		ClearOnUnhovered();
//		Handler_OnUnhovered.BindUObject(Object, Func);
//	}
//
//	inline void ClearOnClicked()
//	{
//		Handler_OnClicked.Unbind();
//	}
//	void ClearOnPressed()
//	{
//		Handler_OnPressed.Unbind();
//	}
//	void ClearOnReleased()
//	{
//		Handler_OnReleased.Unbind();
//	}
//	void ClearOnHovered()
//	{
//		Handler_OnHovered.Unbind();
//	}
//	void ClearOnUnhovered()
//	{
//		Handler_OnUnhovered.Unbind();
//	}


#pragma endregion
};
