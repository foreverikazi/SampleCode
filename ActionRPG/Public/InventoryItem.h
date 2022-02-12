#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Items/RPGItem.h"
#include "InventoryItem.generated.h"

class UImage;
class UBorder;
class UButton;
class UTextBlock;
class UInventoryList;

UCLASS()
class ACTIONRPG_API UInventoryItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemInfo(URPGItem* InItem);
	void SetSlotBtnClickCallback(TFunction<void(URPGItem*)> InCallback);

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ItemSlotClicked();

	void SetPotionInfo(URPGItem* InItem);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LongDescription;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PotionNumberLabel;

	UPROPERTY(meta = (BindWidget))
	UBorder* BorderPotion;

	UPROPERTY(meta = (BindWidget))
	UButton* InventoryButton;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

public :
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<URPGItem> RPGItem;

	TFunction<void(URPGItem*)> SlotBtnClickCallback;
};
