// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryList.generated.h"

class UNamedSlot;
class UEquipmentSlot;
class UHorizontalBox;

UCLASS()
class ACTIONRPG_API UInventoryList : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemType(const FPrimaryAssetType& InItemType);
	void SetSlotBtnClickCallback(TFunction<void(URPGItem*)> InCallback);

private:
	virtual void NativeConstruct() override;

	void SetUpItemList();
	void AddInventoryItemToList();
	void AddStoreItemsToList();

public :
	//
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> PurchaseConfirmWidgetClass;
	//

	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SwipeInAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UNamedSlot*	ConfirmSlot;

private:
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> InventoryItemWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> PurchaseItemWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* ItemsBox;

private:
	FPrimaryAssetType ItemType;

	TFunction<void(URPGItem*)> SlotBtnClickCallback;
};
