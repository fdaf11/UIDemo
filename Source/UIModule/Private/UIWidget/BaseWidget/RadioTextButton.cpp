// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/RadioTextButton.h"
#include "Components/ButtonSlot.h"
#include "Components/TextBlock.h"



void URadioTextButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	FontSize = TextFont.Size;
/*	bInit = false;*/
	MyText = NewObject<UTextBlock>(this, TEXT("MyText"));
	if (MyText != nullptr)
	{
		MyText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		
		if (TextString != "")
		{
			MyText->SetText(FText::FromString(TextString));
		}
		AddChild(MyText);
		if (bSelected)
		{
			SelectTextStyle();
		}
		else
		{
			NormalTextStyle();
		}
	}

	


}

void URadioTextButton::Init()
{
	//OnWidgetRebuilt Addchild出错  暂时处理
	if (!bInit)
	{
		AddChild(MyText);
		bInit = true;
	}
	
}

/**/
void URadioTextButton::SelectTextStyle()
{
	//Super::SelectStyle();
	if (MyText /*&& bInit*/)
	{
		MyText->SetColorAndOpacity(SelectedTextColorAndOpacity);
		if (SelectedFontSize > 0)
		{
			TextFont.Size = SelectedFontSize;
			MyText->SetFont(TextFont);
		}
	}
}

void URadioTextButton::NormalTextStyle()
{
	//Super::NormalStyle();
	if (MyText /*&& bInit*/)
	{
		MyText->SetColorAndOpacity(TextColorAndOpacity);
		if (SelectedFontSize > 0)
		{
			TextFont.Size = FontSize;
			MyText->SetFont(TextFont);
		}
	}
}

void URadioTextButton::SetSelected(bool bInSelected)
{
	Super::SetSelected(bInSelected);
	if (bSelected)
	{
		SelectTextStyle();
		//其他按钮还原
		UPanelWidget* Parent = GetParent();
		if (Parent != nullptr)
		{
			int32 nCount = Parent->GetChildrenCount();
			for (int32 i = 0; i < nCount; ++i)
			{
				UWidget* child = Parent->GetChildAt(i);
				if (child != nullptr)
				{
					URadioTextButton* radiobutton = Cast<URadioTextButton>(child);
					if (radiobutton != nullptr)
					{
						if (child != this)
						{
							radiobutton->NormalTextStyle();
						}
					}
				}
			}

		}
	}
	else
	{
		NormalTextStyle();
	}

}

void URadioTextButton::SetTextString(const FString& s_String)
{
	/*Init();*/
	TextString = s_String;
	MyText->SetText(FText::FromString(TextString));

}