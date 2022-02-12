#include "PurchaseItem.h"
#include "PurchaseConfirm.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/NamedSlot.h"

void UPurchaseItem::NativeConstruct()
{
	Super::NativeConstruct();

	if (InventoryButton)
	{
		InventoryButton->OnClicked.AddDynamic(this, &ThisClass::ItemSlotClicked);
	}
}

void UPurchaseItem::ItemSlotClicked()
{
	if (InventoryNamedSlot.IsValid())
	{
		if (UPurchaseConfirm* PurchaseItem = CreateWidget<UPurchaseConfirm>(this, PurchaseConfirmWidgetClass))
		{
			PurchaseItem->SetItemInfo(RPGItem.Get());
			PurchaseItem->SetSlotBtnClickCallback(SlotBtnClickCallback);
			InventoryNamedSlot->SetContent(PurchaseItem);
		}
	}
}

void UPurchaseItem::SetItemInfo(URPGItem* InItem)
{
	RPGItem = MakeWeakObjectPtr(InItem);

	if (nullptr == InItem)
	{
		return;
	}

	if (ItemIcon)
	{
		ItemIcon->SetBrush(InItem->ItemIcon);
	}

	if (ItemNameLabel)
	{
		ItemNameLabel->SetText(InItem->ItemName);
	}

	if (DescriptionLabel)
	{
		DescriptionLabel->SetText(InItem->ItemDescription);
	}

	if (PriceLabel)
	{
		FText Price = FText::Format(FText::FromString(TEXT("{0} souls")), InItem->Price);
		PriceLabel->SetText(Price);
	}
}


void UPurchaseItem::SetSlotBtnClickCallback(TFunction<void(URPGItem*)> InCallback)
{
	SlotBtnClickCallback = InCallback;
}

void UPurchaseItem::SetParentNamedSlot(UNamedSlot* InSlot)
{
	InventoryNamedSlot = MakeWeakObjectPtr(InSlot);
}

