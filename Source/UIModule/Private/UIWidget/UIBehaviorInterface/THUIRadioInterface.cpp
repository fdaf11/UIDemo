// Fill out your copyright notice in the Description page of Project Settings.

#include "UIWidget/UIBehaviorInterface/THUIRadioInterface.h"

// Add default functionality here for any ISingleSelectInterface functions that are not pure virtual.

void ITHUIRadioInterface::UpdateRadioSelected(bool InbSelections)
{
	SetbRadioSelected(InbSelections);
	if (InbSelections)
	{
		SelectedStyleShow();
		Handler_OnRadioSelected_Dynamic.Broadcast(GetRadioSelectedParam());
	}
	else
	{
		NoselectedStyleShow();
		Handler_OnNoRadioSelected_Dynamic.Broadcast(GetRadioSelectedParam());
	}
}
 
