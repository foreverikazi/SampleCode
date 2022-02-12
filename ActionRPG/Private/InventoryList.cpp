#include "InventoryList.h"
#include "InventoryItem.h"
#include "PurchaseItem.h"
#include "Items/RPGTokenItem.h"
#include "RPGGameInstanceBase.h"
#include "Components/HorizontalBox.h"
#include "RPGPlayerControllerBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EquipmentSlot.h"
#include "PurchaseConfirm.h"
#include "Components/NamedSlot.h"

void UInventoryList::NativeConstruct()
{
	Super::NativeConstruct();

	SetUpItemList();
	PlayAnimation(SwipeInAnimation);
}

void UInventoryList::SetItemType(const FPrimaryAssetType& InItemType)
{
	ItemType = InItemType;
}

void UInventoryList::SetSlotBtnClickCallback(TFunction<void(URPGItem*)> InCallback)
{
	SlotBtnClickCallback = InCallback;
}

void UInventoryList::SetUpItemList()
{
	ItemsBox->ClearChildren();
	AddInventoryItemToList();
	AddStoreItemsToList();
}

void UInventoryList::AddInventoryItemToList()
{
	if (ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		TArray<URPGItem*> Items;

		PC->GetInventoryItems(Items, ItemType);

		for (auto RPGItem : Items)
		{
			if (UInventoryItem* InvenItem = CreateWidget<UInventoryItem>(this, InventoryItemWidgetClass))
			{
				InvenItem->SetItemInfo(RPGItem);
				InvenItem->SetSlotBtnClickCallback(SlotBtnClickCallback);
				ItemsBox->AddChild(InvenItem);
			}
		}
	}
}

void UInventoryList::AddStoreItemsToList()
{
	URPGGameInstanceBase* Instance = Cast<URPGGameInstanceBase>(GetWorld()->GetGameInstance());
	if (nullptr == Instance) { return; }

	ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (nullptr == PC) { return; }

	TArray<URPGItem*>* Items = Instance->GetStoreItems();

	for (URPGItem* RPGItem : *Items)
	{
		if (0 == PC->GetInventoryItemCount(RPGItem))
		{
			FPrimaryAssetId AssetID = UKismetSystemLibrary::GetPrimaryAssetIdFromObject(RPGItem);
			if (ItemType == AssetID.PrimaryAssetType)
			{
				if (UPurchaseItem* PurchaseItem = CreateWidget<UPurchaseItem>(this, PurchaseItemWidgetClass))
				{
					if (PC->CanPurchaseItem(RPGItem))
					{
						PurchaseItem->SetIsEnabled(true);
					}
					else
					{
						PurchaseItem->SetIsEnabled(false);
					}
					PurchaseItem->SetItemInfo(RPGItem);
					PurchaseItem->SetParentNamedSlot(ConfirmSlot);
					PurchaseItem->SetSlotBtnClickCallback(SlotBtnClickCallback);
					ItemsBox->AddChild(PurchaseItem);
				}
			}
		}
	}
}

