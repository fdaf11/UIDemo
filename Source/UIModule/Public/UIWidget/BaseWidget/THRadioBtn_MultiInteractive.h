// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIWidget/BaseWidget/THNormalBtn_MultiInteractive.h"
#include "THRadioBtn_MultiInteractive.generated.h"


/**
 * 自定义组件（主组件），其可拥有次组件（鼠标按下后的进一步预览效果）; 
 */
UCLASS()
class UIMODULE_API UTHRadioBtn_MultiInteractive : public UTHNormalBtn_MultiInteractive
{
	GENERATED_BODY()
public:
};