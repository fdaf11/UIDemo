// Fill out your copyright notice in the Description page of Project Settings.
#include "UIWidget/UIBehaviorInterface/THUIClickInterface_OneParam.h"
#include "Components/Button.h"


#define ExecuteUIBehaviorDynamic( UIBehavior ) \
Handler_##UIBehavior##_Dynamic.Broadcast(GetClickParam()); \


// Add default functionality here for any IClickInterface_OneParam functions that are not pure virtual.
void ITHUIClickInterface_OneParam::ExecuteOnClicked()
{
	/*if (Handler_OnClicked.IsBound())
	{
		Handler_OnClicked.Execute(GetClickParam());
	}*/

	ExecuteUIBehaviorDynamic(OnClicked)
}

void ITHUIClickInterface_OneParam::ExecuteOnPressed()
{
	/*if (Handler_OnPressed.IsBound())
	{
		Handler_OnPressed.Execute(GetClickParam());
	}*/

	ExecuteUIBehaviorDynamic(OnPressed)
}
void ITHUIClickInterface_OneParam::ExecuteOnReleased()
{
	/*if (Handler_OnReleased.IsBound())
	{
		Handler_OnReleased.Execute(GetClickParam());
	}*/

	ExecuteUIBehaviorDynamic(OnReleased)
}
void ITHUIClickInterface_OneParam::ExecuteOnHovered()
{
	/*if (Handler_OnHovered.IsBound())
	{
		Handler_OnHovered.Execute(GetClickParam());
	}*/

	ExecuteUIBehaviorDynamic(OnHovered)
}
void ITHUIClickInterface_OneParam::ExecuteOnUnhovered()
{
	/*if (Handler_OnUnhovered.IsBound())
	{
		Handler_OnUnhovered.Execute(GetClickParam());
	}*/

	ExecuteUIBehaviorDynamic(OnUnhovered)
}

//void ITHUIClickInterface_OneParam::ExecuteOnClicked_Dynamic()
//{
//	if (Handler_OnClicked_dynamic.IsBound())
//	{
//		Handler_OnClicked_dynamic.Broadcast(GetClickParam());
//	}
//}
