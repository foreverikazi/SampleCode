#pragma once

#include "CoreMinimal.h"
#include "Items/RPGItem.h"
#include "RPGTypes.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentSlot.generated.h"

class UImage;
class UBorder;
class UButton;
class UTextBlock;

UCLASS()
class ACTIONRPG_API UEquipmentSlot : public UUserWidget
{
	GENERATED_BODY()
	
public :
	void RefreshItem();
	void SetSlotBtnClickCallback(TFunction<void(UEquipmentSlot*)> InCallback);
	FRPGItemSlot GetRPGItemSlot() const;

	UFUNCTION(BlueprintCallable)
	void UpdateEquipmentSlot(URPGItem* InItem);

private :
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void EquipButtonClicked();

	void SetPotionInfo(const URPGItem* InItem);
	void OnSlottedItemChanged(FRPGItemSlot ItemSlot, URPGItem* RPGItem);
	void SetItemDefault();

private :
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotTypeLabel;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PotionNumberLabel;
	
	UPROPERTY(meta = (BindWidget))
	UBorder* BorderPotion;

	UPROPERTY(meta = (BindWidget))
	UButton* EquipButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* EquipItemAnim;
	
	UPROPERTY(EditAnywhere, Category = config)
	FSlateBrush DefaultBrush;

	UPROPERTY(EditAnywhere, Category = config)
	FRPGItemSlot RPGItemSlot;

private:
	TFunction<void(UEquipmentSlot*)> SlotBtnClickCallback;

};
