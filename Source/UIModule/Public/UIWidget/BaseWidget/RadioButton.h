// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "RadioButton.generated.h"

DECLARE_DELEGATE_OneParam(FRadioButtonOnSelected, int32)
//DECLARE_DELEGATE_TwoParams(FBtnEventHandler_nID, int32, int32)
/**
 * 通用前端Radiobutton，同一个父控件下最多只会有一个Radiobutton Selected
 */
 //觉醒加成类型
UENUM(BlueprintType)
enum class EButtonEventType : uint8
{
	Clicked,
	Selected
};

UCLASS()
class UIMODULE_API URadioButton : public UButton
{
	GENERATED_BODY()
protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnWidgetRebuilt() override;

	FReply RadioButtonSlateHandleClicked();
	FRadioButtonOnSelected RadioButtonOnClickDelegate;
	FRadioButtonOnSelected RadioButtonOnSelectedDelegate;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		int32 nID;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
// 		int32 nID_B;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		bool bSelected;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
		FSlateBrush SelectBrush;
	UPROPERTY()
		FButtonStyle SelectedStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "使用通用按钮按下音效配置"), Category = "CustomParam")
	bool bUseCommonMusic = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "自定义点击音效"), Category = "CustomParam")
	class USoundBase* ClickedSound = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category = "RadionButton|Appearance")
		void SelectStyle();
	UFUNCTION(BlueprintCallable, Category = "RadionButton|Appearance")
		void NormalStyle();
	UFUNCTION(BlueprintCallable, Category = "RadionButton|Appearance")
		virtual void SetSelected(bool bInSelected);

public:
	template<typename ClassType>
	inline void BindBtnEvent(ClassType* Object, typename FRadioButtonOnSelected::TUObjectMethodDelegate<ClassType>::FMethodPtr Func, EButtonEventType Type = EButtonEventType::Selected)
	{
		ClearBtnEvent(Type);

		switch (Type)
		{
		case EButtonEventType::Clicked:
			RadioButtonOnClickDelegate.BindUObject(Object, Func);
			break;
		case EButtonEventType::Selected:
			RadioButtonOnSelectedDelegate.BindUObject(Object, Func);
			break;
		default:
			break;
		}
	}

	inline void ClearBtnEvent(EButtonEventType Type)
	{
		switch (Type)
		{
		case EButtonEventType::Clicked:
			RadioButtonOnClickDelegate.Unbind();
			break;
		case EButtonEventType::Selected:
			RadioButtonOnSelectedDelegate.Unbind();
			break;
		default:
			break;
		}
	}
};
