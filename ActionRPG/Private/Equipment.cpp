#include "Equipment.h"
#include "RPGPlayerControllerBase.h"
#include "EquipmentSlot.h"
#include "InventoryList.h"
#include "ButtonText.h"

void UEquipment::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(FadeAnimation);

	EquipmentSlotList.Empty();
	EquipmentSlotList.Add(WeaponSlot1);
	EquipmentSlotList.Add(WeaponSlot2);
	EquipmentSlotList.Add(WeaponSlot3);
	EquipmentSlotList.Add(SkillSlot);
	EquipmentSlotList.Add(PotionSlot);

	RefreshItems();

	if (BackButton)
	{
		BackButton->OnButtonClick().AddUObject(this, &ThisClass::CloseInventory);
	}
}

void UEquipment::RefreshItems()
{
	auto WeakThis = MakeWeakObjectPtr(this);
	auto EquipSlotBtnClick = [this, WeakThis](UEquipmentSlot* InSlot)
	{
		if (WeakThis.IsValid())
		{
			SelectedSlot = InSlot;
			OpenInventoryList(InSlot);
		}
	};

	if (ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		for (UEquipmentSlot* EquipSlot : EquipmentSlotList)
		{
			EquipSlot->SetSlotBtnClickCallback(EquipSlotBtnClick);
			EquipSlot->RefreshItem();
		}
	}

}

void UEquipment::OpenInventoryList(UEquipmentSlot* InSlot)
{
	if (nullptr == InSlot) { return ;}

	auto WeakThis = MakeWeakObjectPtr(this);
	auto InvenSlotBtnClick = [this, WeakThis](URPGItem* InItem)
	{
		if (WeakThis.IsValid() && SelectedSlot)
		{
			SelectedSlot->UpdateEquipmentSlot(InItem);
		}
	};

	if (UInventoryList* InvenList = CreateWidget<UInventoryList>(this, InventoryListWidgetClass))
	{
		InvenList->SetItemType(InSlot->GetRPGItemSlot().ItemType);
		InvenList->SetSlotBtnClickCallback(InvenSlotBtnClick);
		InvenList->AddToViewport();
	}
}

void UEquipment::CloseInventory()
{
	if (ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PC->CloseInventory();
		RemoveFromParent();
	}
}