#pragma once

#include "CoreMinimal.h"
#include "Items/RPGItem.h"
#include "Blueprint/UserWidget.h"
#include "PurchaseConfirm.generated.h"

class UButton;
class UNamedSlot;
class UTextBlock;
class UButtonText;
class UHorizontalBox;

UCLASS()
class ACTIONRPG_API UPurchaseConfirm : public UUserWidget
{
	GENERATED_UCLASS_BODY()
	
public :
	void SetItemInfo(URPGItem* InItem);
	void SetSlotBtnClickCallback(TFunction<void(URPGItem*)> InCallback);

private:
	virtual void NativeConstruct() override;

	void AddBtnEvent();
	void UpdateWindow(URPGItem* InItem);
	void UpdateQuanttySelector(const int32 InAddQuantity = 0);
	void TryPurchaseItem();
	void CloseWidget();

private :
	UFUNCTION()
	void CancelBtnClicked();

	UFUNCTION()
	void ConfirmBtnClicked();

	UFUNCTION()
	void MoreBtnClicked();

	UFUNCTION()
	void LessBtnClicked();

private :
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> PurchaseItemWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UNamedSlot* IconSlot;

	UPROPERTY(meta = (BindWidget))
	UButtonText* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButtonText* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LessButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* MoreButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox*	QuantitySelectionBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuantityLabel;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeAnimation;

	int32 Quantity;

public:
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<URPGItem> RPGItem;

	TFunction<void(URPGItem*)> SlotBtnClickCallback;
};
