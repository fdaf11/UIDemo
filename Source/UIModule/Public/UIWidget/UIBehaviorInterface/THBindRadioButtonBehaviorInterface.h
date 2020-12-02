#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Styling/SlateTypes.h"
#include "THBindRadioButtonBehaviorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHBindRadioButtonBehaviorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Widget拥有按钮，并对按钮各项表现进行配置的接口
 */
class UIMODULE_API ITHBindRadioButtonBehaviorInterface
{
	GENERATED_BODY()

#pragma region FunctionDelegateAddDynamic
public:
#define MACRO_AddOwnedRadioBtnDynamic( TheButton, TheUIBehavior, UserObject, FuncName ) \
if (!TheButton)	\
{	\
	UE_LOG(LogTemp, Warning, TEXT("ITHBindRadioButtonBehaviorInterface::MACRO_AddOwnedRadioBtnDynamic, TheButton == nullptr"));	\
	return;	\
}	\
TheButton->MACRO_AddUIRadioSelectedDynamic(TheUIBehavior, UserObject, FuncName); \

#pragma endregion FunctionDelegateAddDynamic

};