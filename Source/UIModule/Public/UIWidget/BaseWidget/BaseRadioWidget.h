// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseRadioWidget.generated.h"

DECLARE_DELEGATE_OneParam(FBaseRadioWidget_OnClicked, int32)
/**
 * 
 */
UCLASS()
class UIMODULE_API UBaseRadioWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	FBaseRadioWidget_OnClicked  OnSelect_Delegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam") int32 nParamID;
	//外部使用SetSelected访问
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam") bool bSelected = false;

	void SetSelected(bool bSel);
	bool IsSelect() { return bSelected; };

	virtual void SelectRefresh(bool bSel);

	template <typename ClassType>
	inline void BindBtnEvent(ClassType *Object, typename FBaseRadioWidget_OnClicked::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearBtnEvent();
		OnSelect_Delegate.BindUObject(Object, Func);
	}

	inline void ClearBtnEvent()
	{
		OnSelect_Delegate.Unbind();
	}
	
};
