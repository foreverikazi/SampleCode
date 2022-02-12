// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Equipment.generated.h"

class UButtonText;
class UEquipmentSlot;

UCLASS()
class ACTIONRPG_API UEquipment : public UUserWidget
{
	GENERATED_BODY()
	

private:
	virtual void NativeConstruct() override;

	void RefreshItems();
	void OpenInventoryList(UEquipmentSlot* InSlot);
	
	UFUNCTION(BlueprintCallable)
	void CloseInventory();

private :
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> InventoryListWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* WeaponSlot1;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* WeaponSlot2;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* WeaponSlot3;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* SkillSlot;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlot* PotionSlot;

	UPROPERTY(meta = (BindWidget))
	UButtonText* BackButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeAnimation;

	UPROPERTY(Transient)
	TArray<UEquipmentSlot*> EquipmentSlotList;

	UPROPERTY(Transient)
	UEquipmentSlot* SelectedSlot;
};
