// Fill out your copyright notice in the Description page of Project Settings.
#include "UIWidget/UIBehaviorInterface/THUIClickInterface.h"
#include "Components/Button.h"

// Add default functionality here for any IClickInterface functions that are not pure virtual.

#pragma region >>> FunctionDelegate <<<

void ITHUIClickInterface::ExecuteOnClicked()
{
	if (Handler_OnClicked.IsBound())
	{
		Handler_OnClicked.Execute();
	}
}
void ITHUIClickInterface::ExecuteOnPressed()
{
	if (Handler_OnPressed.IsBound())
	{
		Handler_OnPressed.Execute();
	}
}
void ITHUIClickInterface::ExecuteOnReleased()
{
	if (Handler_OnReleased.IsBound())
	{
		Handler_OnReleased.Execute();
	}
}
void ITHUIClickInterface::ExecuteOnHovered()
{
	if (Handler_OnHovered.IsBound())
	{
		Handler_OnHovered.Execute();
	}
}
void ITHUIClickInterface::ExecuteOnUnhovered()
{
	if (Handler_OnUnhovered.IsBound())
	{
		Handler_OnUnhovered.Execute();
	}
}
#pragma endregion
