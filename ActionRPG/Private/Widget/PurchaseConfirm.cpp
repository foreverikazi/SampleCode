#include "Widget/PurchaseConfirm.h"
#include "Widget/PurchaseItem.h"
#include "Widget/ButtonText.h"
#include "RPGPlayerControllerBase.h"
#include "Components/HorizontalBox.h"
#include "Components/NamedSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TimerManager.h"

UPurchaseConfirm::UPurchaseConfirm(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Quantity(1)
{
}


void UPurchaseConfirm::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(FadeAnimation);
	AddBtnEvent();
	
}

void UPurchaseConfirm::AddBtnEvent()
{
	if (LessButton)
	{
		LessButton->OnClicked.AddDynamic(this, &ThisClass::LessBtnClicked);
	}

	if (MoreButton)
	{
		MoreButton->OnClicked.AddDynamic(this, &ThisClass::MoreBtnClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnButtonClick().AddUObject(this, &ThisClass::CancelBtnClicked);
	}

	if (ConfirmButton)
	{
		ConfirmButton->OnButtonClick().AddUObject(this, &ThisClass::ConfirmBtnClicked);
	}
}

void UPurchaseConfirm::SetItemInfo(URPGItem* InItem)
{
	RPGItem = MakeWeakObjectPtr(InItem);

	if (nullptr == InItem) { return ;}

	if (UPurchaseItem* PurchaseItem = CreateWidget<UPurchaseItem>(this, PurchaseItemWidgetClass))
	{
		PurchaseItem->SetItemInfo(InItem);
		IconSlot->AddChild(PurchaseItem);

		if (InItem->IsConsumable())
		{
			QuantitySelectionBox->SetVisibility(ESlateVisibility::Visible);
		}

		UpdateQuanttySelector();
		UpdateWindow(InItem);
	}
}

void UPurchaseConfirm::SetSlotBtnClickCallback(TFunction<void(URPGItem*)> InCallback)
{
	SlotBtnClickCallback = InCallback;
}

void UPurchaseConfirm::UpdateWindow(URPGItem* InItem)
{
	if (ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (PC->CanPurchaseItem(InItem))
		{
			ConfirmButton->SetIsEnabled(true);
		}
		else
		{
			ConfirmButton->SetIsEnabled(false);
		}
	}
}

void UPurchaseConfirm::UpdateQuanttySelector(const int32 InAddQuantity)
{
	Quantity = Quantity + InAddQuantity;
	if (Quantity > 0)
	{
		if (QuantityLabel)
		{
			QuantityLabel->SetText(FText::AsNumber(Quantity));
		}
	}
}

void UPurchaseConfirm::TryPurchaseItem()
{
	if (RPGItem.IsValid())
	{
		if (ARPGPlayerControllerBase* PC = Cast<ARPGPlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			PC->PurchaseItem(RPGItem.Get(), Quantity);
		}
	}
}

void UPurchaseConfirm::CloseWidget()
{
	RemoveFromParent();
}

void UPurchaseConfirm::CancelBtnClicked()
{
	CloseWidget();
}

void UPurchaseConfirm::ConfirmBtnClicked()
{
	if (ConfirmButton)
	{
		ConfirmButton->SetIsEnabled(false);

		TryPurchaseItem();

		if (SlotBtnClickCallback)
		{
			SlotBtnClickCallback(RPGItem.Get());
		}
		CloseWidget();
	}
}


void UPurchaseConfirm::MoreBtnClicked()
{
	UpdateQuanttySelector(1);
}

void UPurchaseConfirm::LessBtnClicked()
{
	UpdateQuanttySelector(-1);
}
