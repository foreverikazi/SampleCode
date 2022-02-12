// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonText.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnButtonClick);

class UButton;
class UTextBlock;

UCLASS()
class ACTIONRPG_API UButtonText : public UUserWidget
{
	GENERATED_BODY()
	
public :
	FOnButtonClick& OnButtonClick() { return OnButtonClickDelegate; }

private:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ButtonReleased();

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonTextLabel;

	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	FOnButtonClick OnButtonClickDelegate;

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText ButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	FLinearColor BGColor;
};
