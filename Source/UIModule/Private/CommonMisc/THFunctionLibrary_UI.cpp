// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonMisc/THFunctionLibrary_UI.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Widget.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Styling/SlateBrush.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetMathLibrary.h"


// 【】TODO TEST【6】
#pragma optimize("",off)

#pragma region CanvasSlot
bool UTHFunctionLibrary_UI::GetCanvasPanelSlotPosition(UWidget* InWG, FVector2D& InVec2_Pos)
{
	if (!InWG || !InWG->Slot)
		return false;

	UCanvasPanelSlot* tCanvasSlot = Cast<UCanvasPanelSlot>(InWG->Slot);
	if (!tCanvasSlot)
		return false;

	InVec2_Pos = tCanvasSlot->GetPosition();
	return true;
}

bool UTHFunctionLibrary_UI::SetCanvasPanelSlotPosition(UWidget* InWG, const FVector2D& InVec2_Pos)
{
	if (!InWG || !InWG->Slot)
		return false;

	UCanvasPanelSlot* tCanvasSlot = Cast<UCanvasPanelSlot>(InWG->Slot);
	if (!tCanvasSlot)
		return false;

	tCanvasSlot->SetPosition(InVec2_Pos);
	return true;
}

bool UTHFunctionLibrary_UI::GetCanvasPanelSlotSize(UWidget* InWG, FVector2D& InVec2_Size)
{
	if (!InWG || !InWG->Slot)
		return false;

	UCanvasPanelSlot* tCanvasSlot = Cast<UCanvasPanelSlot>(InWG->Slot);
	if (!tCanvasSlot)
		return false;

	InVec2_Size = tCanvasSlot->GetSize();
	return true;
}

bool UTHFunctionLibrary_UI::SetCanvasPanelSlotSize(UWidget* InWG, const FVector2D& InVec2_Size)
{
	if (!InWG || !InWG->Slot)
		return false;

	UCanvasPanelSlot* tCanvasSlot = Cast<UCanvasPanelSlot>(InWG->Slot);
	if (!tCanvasSlot)
		return false;

	tCanvasSlot->SetSize(InVec2_Size);
	return true;
}

bool UTHFunctionLibrary_UI::GetCanvasPanelSlotPositionAndSize(UWidget* InWG, FVector2D& InVec2_Pos, FVector2D& InVec2_Size)
{
	if (!InWG || !InWG->Slot)
		return false;

	UCanvasPanelSlot* tCanvasSlot = Cast<UCanvasPanelSlot>(InWG->Slot);
	if (!tCanvasSlot)
		return false;

	InVec2_Size = tCanvasSlot->GetSize();
	InVec2_Pos = tCanvasSlot->GetPosition();
	return true;
}

bool UTHFunctionLibrary_UI::SetCanvasPanelSlotPositionAndSize(UWidget* InWG, const FVector2D& InVec2_Pos, const FVector2D& InVec2_Size)
{
	if (!InWG || !InWG->Slot)
		return false;

	UCanvasPanelSlot* tCanvasSlot = Cast<UCanvasPanelSlot>(InWG->Slot);
	if (!tCanvasSlot)
		return false;

	tCanvasSlot->SetSize(InVec2_Size);
	tCanvasSlot->SetPosition(InVec2_Pos);
	return true;
}

bool UTHFunctionLibrary_UI::GetCanvasPanelSlotAnchorMinimum(class UWidget* InWidget, FVector2D& InVec2_AnchorMinimum)
{
	if (!InWidget)
		return false;

	UCanvasPanelSlot* tSlot = Cast<UCanvasPanelSlot>(InWidget->Slot);
	if (!tSlot)
		return false;

	InVec2_AnchorMinimum = tSlot->LayoutData.Anchors.Minimum;
	return true;
}

bool UTHFunctionLibrary_UI::SetWidgetAnchorNum(class UWidget* InWG, const FVector2D& InVec2_AnchorNum)
{
	if (!InWG)
		return false;

	UCanvasPanelSlot* tSlot = Cast<UCanvasPanelSlot>(InWG->Slot);
	if (!tSlot)
		return false;

	FAnchors tAnchors = tSlot->GetAnchors();
	tAnchors.Minimum = InVec2_AnchorNum;
	tAnchors.Maximum = InVec2_AnchorNum;
	tSlot->SetAnchors(tAnchors);				// 此时设置后，无效果，故设置完AnchorNum后，还需要自行设置AnchorPos; 需窗口边界长度变化后，方调用LayoutData.Anchors进行刷新.
	return true;
}

// 未拉伸锚点坐标变化
FVector2D UTHFunctionLibrary_UI::Trans2ZeroNumAnchorPos(const FVector2D& InVec2_AnchorPos, const FVector2D& InVec2_ParentSize, const FVector2D& InVec2_AnchorMinimum)
{
	// 锚点为0.5, 0时的处理; 参考TH当中SaveLayout RebaseLayout处理；Layout::BPCallTrans2NoAnchor
	// 150, 150     0.5, 0   - 51, -168
	// - 51 + 150 * 0.5 = 24
	return InVec2_AnchorPos + InVec2_ParentSize * InVec2_AnchorMinimum;
}

#pragma endregion CanvasSlot

#pragma region CommonFunciton

float UTHFunctionLibrary_UI::GetDPIScaleFactor(const FGeometry& InGeometry)
{
	if (InGeometry.Scale == 0.f)		// 【】TODO 修改成Nearly
		return 0.f;

	const float tfDesiredWidth = 1024.0f;
	const float tfUndoDPIScaling = 1.0f / InGeometry.Scale;
	return (InGeometry.GetDrawSize().GetMax() / tfDesiredWidth) * tfUndoDPIScaling;
}

int32 UTHFunctionLibrary_UI::ResolveUIRelativePosition(float Position, float RelativeTo, float ScaleFactor)
{
	// absolute from edge
	if (Position < -1.0f)
	{
		return RelativeTo + Position * ScaleFactor;
	}
	// relative from edge
	else if (Position < 0.0f)
	{
		return RelativeTo + Position * RelativeTo;
	}
	// relative from 0
	else if (Position <= 1.0f)
	{
		return Position * RelativeTo;
	}
	// absolute from 0
	else
	{
		return Position * ScaleFactor;
	}
}

FVector2D UTHFunctionLibrary_UI::ResolveUIRelativePosition_Vec2D(FVector2D Position, FVector2D RelativeTo, float ScaleFactor)
{
	return FVector2D(UTHFunctionLibrary_UI::ResolveUIRelativePosition(Position.X, RelativeTo.X, ScaleFactor), 
		UTHFunctionLibrary_UI::ResolveUIRelativePosition(Position.Y, RelativeTo.Y, ScaleFactor));
}

float UTHFunctionLibrary_UI::GetScaleFactor(const FGeometry& Geometry)
{
	const float DesiredWidth = 1024.0f;

	float UndoDPIScaling = 1.0f / Geometry.Scale;
	return (Geometry.GetDrawSize().GetMax() / DesiredWidth) * UndoDPIScaling;
}

//FVector2D UTHFunctionLibrary_UI::GetLayoutLocalSize(class ATHPlayerController* InPC)
//{
//	if (!InPC || !InPC->UIController)
//		return FVector2D::ZeroVector;
//
//	return InPC->UIController->GetOperatorLayoutLocalSize();
//}

#pragma endregion CommonFunciton

#pragma region GradientEffect

void UTHFunctionLibrary_UI::GradinetEffect_PerSecondsFadeOut(const float InfDeltaTime, float& InfTemp, const float InfCurrent, const float InfProgressMax, const float InfTransitionalPctPerSeconds, float& InfDelayTime)
{
	if (InfDelayTime > 0.f)
	{
		InfDelayTime -= InfDeltaTime;
	}
	else
	{
		UTHFunctionLibrary_UI::GradinetEffect_PerSecondsFadeOut(InfDeltaTime, InfTemp, InfCurrent, InfProgressMax, InfTransitionalPctPerSeconds);
	}
}

void UTHFunctionLibrary_UI::GradinetEffect_PerSecondsFadeOut(const float InfDeltaTime, float& InfTemp, const float InfCurrent, const float InfProgressMax, const float InfTransitionalPctPerSeconds)
{
	if (InfTemp > InfCurrent)
	{
		InfTemp -= InfProgressMax * InfTransitionalPctPerSeconds * InfDeltaTime;
		InfTemp = FMath::Max(InfTemp, InfCurrent);
	}
}

#pragma endregion GradientEffect

#pragma region SlateBrush
UMaterialInstanceDynamic* UTHFunctionLibrary_UI::GetDynamicMaterial(class UObject* WorldContextObject, FSlateBrush& InBrush)
{
	UMaterialInterface* tMaterial = NULL;
	UObject* tResource = InBrush.GetResourceObject();
	tMaterial = Cast<UMaterialInterface>(tResource);
	if (tMaterial)
	{
		UMaterialInstanceDynamic* tDynamicMaterial = Cast<UMaterialInstanceDynamic>(tMaterial);
		if (!tDynamicMaterial)
		{
			tDynamicMaterial = UMaterialInstanceDynamic::Create(tMaterial, WorldContextObject);
			InBrush.SetResourceObject(tDynamicMaterial);
		}

		return tDynamicMaterial;
	}

	return NULL;
}

class UMaterialInterface* UTHFunctionLibrary_UI::GetMaterialFromImage(class UImage* InImg)
{
	if (!InImg)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHFunctionLibrary_UI::GetMaterialFromImage, !InImg"));
		return nullptr;
	}

	UMaterialInterface* tMat = Cast<UMaterialInterface>(InImg->Brush.GetResourceObject());
	if (tMat && tMat->IsA(UMaterialInstanceDynamic::StaticClass()))
	{
		UMaterialInstanceDynamic* tOriginMatInsDy = Cast<UMaterialInstanceDynamic>(tMat);
		tMat = tOriginMatInsDy->Parent;
	}

	return tMat;
}

bool UTHFunctionLibrary_UI::GetHudDrawInfoFromImage(class UObject* WorldContextObject, class UImage* InIMG, TArray<FHudDrawInfo>& InArrHudDrawInfo, int32 InNum /*= 1*/)
{
	if (!WorldContextObject || !InIMG)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHFunctionLibrary_UI::GetHudDrawInfoFromImage, !WorldContextObject || !InIMG"));
		return false;
	}

	FVector2D tVec2PlayerIconSize;
	UTHFunctionLibrary_UI::GetCanvasPanelSlotSize(InIMG, tVec2PlayerIconSize);
	UMaterialInterface* tMat = UTHFunctionLibrary_UI::GetMaterialFromImage(InIMG);
	if (!tMat)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHFunctionLibrary_UI::GetHudDrawInfoFromImage, !GetMaterialFromImage"));
		return false;
	}

	FHudDrawInfo tItemInfo;
	for (int32 i = 0; i < InNum; i++)
	{
		FSlateBrush tBrush;
		UMaterialInstanceDynamic* tMatInsDy = UMaterialInstanceDynamic::Create(tMat, NULL, MakeUniqueObjectName(WorldContextObject, UMaterialInstanceDynamic::StaticClass()));
		if (tMatInsDy)
		{
			tBrush.SetResourceObject(tMatInsDy);
			tItemInfo.Brush = tBrush;
			tItemInfo.DrawSize = tVec2PlayerIconSize;
			InArrHudDrawInfo.Emplace(tItemInfo);
		}
	}
	return true;
}

bool UTHFunctionLibrary_UI::GetHudDrawInfoFromImage(class UObject* WorldContextObject, class UImage* InIMG, FHudDrawInfo& InHudDrawInfo)
{
	if (!WorldContextObject || !InIMG)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHFunctionLibrary_UI::GetHudDrawInfoFromImage, !WorldContextObject || !InIMG"));
		return false;
	}

	FVector2D tVec2PlayerIconSize;
	UTHFunctionLibrary_UI::GetCanvasPanelSlotSize(InIMG, tVec2PlayerIconSize);
	UMaterialInterface* tMat = UTHFunctionLibrary_UI::GetMaterialFromImage(InIMG);
	if (!tMat)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHFunctionLibrary_UI::GetHudDrawInfoFromImage, !GetMaterialFromImage"));
		return false;
	}

	FHudDrawInfo tItemInfo;
	FSlateBrush tBrush;
	UMaterialInstanceDynamic* tMatInsDy = UMaterialInstanceDynamic::Create(tMat, NULL, MakeUniqueObjectName(WorldContextObject, UMaterialInstanceDynamic::StaticClass()));
	if (tMatInsDy)
	{
		tBrush.SetResourceObject(tMatInsDy);
		tItemInfo.Brush = tBrush;
		tItemInfo.DrawSize = tVec2PlayerIconSize;
		InHudDrawInfo = tItemInfo;
	}
	return true;
}

FVector2D UTHFunctionLibrary_UI::GetScreenLocalSize(class UObject* WorldContextObject)
{
	return UWidgetLayoutLibrary::GetViewportSize(WorldContextObject) / UWidgetLayoutLibrary::GetViewportScale(WorldContextObject);
}

bool UTHFunctionLibrary_UI::GetTargetFromRelativeLocDistanceScaleFactor(const FVector2D& InVec2_ScreenSize, FVector InTargetLocation, FVector InRelativeLocation, float& InfDistanceSqr, float& InfDistanceFactor, const bool InbUnLimitDistance /*= false*/, const int32 InDistanceCfgRange /*= 60*/)
{
	if (InDistanceCfgRange == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHFunctionLibrary_UI::GetTargetFromCameraDistanceScaleFactor, InDistanceCfgRange == 0"));
		return false;
	}

	//若目标中心点于半空中，且高于角色水平面（eg. 比角色高的AI，含BOSS等）, 将Z坐标与相对位置持平; 准确测算距离，防止高度差问题
	InTargetLocation.Z = InRelativeLocation.Z; 
	InfDistanceSqr = FVector::DistSquared(InRelativeLocation, InTargetLocation);
	InfDistanceFactor = 1.f - InfDistanceSqr / FMath::Square(InDistanceCfgRange * 100);	//  DistFactor = 1 - 实际距离 / 配置范围距离
	if (!InbUnLimitDistance && InfDistanceFactor < 0.f)
		return false;

	return true;
}

bool UTHFunctionLibrary_UI::GetTargetFromRelativeLocDistanceScaleFactor(const FVector2D& InVec2ScreenViewportSize, FVector InTargetLocation, FVector InRelativeLocation, float& InfDistanceSqr, float& InfDistanceFactor, float& InfUIScaleFactor, const bool InbUnLimitDistance /*= false*/, const int32 InDistanceCfgRange /*= 60*/, float InfUIScaleFactorClampMin /*= 0.4f*/)
{
	const bool tbResult = UTHFunctionLibrary_UI::GetTargetFromRelativeLocDistanceScaleFactor(InVec2ScreenViewportSize, InTargetLocation, InRelativeLocation, InfDistanceSqr, InfDistanceFactor, InbUnLimitDistance, InDistanceCfgRange);

	// 防止极远距离UI缩放过小
	if (tbResult)
	{
		InfUIScaleFactor = FMath::Max<float>(InfUIScaleFactorClampMin,
			InVec2ScreenViewportSize.Y * FMath::Max<float>(InfDistanceFactor, 0.f) * 0.000926f);		// 1080 * 0.000926f = 1; 输入ViewportSize缘由：窗口缩小后，图标相应缩小
	}

	return tbResult;
}

//
//void UTHFunctionLibrary_UI::2DInterpToGoalLocation(FWidgetTransform CurrTransform, FWidgetTransform GoalTransform, float DeltaTime, float InterpSpeed, FWidgetTransform& OutTransform, bool& OutArrived)
//{
//	const FVector2D& tVec2GoalTranslation = GoalTransform.Translation;
//	const FVector2D& tVec2GoalScale = GoalTransform.Scale;
//	const float& tfGoalAngle = GoalTransform.Angle;
//
//	const float tfGoalTranslationLength = tVec2GoalTranslation.SizeSquared();
//	const float tfGoalScaleLength = tVec2GoalScale.SizeSquared();
//
//	const FVector2D tVec2ResTranslation = UKismetMathLibrary::Vector2DInterpTo(CurrTransform.Translation, tVec2GoalTranslation, DeltaTime, InterpSpeed);
//	const FVector2D tVec2ResScale = UKismetMathLibrary::Vector2DInterpTo(CurrTransform.Scale, tVec2GoalScale, DeltaTime, InterpSpeed);
//	const float tfResAngle = UKismetMathLibrary::FInterpTo(CurrTransform.Angle, tfGoalAngle, DeltaTime, InterpSpeed);
//
//
//	FVector2D tfResTranslation = FMath::IsNearlyEqual(tVec2GoalTranslation.SizeSquared(), tfGoalAngle, 0.01f) ? tVec2GoalTranslation : tVec2ResTranslation.SizeSquared();
//	FVector2D tfResScale = FMath::IsNearlyEqual(tVec2GoalScale.SizeSquared(), tfGoalAngle, 0.01f) ? tVec2GoalTranslation.SizeSquared() : tVec2ResScale.SizeSquared();
//	float tfResAngle = FMath::IsNearlyEqual(tfResAngle, tfGoalAngle, 0.01f) ? tfResAngle : tfGoalAngle;
//}

#pragma endregion SlateBrush

float UTHFunctionLibrary_UI::GetAngleFromTwoVector2D(FVector2D InGoalDir, FVector2D InOriginPivot)
{
	UKismetMathLibrary::Normalize2D(InGoalDir);
	float tAngle = UKismetMathLibrary::DegAcos(FVector2D::DotProduct(InOriginPivot, InGoalDir));	// 向量夹角
	int8 tnNegativeVal = FVector2D::CrossProduct(InOriginPivot, InGoalDir) < 0 ? -1 : 1;			// 正负角度
	return tAngle * tnNegativeVal;
}


#pragma optimize("",on)
