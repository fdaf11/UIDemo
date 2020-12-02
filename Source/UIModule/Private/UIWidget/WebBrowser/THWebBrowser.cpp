// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidget/WebBrowser/THWebBrowser.h"
#include "SWebBrowser.h"
#include "Framework/Application/SlateApplication.h"

#define LOCTEXT_NAMESPACE "WebBrowser"

TSharedRef<SWidget> UTHWebBrowser::RebuildWidget()
{
	if (IsDesignTime())
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Web Browser", "Web Browser"))
			];
	}
	else
	{
		WebBrowserWidget = SNew(SWebBrowser)
			.InitialURL(InitialURL)
			.ShowControls(false)
			.SupportsTransparency(bSupportsTransparency)
			.OnUrlChanged(BIND_UOBJECT_DELEGATE(FOnTextChanged, HandleOnUrlChanged))
			.OnBeforePopup(BIND_UOBJECT_DELEGATE(FOnBeforePopupDelegate, HandleOnBeforePopup));

		//支持中文输入法
		if (WebBrowserWidget.IsValid())
		{
			ITextInputMethodSystem* tInputSystem = FSlateApplication::Get().GetTextInputMethodSystem();

			if (tInputSystem)
			{
				WebBrowserWidget->UnbindInputMethodSystem();
				WebBrowserWidget->BindInputMethodSystem(tInputSystem);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UTHWebBrowser::RebuildWidget, Text Input System is not valid"));
			}
		}

		return WebBrowserWidget.ToSharedRef();
	}
}
