// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "NormalButton.generated.h"

DECLARE_DELEGATE_OneParam(FNormalButton_OnClicked, int32);
DECLARE_DELEGATE_OneParam(FNormalButton_OnPressed, int32);
DECLARE_DELEGATE_OneParam(FNormalButton_OnReleased, int32);
DECLARE_DELEGATE_OneParam(FNormalButton_OnHovered, int32);
DECLARE_DELEGATE_OneParam(FNormalButton_OnUnhovered, int32);
/**
 * 通用按钮，Click事件带ID参数
 */
UCLASS()
class UIMODULE_API UNormalButton : public UButton
{
	GENERATED_BODY()
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	FReply ExecuteOnClicked();
	void ExecuteOnPressed();
	void ExecuteOnReleased();
	void ExecuteOnHovered();
	void ExecuteOnUnhovered();


	FNormalButton_OnClicked Handler_OnClicked;
	FNormalButton_OnPressed Handler_OnPressed;
	FNormalButton_OnReleased Handler_OnReleased;
	FNormalButton_OnHovered Handler_OnHovered;
	FNormalButton_OnUnhovered Handler_OnUnhovered;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "--CustomSettings--") int32 nID = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "使用通用按钮按下音效配置"), Category = "--CustomSettings--")
	//bool bUseCommonMusic = true;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "自定义点击音效", EditCondition = "!bUseCommonMusic"), Category = "--CustomSettings--")
	//FString ClickedWwiseEventName = "";

#pragma region >>> Function Delegate <<< 
public:
	template<typename ClassType>
	void BindBtnEvent(ClassType* Object, typename FNormalButton_OnClicked::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearBtnEvent();
		Handler_OnClicked.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnPressed(ClassType* Object, typename FNormalButton_OnPressed::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnPressed();
		Handler_OnPressed.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnReleased(ClassType* Object, typename FNormalButton_OnReleased::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnReleased();
		Handler_OnReleased.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnHovered(ClassType* Object, typename FNormalButton_OnHovered::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnHovered();
		Handler_OnHovered.BindUObject(Object, Func);
	}
	template<typename ClassType>
	void BindOnUnhovered(ClassType* Object, typename FNormalButton_OnUnhovered::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearOnUnhovered();
		Handler_OnUnhovered.BindUObject(Object, Func);
	}

	inline void ClearBtnEvent()
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

#pragma endregion
};
