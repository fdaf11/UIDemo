// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/BaseRadioWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UBaseRadioWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SelectRefresh(bSelected);
}

void UBaseRadioWidget::SetSelected(bool bSel)
{
	bSelected = bSel;
	if (bSel)
	{
		if (OnSelect_Delegate.IsBound())
		{
			OnSelect_Delegate.Execute(nParamID);
		}
		//其他控件设置为非选中
		UPanelWidget* Parent = GetParent();
		if (Parent != nullptr)
		{
			int32 nCount = Parent->GetChildrenCount();
			for (int32 i = 0; i < nCount; ++i)
			{	
				UWidget* child = Parent->GetChildAt(i);
				if (child != nullptr)
				{
					UBaseRadioWidget* Item = Cast<UBaseRadioWidget>(child);
					if (Item != nullptr)
					{
						if (child != this)
						{
							Item->SetSelected(false);
						}
					}
				}
			}
		}
	}
	//刷新
	SelectRefresh(bSel);
}

void UBaseRadioWidget::SelectRefresh(bool bSel)
{

}