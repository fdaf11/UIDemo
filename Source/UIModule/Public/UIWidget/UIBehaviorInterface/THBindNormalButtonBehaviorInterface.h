#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Styling/SlateTypes.h"
#include "THBindNormalButtonBehaviorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTHBindNormalButtonBehaviorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Widget拥有按钮，并对按钮各项表现进行配置的接口
 */
class UIMODULE_API ITHBindNormalButtonBehaviorInterface
{
	GENERATED_BODY()

#pragma region FunctionDelegateAddDynamic
public:
#define MACRO_AddOwnedBtnDynamic( TheButton, TheUIBehavior, UserObject, FuncName ) \
if (!TheButton)	\
{	\
	UE_LOG(LogTemp, Warning, TEXT("ITHBindNormalButtonBehavior::MACRO_AddOwnedBtnDynamic, TheButton == nullptr"));	\
	return;	\
}	\
TheButton->MACRO_AddUIBehaviorDynamic(TheUIBehavior, UserObject, FuncName); \

#pragma endregion FunctionDelegateAddDynamic

};