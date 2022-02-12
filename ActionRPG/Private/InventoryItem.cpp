#include "InventoryItem.h"
#include "RPGPlayerControllerBase.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "InventoryList.h"
#include "EquipmentSlot.h"

void UInventoryItem::NativeConstruct()
{
	Super::NativeConstruct();

	if (InventoryButton)
	{
		InventoryButton->OnClicked.AddDynamic(this, &ThisClass::ItemSlotClicked);
	}
}

void UInventoryItem::ItemSlotClicked()
{
	if (SlotBtnClickCallback)
	{
		SlotBtnClickCallback(RPGItem.Get());
	}
}

void UInventoryItem::SetItemInfo(URPGItem* InItem)
{
	RPGItem = MakeWeakObjectPtr(InItem);

	if (nullptr == InItem)
	{
		return;
	}

	if (ItemImage)
	{
		ItemImage->SetBrush(InItem->ItemIcon);
	}

	if (ItemName)
	{
		ItemName->SetText(InItem->ItemName);
	}

	if (LongDescription)
	{
		LongDescription->SetText(InItem->ItemDescription);
	}

	SetPotionInfo(InItem);
}

void UInventoryItem::SetSlotBtnClickCallback(TFunction<void(URPGItem*)> InCallback)
{
	SlotBtnClickCallback = InCallback;
}

void UInventoryItem::SetPotionInfo(URPGItem* InItem)
{
	if (BorderPotion)
	{
		if (InItem->IsConsumable())
		{
			BorderPotion->SetVisibility(ESlateVisibility::Visible);

			if (ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
			{
				int ItemCount = PC->GetInventoryItemCount(InItem);

				if (PotionNumberLabel)
				{
					PotionNumberLabel->SetText(FText::AsNumber(ItemCount));
				}
			}
		}
		else
		{
			BorderPotion->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
