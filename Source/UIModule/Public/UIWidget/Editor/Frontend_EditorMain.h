// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Frontend_EditorMain.generated.h"

/**
 * 
 */
UCLASS()
class UIMODULE_API UFrontend_EditorMain : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	//UFUNCTION(BlueprintCallable) void ShowWidget(TSubclassOf<class UUserWidget> inUserWidgetClasss);
public:
	//根窗口画布
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite) class UCanvasPanel* Main_CanvasPanel;
};
