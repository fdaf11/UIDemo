// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/UIBehaviorInterface/THUIDragDropInterface.h"
#include "Blueprint/DragDropOperation.h"
#include "UIWidget/DragDrop/THDragDropOperation.h"

UTHDragDropOperation* ITHUIDragDropInterface::CreateDragDropOp(UObject* WorldContextObject)
{
	return NewObject<UTHDragDropOperation>(WorldContextObject, MakeUniqueObjectName(WorldContextObject, UTHDragDropOperation::StaticClass()));
}

// Add default functionality here for any IDragDropInterface functions that are not pure virtual.

void ITHUIDragDropInterface::ExecuteOnDragDetectedEvent()
{
	if (OnDragDetectedDelegate.IsBound())
	{
		OnDragDetectedDelegate.Execute(GetDragDropParam());
	}
}
