// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "UIWidget/Joystick/STHJoystick.h"
#include "THJoystick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FJoystickOnTouchMove, EJoystickHandleTouchType, HandleTouchType, int32, ControlIndex, const FVector2D&, LocalCoord, const FVector2D&, ScreenSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FJoystickOnTouchStart, EJoystickHandleTouchType, HandleTouchType, int32, ControlIndex, const FVector2D&, LocalCoord, const FVector2D&, ScreenSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FJoystickOnTouchEnd, EJoystickHandleTouchType, HandleTouchType, int32, ControlIndex, const FVector2D&, LocalCoord, const FVector2D&, ScreenSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FJoystickThumbTick, float, xAxis, float, yAxis, bool, InbIsTouchEndedTick);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FJoystickInitPropertyUpdate);

// 【】TODO 这两个结构体挪到Common当中
USTRUCT(BlueprintType)
struct FControlConfig
{
	GENERATED_USTRUCT_BODY()

	/** The actual center of the control */
	UPROPERTY(EditAnywhere)
	FVector2D Center = FVector2D(0.18f, 0.73f);
	/** 背景大小,使用0~1百分比设置; The size of a joystick that can be re-centered within InteractionSize area*/
	UPROPERTY(EditAnywhere)
	FVector2D VisualSize = FVector2D(155.f, 155.f);
	/** 滑竿大小,使用0~1百分比设置; The size of the thumb that can be re-centered within InteractionSize area */
	UPROPERTY(EditAnywhere)
	FVector2D ThumbSize = FVector2D(68.f, 68.f);
	/** The size of a the interactable area around Center */
	UPROPERTY(EditAnywhere)
	FVector2D InteractionSize = FVector2D(155.f, 155.f);
	/** The scale for control input */
	UPROPERTY(EditAnywhere)
	FVector2D InputScale = FVector2D(1.f, 1.f);
};

// GlobalParameters
USTRUCT(BlueprintType)
struct FJoystick_GlobalParameters
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) float ActiveOpacity = 1.f;
	UPROPERTY(EditAnywhere) float InactiveOpacity = 0.2f;
	UPROPERTY(EditAnywhere) float TimeUntilDeactive = 0.5f;
	UPROPERTY(EditAnywhere) float TimeUntilReset = 2.0f;
	UPROPERTY(EditAnywhere) float ActivationDelay = 0;
	UPROPERTY(EditAnywhere) bool PreventRecenter = true;
	UPROPERTY(EditAnywhere) float StartupDelay = 0;
};


/**
 * 
 */
UCLASS()
class UIMODULE_API UTHJoystick : public UWidget
{
	GENERATED_BODY()

public:
	UTHJoystick();
	virtual void Init(FJoystick_GlobalParameters InGlobalParameter);
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	// UWidget interface
	// virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface
#endif

public:
	DECLARE_DYNAMIC_DELEGATE_RetVal(FControlConfig, FGetControlConfig);

	// 摇杆设置
	UPROPERTY(EditInstanceOnly, Category = SJoystick)
	FControlConfig ControlInfo;
	UPROPERTY()
	FGetControlConfig ControlInfoDelegate;
	const FControlConfig* ConvertControlInfo(TAttribute<FControlConfig> InControlConfig) const;

	// 虚拟摇杆滑竿图
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = SJoystick)
	FSlateBrush JoystickThumb;
	UPROPERTY()
	FGetSlateBrush JoystickThumbDelegate;
	const FSlateBrush* ConvertJoystickThumb(TAttribute<FSlateBrush> InImageAsset) const;

	// 虚拟摇杆背景图
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = SJoystick)
	FSlateBrush JoystickBGI;
	UPROPERTY()
	FGetSlateBrush JoystickBGIDelegate;
	const FSlateBrush* ConvertJoystickBGI(TAttribute<FSlateBrush> InImageAsset) const;

	// 自动奔跑箭头提示
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = SJoystick)
	FSlateBrush FastRunArrow;
	UPROPERTY()
	FGetSlateBrush FastRunArrowDelegate;
	const FSlateBrush* ConvertFastRunArrow(TAttribute<FSlateBrush> InImageAsset) const;

	// 自动奔跑按钮图
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = SJoystick)
	FSlateBrush FastRunBtn;
	UPROPERTY()
	FGetSlateBrush FastRunBtnDelegate;
	const FSlateBrush* ConvertFastRunBtn(TAttribute<FSlateBrush> InImageAsset) const;

	// 自动奔跑按钮(激活效果)图
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = SJoystick)
	FSlateBrush FastRunActive;
	UPROPERTY()
	FGetSlateBrush FastRunActiveDelegate;
	const FSlateBrush* ConvertFastRunActive(TAttribute<FSlateBrush> InImageAsset) const;

	// 自动奔跑图标
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = SJoystick)
	FSlateBrush AutoRunThumb;
	UPROPERTY()
	FGetSlateBrush AutoRunThumbDelegate;
	const FSlateBrush* ConvertAutoRunThumb(TAttribute<FSlateBrush> InImageAsset) const;

	// 自动奔跑图标的偏移
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = SJoystick)
	float OffsetY = 350.f;

public:
	void SetAllowFastRun(bool flag);


//public:
//	class ATHPlayerCharacter* GetTHPlayerPawn();
//	class ATHPlayerController* GetTHPC();
//
//private:
//	UPROPERTY()
//	ATHPlayerCharacter* LocalPawn = nullptr;
//	UPROPERTY()
//	ATHPlayerController* LocalPC = nullptr;

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

protected:
	TSharedPtr<class STHJoystick> SJoystick;
	PROPERTY_BINDING_IMPLEMENTATION(FControlConfig, ControlInfo);

#pragma region Delegate
public:
	FJoystickOnTouchStart OnJoystickTouchStartDelegate;
	FJoystickOnTouchMove OnJoystickTouchMoveDelegate;
	FJoystickOnTouchEnd OnJoystickTouchEndDelegate;
	FJoystickThumbTick OnJoystickTumbMoveTickDelegate;
	FJoystickInitPropertyUpdate OnJoystickInitPropertyUpdate;

public:
	void HandleJoystickTouch(EJoystickHandleTouchType HandleTouchType, int32 ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize);

	virtual void ThumbOffsetTickDelegate(const float xAxis, const float yAxis, const bool InbIsTouchEndedTick);
	void OnJoystickInitPropertyUpdateDelegate();

#pragma endregion Delegate

public:
	bool GetJoystickControlsAndThumbOrientation(TArray<FJoystickControlInfo>& InJoystickControls, FThumbOrientationInfo& InThumbInfo);

	UPROPERTY(BlueprintReadOnly) FJoystick_GlobalParameters GlobalParameter;

	UFUNCTION(BlueprintCallable) void SetGlobalParameter(const FJoystick_GlobalParameters InGlobalParameter);
	UFUNCTION(BlueprintCallable) const FJoystick_GlobalParameters& GetGlobalParameter() { return GlobalParameter; }

	friend class UTHGameJoystick;
};
