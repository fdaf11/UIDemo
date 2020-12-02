// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidget/DragDrop/THDragDropOperation.h"

void UTHDragDropOperation::BpCallOnDragged(const FPointerEvent& PointerEvent)
{
	ExecuteOnDragged(PointerEvent);
}

void UTHDragDropOperation::ExecuteOnDragged(const FPointerEvent& PointerEvent)
{
	if (Handler_OnDragged.IsBound())
		Handler_OnDragged.Execute(PointerEvent, this);
}
