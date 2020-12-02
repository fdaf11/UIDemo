#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "THClearAnyOtherRadioSelectionsBesidesSpecify.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHClearAnyOtherRadioSelectionsBesidesSpecify : public UInterface
{
	GENERATED_BODY()
};

/**
 * 单选清除接口, 用于清除一个层级下的所有组件的单选状态（除指定组件外_ID作为辨识）
 */
class UIMODULE_API ITHClearAnyOtherRadioSelectionsBesidesSpecify
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	void ClearAnyOtherRadioSelectionsBesidesSpecify(class UPanelWidget* ParentCanvas, int32 nSpecifiedID);
};
