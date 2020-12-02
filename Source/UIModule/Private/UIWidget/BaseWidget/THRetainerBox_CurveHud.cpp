#include "UIWidget/BaseWidget/THRetainerBox_CurveHud.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Slate/SRetainerWidget.h"

void UTHRetainerBox_CurveHud::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	UpdateCurveHudValue();

#if WITH_EDITOR
	if (bRealTimeRendering)
		RequestRender();
#endif
}

void UTHRetainerBox_CurveHud::UpdateCurveHudValue()
{
	UMaterialInstanceDynamic* tMatIns = GetEffectMaterial();
	if (!tMatIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHRetainerBox_CurveHud::PostEditChangeProperty, !tMatIns"));
		return;
	}

	tMatIns->SetScalarParameterValue(FName("DistortionAmount"), fCurveFloat);
}

TSharedRef<SWidget> UTHRetainerBox_CurveHud::RebuildWidget()
{
	MyRetainerWidget =
		SNew(SRetainerWidget)
		.RenderOnInvalidation(RenderOnInvalidation)
		.RenderOnPhase(RenderOnPhase)
		.Phase(Phase)
		.PhaseCount(PhaseCount)
#if STATS
		.StatId(FName(*FString::Printf(TEXT("%s [%s]"), *GetFName().ToString(), *GetClass()->GetName())))
#endif//STATS
		;

#if WITH_EDITOR
	if (!IsDesignTime())
		bRealTimeRendering = false;

	MyRetainerWidget->SetRetainedRendering(bRealTimeRendering);
	if (!bRealTimeRendering)
		MyRetainerWidget->SetRetainedRendering(IsDesignTime() ? false : true);
#else
	MyRetainerWidget->SetRetainedRendering(IsDesignTime() ? false : true);
#endif

	if (GetChildrenCount() > 0)
	{
		MyRetainerWidget->SetContent(GetContentSlot()->Content ? GetContentSlot()->Content->TakeWidget() : SNullWidget::NullWidget);
	}

	return MyRetainerWidget.ToSharedRef();
}

#if WITH_EDITOR
void UTHRetainerBox_CurveHud::UpdatePresetConfig()
{
	if (bUsePresetConfig)
	{
		UMaterialInstance* mat_CurveHudFx_Ins = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), NULL, TEXT("MaterialInstanceConstant'/Game/MaterialLibrary/Effect_UI/CurvedHUD_Helmet_Inst.CurvedHUD_Helmet_Inst'"), NULL, LOAD_None, NULL));
		SetEffectMaterial(mat_CurveHudFx_Ins);
		SetTextureParameter(FName("SlateUI"));
	}
}

void UTHRetainerBox_CurveHud::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdatePresetConfig();
	UpdateCurveHudValue();
}

#endif
