#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Styling/SlateTypes.h"
#include "THHaveButton2ConfigInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHHaveButton2ConfigInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Widget拥有按钮，并对按钮各项表现进行配置的接口
 */
class UIMODULE_API ITHHaveButton2ConfigInterface
{
	GENERATED_BODY()

public:
	// Need Override
	virtual class UButton* GetWidgetBtn() = 0;
	virtual void InitConfigStyle_Button() = 0;

	// No Need Override
	virtual void SetWidgetButtonStyleFromTexture(class UTexture2D* InTex_Item);
	virtual void SetWidgetButtonStyle(const FButtonStyle& InBtnStyle);
	virtual void SetWidgetButtonVisibility(const ESlateVisibility& IneVisibility);
	virtual void SetWidgetButtonBackgroundColor(const FLinearColor& InColor);

};
