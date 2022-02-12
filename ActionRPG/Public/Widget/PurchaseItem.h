// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/RPGItem.h"
#include "Blueprint/UserWidget.h"
#include "PurchaseItem.generated.h"

class UImage;
class UButton;
class UTextBlock;

UCLASS()
class ACTIONRPG_API UPurchaseItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemInfo(URPGItem* InItem);
	void SetParentNamedSlot(UNamedSlot* InSlot);
	void SetSlotBtnClickCallback(TFunction<void(URPGItem*)> InCallback);

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ItemSlotClicked();

private:
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> PurchaseConfirmWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemNameLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceLabel;

	UPROPERTY(meta = (BindWidget))
	UButton* InventoryButton;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;

private:
	TWeakObjectPtr<URPGItem> RPGItem;
	TWeakObjectPtr<UNamedSlot> InventoryNamedSlot;
	TFunction<void(URPGItem*)> SlotBtnClickCallback;
	
};
