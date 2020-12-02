#include "UIWidget/UIBehaviorInterface/THHaveInteractiveWidget2ConfigInterface.h"
#include "UIWidget/BaseWidget/THNormalBtn.h"
#include "UIWidget/BaseWidget/THInteractiveWidgetBase.h"

void ITHHaveInteractiveWidget2ConfigInterface::SetNormalButtonID(int32 InID)
{
	if (UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget())
		tWidget->nID = InID;
}

class UTextBlock* ITHHaveInteractiveWidget2ConfigInterface::GetWidgetText()
{
	if (UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget())
		return tWidget->Text_Item;

	return nullptr;
}

class UImage* ITHHaveInteractiveWidget2ConfigInterface::GetWidgetImage()
{
	if (UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget())
		return tWidget->IMG_Item;

	return nullptr;
}

class UButton* ITHHaveInteractiveWidget2ConfigInterface::GetWidgetBtn()
{
	if (UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget())
		return tWidget->Btn;

	return nullptr;
}

void ITHHaveInteractiveWidget2ConfigInterface::InitConfigStyle_InteractiveButton()
{
	SetNormalButtonID(GetNormalButtonID());		// 自行配置ID
	InitConfigStyle_Button();
	InitConfigStyle_ImgAndText();
}

void ITHHaveInteractiveWidget2ConfigInterface::UpdateWidgetRadioSelected(bool InbSelections)
{
	UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget();
	if (!tWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHExternalNormalBtnInterface::UpdateRadioSelected, tWidget == nullptr"));
		return;
	}

	return tWidget->UpdateRadioSelected(InbSelections);
}

bool ITHHaveInteractiveWidget2ConfigInterface::GetWidgetbRadioSelected()
{
	UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget();
	if (!tWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHExternalNormalBtnInterface::GetbRadioSelected, tWidget == nullptr"));
		return false;
	}

	return tWidget->GetbRadioSelected();
}

int32 ITHHaveInteractiveWidget2ConfigInterface::GetWidgetRadioSelectedParam()
{
	UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget();
	if (!tWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHExternalNormalBtnInterface::GetRadioSelectedParam, tWidget == nullptr"));
		return false;
	}

	return tWidget->GetRadioSelectedParam();
}

void ITHHaveInteractiveWidget2ConfigInterface::SetWidgetbRadioSelected(bool bSelect)
{
	UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget();
	if (!tWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITHExternalNormalBtnInterface::SetbRadioSelected, tWidget == nullptr"));
		return;
	}

	tWidget->bRadioSelected = bSelect;
}


//#pragma region OverrideFunction 注释用于粘贴
//
//void UTHOperatorButton::NativeConstruct()		// 【】TODO 请挪出Region
//{
//	Super::NativeConstruct();
//
//	InitConfigStyle_InteractiveWidget();
//	
//}
//void UTHOperatorButton::InitConfigStyle_Button()
//{
//	SetWidgetButtonStyle(TheButtonStyle);
//}
//void UTHOperatorButton::InitConfigStyle_ImgAndText()
//{
//	SetWidgetImgBrush(Brush_Icon);
//	//SetWidgetText(TextString);			// 需要则自行添加
//	//SetWidgetTextFont(TextFont);
//	//SetWidgetTextColorAndOpacity(TextColorAndOpacity);
//	//SetWidgetTextVisiblity(Visibility_Text);			// OnWidgetRebuilt当中设置Visibility会导致"眼睛"图标不可使用, By ZZQ
//	//SetWidgetImgVisiblity(Visibility_Image);
//}
//void ITHHaveInteractiveWidget2ConfigInterface::RegisterOwnedInteractiveWidgetClick2SelfCallback()
//{
//	if (UTHInteractiveWidgetBase* tWidget = GetInteractiveWidget())
//	{
//		tWidget->MACRO_AddUIBehaviorDynamic(OnClicked, this, &ITHHaveInteractiveWidget2ConfigInterface::OnClicked_NormalBtn);
//		tWidget->MACRO_AddUIBehaviorDynamic(OnPressed, this, &ITHHaveInteractiveWidget2ConfigInterface::OnPressed_NormalBtn);
//		tWidget->MACRO_AddUIBehaviorDynamic(OnReleased, this, &ITHHaveInteractiveWidget2ConfigInterface::OnReleased_NormalBtn);
//		tWidget->MACRO_AddUIBehaviorDynamic(OnHovered, this, &ITHHaveInteractiveWidget2ConfigInterface::OnHovered_NormalBtn);
//		tWidget->MACRO_AddUIBehaviorDynamic(OnUnhovered, this, &ITHHaveInteractiveWidget2ConfigInterface::OnUnhovered_NormalBtn);
//		tWidget->MACRO_AddUIRadioSelectedDynamic(OnRadioSelected, this, &ITHHaveInteractiveWidget2ConfigInterface::OnRadioSelected_NormalBtn);
//		tWidget->MACRO_AddUIRadioSelectedDynamic(OnNoRadioSelected, this, &ITHHaveInteractiveWidget2ConfigInterface::OnNoRadioSelected_NormalBtn);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ITHHaveInteractiveWidget2ConfigInterface::RegisterOwnedInteractiveWidgetClick2SelfCallback, tWidget == nullptr"));
//	}
//}
//#pragma endregion OverrideFunction 注释用于粘贴
