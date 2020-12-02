// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "NormalobjButton.generated.h"

/**
 * ͨ�ð�ť��Click�¼���ʵ��ָ�����
 */
DECLARE_DELEGATE_OneParam(FNormalobjButtonOnClick, UObject*)
UCLASS()
class UIMODULE_API UNormalobjButton : public UButton
{
	GENERATED_BODY()
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;
	FReply NormalobjButtonSlateHandleClicked();
	FNormalobjButtonOnClick NormalButtonOnClickDelegate;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		int32 nID;

public:

	template<typename ClassType>
	inline void BindBtnEvent(ClassType* Object, typename FNormalobjButtonOnClick::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		ClearBtnEvent();
		NormalButtonOnClickDelegate.BindUObject(Object, Func);
	}

	inline void ClearBtnEvent()
	{
		NormalButtonOnClickDelegate.Unbind();
	}
};
