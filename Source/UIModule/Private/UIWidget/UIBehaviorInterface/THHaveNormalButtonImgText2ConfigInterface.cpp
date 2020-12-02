#include "UIWidget/UIBehaviorInterface/THHaveNormalButtonImgText2ConfigInterface.h"
#include "UIWidget/BaseWidget/THNormalBtn_ImgText.h"
//
//void ITHHaveNormalButtonImgText2ConfigInterface::RegisterOwnedNormalBtnClick2SelfCallback()
//{
//	if (UTHNormalBtn_ImgText* tNormalBtn = GetNormalButton_UserWidget())
//	{
//		tNormalBtn->MACRO_AddUIBehaviorDynamic(OnClicked, this, &ITHHaveNormalButtonImgText2ConfigInterface::OnClicked_NormalBtn); 
//		tNormalBtn->MACRO_AddUIBehaviorDynamic(OnPressed, this, &ITHHaveNormalButtonImgText2ConfigInterface::OnPressed_NormalBtn);
//		tNormalBtn->MACRO_AddUIBehaviorDynamic(OnReleased, this, &ITHHaveNormalButtonImgText2ConfigInterface::OnReleased_NormalBtn);
//		tNormalBtn->MACRO_AddUIBehaviorDynamic(OnHovered, this, &ITHHaveNormalButtonImgText2ConfigInterface::OnHovered_NormalBtn);
//		tNormalBtn->MACRO_AddUIBehaviorDynamic(OnUnhovered, this, &ITHHaveNormalButtonImgText2ConfigInterface::OnUnhovered_NormalBtn);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ITHHaveNormalButtonImgText2ConfigInterface::RegisterOwnedNormalBtnClick2SelfCallback, tNormalBtn == nullptr"));
//	}
//}

void ITHHaveNormalButtonImgText2ConfigInterface::SetNormalButtonID(int32 InID)
{
	if (UTHNormalBtn_ImgText* tNormalBtn = GetNormalButton_UserWidget())
		tNormalBtn->nID = InID;
}

class UTextBlock* ITHHaveNormalButtonImgText2ConfigInterface::GetWidgetText()
{
	if (UTHNormalBtn_ImgText* tNormalBtn = GetNormalButton_UserWidget())
		return tNormalBtn->Text_Item;

	return nullptr;
}

class UImage* ITHHaveNormalButtonImgText2ConfigInterface::GetWidgetImage()
{
	if (UTHNormalBtn_ImgText* tNormalBtn = GetNormalButton_UserWidget())
		return tNormalBtn->IMG_Item;

	return nullptr;
}

class UButton* ITHHaveNormalButtonImgText2ConfigInterface::GetWidgetBtn()
{
	if (UTHNormalBtn_ImgText* tNormalBtn = GetNormalButton_UserWidget())
		return tNormalBtn->Btn;

	return nullptr;
}

void ITHHaveNormalButtonImgText2ConfigInterface::InitConfigStyle_NormalButton_ImgText()
{
	SetNormalButtonID(GetNormalButtonID());		// 自行配置ID
	InitConfigStyle_Button();
	InitConfigStyle_ImgAndText();
}

//void ITHHaveNormalButtonImgText2ConfigInterface::InitRegisterOwnedBtnClick2SelfCallback()
//{
//	UTHNormalBtn_ImgText* tBtn = GetNormalButtonImgText();
//	if (!tBtn)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ITHHaveNormalButtonImgText2ConfigInterface::InitRegisterOwnedBtnClick2SelfCallback, tBtn == nullptr"));
//		return;
//	}
//
//	tBtn->MACRO_AddUIBehaviorDynamic(OnClicked, this, &ITHHaveNormalButtonImgText2ConfigInterface::OnOwnedButtonClicked);
//}

//#pragma region OverrideFunction
//void UTHOperatorButton::NativeConstruct()		// 【】TODO 需要挪出去
//{
//	Super::NativeConstruct();
//
//	InitConfigStyle_NormalButton_ImgText();
//	InitRegisterOwnedInteractiveBtnClick2SelfCallback();
//}
//void UTHNormalBtn_ImgText::OnWidgetRebuilt()		// 【】TODO 需要挪出去
//{
//	Super::OnWidgetRebuilt();
//
//	InitConfigStyle_ImgAndText();
//}
//
//void UTHOperatorButton::InitConfigStyle_Button()
//{
//	if (NormalBtn)
//	{
//		NormalBtn->SetWidgetButtonStyle(TheButtonStyle);
//	}
//}
//
//void UTHOperatorButton::InitConfigStyle_ImgAndText()
//{
//	if (NormalBtn)
//	{
//		NormalBtn->SetWidgetImgBrush(Brush_Icon);
//		//NormalBtn->SetWidgetText(TextString);			// 需要则自行添加
//		//NormalBtn->SetWidgetTextFont(TextFont);
//		//NormalBtn->SetWidgetTextColorAndOpacity(TextColorAndOpacity);
//		//NormalBtn->SetWidgetTextVisiblity(Visibility_Text);			// OnWidgetRebuilt当中设置Visibility会导致"眼睛"图标不可使用, By ZZQ
//		//NormalBtn->SetWidgetImgVisiblity(Visibility_Image);
//	}
//}
//void UTHOperatorButton::InitRegisterOwnedBtnClick2SelfCallback()
//{
//	if (NormalBtn)
//	{
//		//tNormalBtn->BindOnRadioSelected(this, &UTHOperatorButton::OnOwnedButtonRadioSelected);
//
//		NormalBtn->MACRO_AddUIBehaviorDynamic(OnClicked, this, &UTHOperatorButton::OnClicked_NormalBtn);
//		NormalBtn->MACRO_AddUIBehaviorDynamic(OnPressed, this, &UTHOperatorButton::OnPressed_NormalBtn);
//		NormalBtn->MACRO_AddUIBehaviorDynamic(OnReleased, this, &UTHOperatorButton::OnReleased_NormalBtn);
//		NormalBtn->MACRO_AddUIBehaviorDynamic(OnHovered, this, &UTHOperatorButton::OnHovered_NormalBtn);
//		NormalBtn->MACRO_AddUIBehaviorDynamic(OnUnhovered, this, &UTHOperatorButton::OnUnhovered_NormalBtn);
//	}
//}
//
//void ITHHaveNormalButtonImgText2ConfigInterface::OnClicked_NormalBtn(int32 InID)
//{
//	ExecuteOnClicked();
//}
//
//void ITHHaveNormalButtonImgText2ConfigInterface::OnPressed_NormalBtn(int32 InID)
//{
//	ExecuteOnPressed();
//}
//
//void ITHHaveNormalButtonImgText2ConfigInterface::OnReleased_NormalBtn(int32 InID)
//{
//	ExecuteOnReleased();
//}
//
//void ITHHaveNormalButtonImgText2ConfigInterface::OnHover_NormalBtn(int32 InID)
//{
//	ExecuteOnHovered();
//}
//
//void ITHHaveNormalButtonImgText2ConfigInterface::OnUnhover_NormalBtn(int32 InID)
//{
//	ExecuteOnUnhovered();
//}
//#pragma endregion OverrideFunction

