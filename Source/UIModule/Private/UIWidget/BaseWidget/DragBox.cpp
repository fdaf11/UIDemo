// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/BaseWidget/DragBox.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"



void UDragBox::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();

	this->SetMainImage(MainTexture);
	this->SetFrameImage(FrameTexture);	
}

FReply UDragBox::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	if (bDrag)
	{
		//EKeys::LeftMouseButton
		Reply.NativeReply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
		//Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), EKeys::AnyKey);
	}
	else
	{
		Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}

	return Reply.NativeReply;
}

FReply UDragBox::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	UE_LOG(LogTemp, Warning, TEXT("*********** NativeOnMouseButtonUp *************"));
	//const FVector2D& Position = InMouseEvent.GetLastScreenSpacePosition();

	if (bCanClick)
	{
		if (OnClickDelegate.IsBound())
		{
			OnClickDelegate.Execute(nID, nType);
			//OnClickDelegate.Execute(nID, nType, Position.X, Position.Y);
		}
	}

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

bool UDragBox::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("***********NativeOnDrop *************"));
	if (OnDropDelegate.IsBound())
	{
		UDragBox* Drag = Cast<UDragBox>(InOperation->Payload);
		if (Drag != nullptr && Drag != this)
		{
			OnDropDelegate.Execute(nID, nType, Drag->nID, Drag->nType);
		}
	}

	return true;
}

//void UDragBox::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
//{
//	if (CurrentDraggableBox)
//	{
//		CurrentDraggableBox->
//	}
//	UWidgetBlueprintLibrary::CreateDragDropOperation();
//}

void UDragBox::SetMainImage(UTexture2D* Tex)
{
	if (Tex && MainImage)
	{
		MainImage->SetVisibility(ESlateVisibility::Visible);
		MainImage->SetBrushFromTexture(Tex, true);
		UCanvasPanelSlot* CanvesSlot = Cast<UCanvasPanelSlot>(Slot);
		UCanvasPanelSlot* MainImageSlot = Cast<UCanvasPanelSlot>(MainImage->Slot);
		if (CanvesSlot)
		{
			MainImageSlot->SetSize(CanvesSlot->GetSize());
			MainImage->SetBrushSize(CanvesSlot->GetSize());
		}
		//MainImage->SetBrushSize(FVector2D(Tex->GetSurfaceWidth(), Tex->GetSurfaceHeight()));	
	}
}

void UDragBox::SetFrameImage(UTexture2D* Tex)
{
	if (Tex && FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Visible);
		FrameImage->SetBrushFromTexture(Tex, true);

		UCanvasPanelSlot* CanvesSlot = Cast<UCanvasPanelSlot>(Slot);
		UCanvasPanelSlot* FrameImageSlot = Cast<UCanvasPanelSlot>(MainImage->Slot);
		if (CanvesSlot)
		{
			FrameImageSlot->SetSize(CanvesSlot->GetSize());
			FrameImage->SetBrushSize(CanvesSlot->GetSize());
		}
	}
	//FrameImage->SetVisibility(ESlateVisibility::Visible);
}