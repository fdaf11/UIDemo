#include "UIWidget/BaseWidget/THRetainerBox.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"

void UTHRetainerBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	//if (bUsePresetConfig)
	//{
	//	ConstructorHelpers::FObjectFinder<UMaterialInstance> tFatalBlood_FullScreenMatRes(TEXT("MaterialInstanceConstant'/Game/UIResource/res/InGame/Common/CurvedHUD_FX_Inst.CurvedHUD_FX_Inst'"));
	//	UMaterialInstance* mat_FatalInjuryScreenEffect = tFatalBlood_FullScreenMatRes.Object;
	//	SetEffectMaterial(mat_FatalInjuryScreenEffect);
	//}
}
