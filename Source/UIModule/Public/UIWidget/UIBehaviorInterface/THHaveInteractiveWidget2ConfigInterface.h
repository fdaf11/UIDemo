#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/Button.h"
#include "THHaveButton2ConfigInterface.h"
#include "THHaveImgAndText2ConfigInterface.h"
#include "THHaveInteractiveWidget2ConfigInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHHaveInteractiveWidget2ConfigInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 作为含有THNormtalBtn的UserWidget的特性接口，主要用来绑定参数、点击等交互方法.
 * 【】TODO TEST 增加各项参数的配置，以及“绑定给按钮”
 * TODO 此接口，应该整个“按钮、图片、文字”的配置
 * By ZhanZiqi 200426
 */
class UIMODULE_API ITHHaveInteractiveWidget2ConfigInterface : public IInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

#pragma region OverrideFunction
public:
	virtual int32 GetNormalButtonID() = 0;
	virtual class UTHInteractiveWidgetBase* GetInteractiveWidget() = 0;
	virtual void InitConfigStyle_Button() = 0;
	virtual void InitConfigStyle_ImgAndText() = 0;
	virtual void RegisterOwnedInteractiveWidgetClick2SelfCallback() = 0;

	UFUNCTION() virtual void OnClicked_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnPressed_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnReleased_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnHovered_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnUnhovered_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnRadioSelected_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnNoRadioSelected_NormalBtn(int32 InID) {};
#pragma endregion OverrideFunction

public:
	void InitConfigStyle_InteractiveButton();

	// Normal
	void SetNormalButtonID(int32 InID);
	class UTextBlock* GetWidgetText();
	class UImage* GetWidgetImage();
	class UButton* GetWidgetBtn();

	// Radio
	void UpdateWidgetRadioSelected(bool InbSelections);
	bool GetWidgetbRadioSelected();
	int32 GetWidgetRadioSelectedParam();
	void SetWidgetbRadioSelected(bool bSelect);
};


