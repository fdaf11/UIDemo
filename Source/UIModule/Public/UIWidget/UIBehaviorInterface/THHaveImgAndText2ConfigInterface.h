#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Styling/SlateBrush.h"
#include "Fonts/SlateFontInfo.h"
#include "THHaveImgAndText2ConfigInterface.generated.h"


//DECLARE_DELEGATE_OneParam(FBaseRadioWidget_OnClicked, int32)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHHaveImgAndText2ConfigInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * NormalButton_ImgText_UserWidget 绑定接口; 目前同时用于单选同类型按钮接口
 */
class UIMODULE_API ITHHaveImgAndText2ConfigInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Need Override
	virtual class UTextBlock* GetWidgetText() = 0;
	virtual class UImage* GetWidgetImage() = 0;
	virtual void InitConfigStyle_ImgAndText() = 0;

	// No Need Override
	virtual void SetWidgetText(FString InData);
	virtual void SetWidgetTextColorAndOpacity(const FSlateColor& InColor);
	virtual void SetWidgetTextFont(const FSlateFontInfo& InFont);
	virtual void SetWidgetTextSize(const int32& InSize);
	virtual void SetWidgetTextVisiblity(const ESlateVisibility& IneVisible);

	virtual void SetWidgetImgBrushFromTexture(class UTexture2D* Intex2_Icon, bool InbMatchSize = false);
	virtual void SetWidgetImgBrush(const FSlateBrush& InBrush);
	virtual void SetWidgetImgBrushTintColor(const FSlateColor& TintColor);
	virtual void SetWidgetImgVisiblity(const ESlateVisibility& IneVisible);
};
