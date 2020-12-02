// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonMisc/THCommon_UI.h"
//#include "CommonMisc/THCommonVariableTypes.h"
#include "Slate/WidgetTransform.h"
#include "THFunctionLibrary_UI.generated.h"

/**
 * UI公共函数	
 * By ZhanZiqi 20200323
 */
UCLASS()
class UIMODULE_API UTHFunctionLibrary_UI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region CommonFunction
public:
	// 获取当前Geometry的缩放系数; 参考: VirtualJoystick; 可适用于编辑器UMG设计窗口.
	static float GetDPIScaleFactor(const FGeometry& InGeometry);	// 【】TODO 后续可能使用UWidgetLayoutLibrary::GetViewportScale替代？

	/**
	 * UI坐标转换; 
	 * @param Position - 输入位置, 可为小数（百分比位置）/>1（即未经过DPI缩放的LocalPos）
	 * @param RelativeTo - 相对位置（通常为Geometry.X OR .Y值）
	 * @param ScaleFactor - 缩放率GetDPIScaleFactor; 也可通过GetViewportScaleFactor获取
	 */
	static int32 ResolveUIRelativePosition(float Position, float RelativeTo, float ScaleFactor);
	UFUNCTION(BlueprintPure, Category = "--CommonFunc--|--UI--") static FVector2D ResolveUIRelativePosition_Vec2D(FVector2D Position, FVector2D RelativeTo, float ScaleFactor);

	// 通过Geometry.DrawScale获取当前缩放率
	UFUNCTION(BlueprintPure, Category = "--CommonFunc--|--UI--") static float GetScaleFactor(const FGeometry& Geometry);

	/** 【】TODO 用于缓存时，需注意窗口大小变化*/
	UFUNCTION(BlueprintCallable, Category = "--CommonFunc--|--UI--", meta = (WorldContext = "WorldContextObject"))
	static FVector2D GetScreenLocalSize(class UObject* WorldContextObject);

	//static class UTHDragDropOperation* GetDragDropOp(class UObject* WorldContextObject);
#pragma endregion CommonFunction

#pragma region OperatorWidget
public:
	static const FString GetOperatorWidgetTypeEnumString(EOperatorWidgetType IneType) { return StrEnumOperatorWidgetType[(int32)IneType]; }
#pragma endregion OperatorWidget

#pragma region CanvasSlot
public:
	UFUNCTION(BlueprintPure) static bool GetCanvasPanelSlotPosition(class UWidget* InWG, FVector2D& InVec2_Pos);
	UFUNCTION(BlueprintCallable) static bool SetCanvasPanelSlotPosition(class UWidget* InWG, const FVector2D& InVec2_Pos);
	UFUNCTION(BlueprintPure) static bool GetCanvasPanelSlotSize(class UWidget* InWG, FVector2D& InVec2_Size);
	UFUNCTION(BlueprintCallable) static bool SetCanvasPanelSlotSize(class UWidget* InWG, const FVector2D& InVec2_Size);
	UFUNCTION(BlueprintPure) static bool GetCanvasPanelSlotPositionAndSize(class UWidget* InWG, FVector2D& InVec2_Pos, FVector2D& InVec2_Size);
	UFUNCTION(BlueprintCallable) static bool SetCanvasPanelSlotPositionAndSize(class UWidget* InWG, const FVector2D& InVec2_Pos, const FVector2D& InVec2_Size);
	UFUNCTION(BlueprintPure) static bool GetCanvasPanelSlotAnchorMinimum(class UWidget* InWG, FVector2D& InVec2_AnchorMinimum);
	UFUNCTION(BlueprintCallable) static bool SetWidgetAnchorNum(class UWidget* InWG, const FVector2D& InVec2_AnchorMinimum);

	// 【】TODO 现4.24蓝图中有类似函数，可改成那个.
	static FVector2D Trans2ZeroNumAnchorPos(const FVector2D& InVec2_AnchorPos, const FVector2D& InVec2_ParentSize, const FVector2D& InVec2_AnchorMinimum);
#pragma endregion CanvasSlot

#pragma region GradientEffect
public:
	/** 渐变效果（每秒一定速率降低）（总进度满值的百分比/秒 进行消退）;
	 * @param InfTemp - 渐变Progress当前值
	 * @param InfCurrent - Progress当前值
	 * @param InfProgressMax - 总进度满值
	 * @param InfTransitionalPctPerSeconds - 每秒消退百分比(InfProgressMax * InfTransitionalPctPerSeconds)
	 * @param InfDelayTime - 延迟X秒后开始消退
	*/
	static void GradinetEffect_PerSecondsFadeOut(const float InfDeltaTime, float& InfTemp, const float InfCurrent, const float InfProgressMax, const float InfTransitionalPctPerSeconds);
	static void GradinetEffect_PerSecondsFadeOut(const float InfDeltaTime, float& InfTemp, const float InfCurrent, const float InfProgressMax, const float InfTransitionalPctPerSeconds, float& InfDelayTime);
#pragma endregion GradientEffect

#pragma region SlateBrush
public:
	static class UMaterialInstanceDynamic* GetDynamicMaterial(class UObject* WorldContextObject, FSlateBrush& InBrush);
	static class UMaterialInterface* GetMaterialFromImage(class UImage* InIMG);

	// 从Image当中获取Brush(目前仅使用Material的情况); InArrHudDrawInfo, InNum - 两者配合用于创建多个Brush返回回去; 
	static bool GetHudDrawInfoFromImage(class UObject* WorldContextObject, class UImage* InIMG, FHudDrawInfo& InHudDrawInfo);
	static bool GetHudDrawInfoFromImage(class UObject* WorldContextObject, class UImage* InIMG, TArray<FHudDrawInfo>& InArrHudDrawInfo, int32 InNum = 1);

#pragma endregion SlateBrush

#pragma region DistanceScaledUI
public:
	// 减少一次计算UI缩放系数
	static bool GetTargetFromRelativeLocDistanceScaleFactor(const FVector2D& InVec2_ScreenSize, FVector InTargetLocation, FVector InRelativeLocation, float& InfDistanceSqr, float& InfDistanceFactor, const bool InbUnLimitDistance = false, const int32 InDistanceCfgRange = 60);

	/** 获取目标距离相对位置（eg. 常用：当前控制角色位置）的距离缩放系数;
	  * @param InVec2ScreenHudSize - 从GetViewportSize获取
	  * @param InDistanceCfgRange - 限制范围，目标超过此距离返回false, 若要无限制范围，勾选InbIsNoLimitDistance;
	  * @param InbIsNoLimitDistance - true = 无限制距离，勾选后InDistanceCfgRange需使用默认值
	  * @param InfDistanceFactor - 回调距离系数，= 1 - 实际距离 / 设定范围距离; 范围超过设定范围返回负数，越远数字越大; 范围在设定范围内, 返回0~1，越近越靠近1
	  * @param InfUIScaleFactor - 回调给UI的缩放系数，超过一定距离后，设置最小值InfUIScaleFactorClampMin，防止过远后UI过小; 目前 0.4 ~ 1
	  * @return 是否在划定半径范围内. */
	UFUNCTION(BlueprintCallable, Category = "--CommonFunc--|--UI--")
	static bool GetTargetFromRelativeLocDistanceScaleFactor(const FVector2D& InVec2ScreenViewportSize, FVector InTargetLocation, FVector InRelativeLocation, float& InfDistanceSqr, float& InfDistanceFactor, float& InfUIScaleFactor, const bool InbUnLimitDistance = false, const int32 InDistanceCfgRange = 60, float InfUIScaleFactorClampMin = 0.4f);
#pragma endregion DistanceScaledUI

public:
	// 逆时针负数角度  顺时针+
	UFUNCTION(BlueprintPure) static float GetAngleFromTwoVector2D(FVector2D InGoalDir, FVector2D InOriginPivot);

	/*
	#pragma region MovingInterp
	public:
		UFUNCTION(BlueprintCallable, Category = "--CommonFunc--|2DInterp")
		static void 2DInterpToGoalLocation(FWidgetTransform CurrTransform, FWidgetTransform GoalTransform, float DeltaTime, float InterpSpeed, FWidgetTransform& OutTransform, bool& OutArrived);
	#pragma endregion MovingInterp*/

};
