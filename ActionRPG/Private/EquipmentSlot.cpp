#include "EquipmentSlot.h"
#include "RPGPlayerControllerBase.h"
#include "RPGGameInstanceBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/Image.h"

void UEquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PC->OnSlottedItemChangedNative.AddUObject(this, &ThisClass::OnSlottedItemChanged);
	}

	if (EquipButton)
	{
		EquipButton->OnClicked.AddDynamic(this, &ThisClass::EquipButtonClicked);
	}
}

void UEquipmentSlot::NativeDestruct()
{
	if (ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PC->OnSlottedItemChangedNative.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UEquipmentSlot::EquipButtonClicked()
{
	if (SlotBtnClickCallback)
	{
		SlotBtnClickCallback(this);
	}
}

void UEquipmentSlot::UpdateEquipmentSlot(URPGItem* InItem)
{
	ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (nullptr == PC) { return ;}

	URPGGameInstanceBase* Instance = Cast<URPGGameInstanceBase>(GetWorld()->GetGameInstance());
	if (nullptr == Instance) { return; }

	if(InItem)
	{ 
		PC->SetSlottedItem(RPGItemSlot, InItem);
		RefreshItem();
		Instance->WriteSaveGame();
	}
}

void UEquipmentSlot::RefreshItem()
{
	ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (nullptr == PC)
	{
		SetItemDefault();
		return;
	}

	URPGItem* RPGItem = PC->GetSlottedItem(RPGItemSlot);
	if (RPGItem && ItemImage)
	{
		ItemImage->SetBrush(RPGItem->ItemIcon);
	}
	else
	{
		SetItemDefault();
		return;
	}

	if (PotionNumberLabel)
	{
		int ItemCount = PC->GetInventoryItemCount(RPGItem);
		PotionNumberLabel->SetText(FText::AsNumber(ItemCount));
	}

	if (SlotTypeLabel)
	{
		FText TypeText = FText::FromName(RPGItemSlot.ItemType.GetName());
		SlotTypeLabel->SetText(TypeText);
	}

	SetPotionInfo(RPGItem);
	PlayAnimation(EquipItemAnim);
}

void UEquipmentSlot::SetSlotBtnClickCallback(TFunction<void(UEquipmentSlot*)> InCallback)
{
	SlotBtnClickCallback = InCallback;
}

FRPGItemSlot UEquipmentSlot::GetRPGItemSlot() const
{
	return RPGItemSlot;
}

void UEquipmentSlot::SetItemDefault()
{
	if (ItemImage)
	{
		ItemImage->SetBrush(DefaultBrush);
	}
	
	if (BorderPotion)
	{
		BorderPotion->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UEquipmentSlot::SetPotionInfo(const URPGItem* InItem)
{
	// Is Consumable?
	if (InItem && InItem->MaxCount > 0)
	{
		BorderPotion->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		BorderPotion->SetVisibility(ESlateVisibility::Visible);
	}
}

void UEquipmentSlot::OnSlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* RPGItem)
{
	if (RPGItemSlot == ItemSlot)
	{
		RefreshItem();
	}
}
