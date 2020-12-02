// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragBox.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_TwoParams(FOnClick, int32, int32)
//DECLARE_DELEGATE_FourParams(FOnClick, int32, int32, float, float)
DECLARE_DELEGATE_FourParams(FOnDropEvent, int32, int32, int32, int32)

UCLASS()
class UIMODULE_API UDragBox : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void OnWidgetRebuilt() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	FOnDropEvent OnDropDelegate;
	FOnClick OnClickDelegate;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
	int32 nID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
	int32 nType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
	bool bCanClick = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
	bool bDrag = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
	class UTexture2D* MainTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
	class UTexture2D* FrameTexture;
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomParam")
// 	FMargin MainImageMargin = FMargin(0.f,0.f,100.f,100.f);

	UPROPERTY(meta = (BindWidget, OptionalWidget), BlueprintReadWrite)
		class UImage* MainImage;
	UPROPERTY(meta = (BindWidget, OptionalWidget), BlueprintReadWrite)
		class UImage* FrameImage;
public:
	void SetMainImage(UTexture2D* Tex);
	void SetFrameImage(UTexture2D* Tex);

	template<typename ClassType>
	inline void BindBtnEvent(ClassType* Object, typename FOnClick::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		OnClickDelegate.BindUObject(Object, Func);
	}
	inline void ClearBtnEvent()
	{
		OnClickDelegate.Unbind();
	}

	template<typename ClassType>
	inline void BindBtnDropEvent(ClassType* Object, typename FOnDropEvent::TUObjectMethodDelegate<ClassType>::FMethodPtr Func)
	{
		OnDropDelegate.BindUObject(Object, Func);
	}
	inline void ClearBtnDropEvent()
	{
		OnDropDelegate.Unbind();
	}

	inline void ClearAllBtnEvent()
	{
		OnClickDelegate.Unbind();
		OnDropDelegate.Unbind();
	}
};
