#include "UIWidget/BaseWidget/THNormalBtn.h"
#include "Components/Button.h"
//#include "THMusicPluginLibrary.h"
//#include "Controller/THPlayerControllerBase.h"

void UTHNormalBtn::NativeConstruct()
{
	Super::NativeConstruct();

	// 1. NativeConstuct将在初始的RegisterUIComponent(即PostInitializeComp)之后调用;
	// 2. Wrap.AddChild会重复调用NativeConstruct
	if (Btn)
	{
		Btn->OnClicked.AddUniqueDynamic(this, &UTHNormalBtn::ExecuteOnClicked);
		Btn->OnPressed.AddUniqueDynamic(this, &UTHNormalBtn::ExecuteOnPressed);
		Btn->OnReleased.AddUniqueDynamic(this, &UTHNormalBtn::ExecuteOnReleased);
		Btn->OnHovered.AddUniqueDynamic(this, &UTHNormalBtn::ExecuteOnHovered);
		Btn->OnUnhovered.AddUniqueDynamic(this, &UTHNormalBtn::ExecuteOnUnhovered);
	}
}

void UTHNormalBtn::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	InitConfigStyle_Button();
}

void UTHNormalBtn::InitConfigStyle_Button()
{
	SetWidgetButtonStyle(TheButtonStyle);
}

#if WITH_EDITOR
void UTHNormalBtn::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	InitConfigStyle_Button();
}
#endif

#pragma region OverrideFunction
void UTHNormalBtn::ExecuteOnClicked()
{
	ITHUIClickInterface_OneParam::ExecuteOnClicked();

	OnWidgetClicked(GetClickParam());

	// 【】TODO音乐的调用方式后续修改
	//// 【】TODO 如何判断前、后端？进行播放? 再次进行派生处理？有点麻烦，不过也不是不可;
	//ATHPlayerControllerBase* tPC = Cast<ATHPlayerControllerBase>(GetWorld()->GetFirstPlayerController());
	//if (tPC)
	//{
	//	UTHCommonFunctionLibrary::BPCallPlaySound2D(tPC->LocalMusicManager, EMusicType::SoundEffect_Divider, ClickedPlaySound);
	//}
	// 【】TODO 还是后续派生出来再说。
	/*else
	{
		UMusicManager* tMusicManager = UTreasureHunterGameInstance::GetMusicManager(this);
		{
			UTHMusicPluginLibrary::PlaySound2D(tMusicManager, EMusicType::SoundEffect_Divider, ClickedPlaySound);
		}
	}*/
}
#pragma endregion OverrideFunction

