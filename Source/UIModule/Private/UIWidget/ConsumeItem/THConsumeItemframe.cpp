// Fill out your copyright notice in the Description page of Project Settings.


#include "UIWidget/ConsumeItem/THConsumeItemframe.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UIWidget/BaseWidget/NormalButton.h"


void UTHConsumeItemframe::SetItemInfo(int32 ItemType, int32 InHaveNum, int32 InDemandNum, UTexture2D* ItemTex)
{
	if (!Text_HaveNum || !Text_NeedAfford || !IMG_Item || !NorBT_Add)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTHConsumeItemframe::SetItemInfo, !Text_Num || !Text_NumMax || !IMG_Item || !NorBT_Add"));
		return;
	}

	NorBT_Add->nID = ItemType;
	const bool tbIsEnough2Afford = InHaveNum >= InDemandNum;
	Text_HaveNum->SetText(FText::AsNumber(InHaveNum));
	Text_NeedAfford->SetText(FText::AsNumber(InDemandNum));
	IMG_Item->SetBrushFromTexture(ItemTex);	
	CallBP_Enough2Afford(tbIsEnough2Afford, InHaveNum, InDemandNum);
}
