// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WebBrowserWidget/Public/WebBrowser.h"
#include "THWebBrowser.generated.h"

/**
 * WebBrowser重写（可调用输入法/小键盘）
 */
UCLASS()
class UIMODULE_API UTHWebBrowser : public UWebBrowser
{
	GENERATED_BODY()
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

};
