#include "ButtonText.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UButtonText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonTextLabel)
	{
		ButtonTextLabel->SetText(ButtonText);
	}

	if (Button)
	{
		Button->SetBackgroundColor(BGColor);
	}
}

void UButtonText::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnReleased.AddDynamic(this, &ThisClass::ButtonReleased);
}

void UButtonText::ButtonReleased()
{
	if (OnButtonClickDelegate.IsBound())
	{
		OnButtonClickDelegate.Broadcast();
	}
}
