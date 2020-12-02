#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "THUIClickInterface_OneParam.h"
#include "UIWidget/BaseWidget/THNormalBtn_ImgText.h"
#include "THHaveNormalButtonImgText2ConfigInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHHaveNormalButtonImgText2ConfigInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 拥有NormalButtonImgText_UserWidget的外在组件的配置; 提供被绑定的函数接口
 * PS1: AddDynamic无法加入Interface，故需子类重写RegisterOwnedNormalBtnClick2SelfCallback进行绑定
 * 绑定使用eg.: THNorBtn->MACRO_AddUIBehaviorDynamic(UIBehavior, this, &::UIBehavior_Test);
 */
class UIMODULE_API ITHHaveNormalButtonImgText2ConfigInterface : public IInterface
{
	GENERATED_BODY()

#pragma region OverrideFunction
public:
	virtual int32 GetNormalButtonID() = 0;
	virtual class UTHNormalBtn_ImgText* GetNormalButton_UserWidget() = 0;
	virtual void InitConfigStyle_Button() = 0;
	virtual void InitConfigStyle_ImgAndText() = 0;
	virtual void RegisterOwnedNormalBtnClick2SelfCallback() = 0;

	UFUNCTION() virtual void OnClicked_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnPressed_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnReleased_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnHovered_NormalBtn(int32 InID) {};
	UFUNCTION() virtual void OnUnhovered_NormalBtn(int32 InID) {};
#pragma endregion OverrideFunction

public:
	void SetNormalButtonID(int32 InID);
	class UTextBlock* GetWidgetText();
	class UImage* GetWidgetImage();
	class UButton* GetWidgetBtn();
	void InitConfigStyle_NormalButton_ImgText();
};