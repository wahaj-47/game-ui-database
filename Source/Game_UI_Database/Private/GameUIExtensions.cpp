// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUIExtensions.h"

#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "GameRootLayout.h"
#include "GameUIManagerSubsystem.h"

ECommonInputType UGameUIExtensions::GetOwningPlayerInputType(const UUserWidget *WidgetContextObject)
{
    if (WidgetContextObject)
    {
        if (const UCommonInputSubsystem *InputSubsystem =
                UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
        {
            return InputSubsystem->GetCurrentInputType();
        }
    }

    return ECommonInputType::Count;
}

bool UGameUIExtensions::IsOwningPlayerUsingTouch(const UUserWidget *WidgetContextObject)
{
    if (WidgetContextObject)
    {
        if (const UCommonInputSubsystem *InputSubsystem =
                UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
        {
            return InputSubsystem->GetCurrentInputType() == ECommonInputType::Touch;
        }
    }
    return false;
}

bool UGameUIExtensions::IsOwningPlayerUsingGamepad(const UUserWidget *WidgetContextObject)
{
    if (WidgetContextObject)
    {
        if (const UCommonInputSubsystem *InputSubsystem =
                UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
        {
            return InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad;
        }
    }
    return false;
}

UCommonActivatableWidget *
UGameUIExtensions::PushContentToLayer_ForPlayer(const ULocalPlayer *LocalPlayer, FGameplayTag LayerName,
                                                TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    if (!ensure(LocalPlayer) || !ensure(WidgetClass != nullptr))
    {
        return nullptr;
    }

    if (UGameUIManagerSubsystem *UIManager = LocalPlayer->GetSubsystem<UGameUIManagerSubsystem>())
    {
        if (UGameRootLayout *RootLayout = UIManager->GetRootLayout())
        {
            return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
        }
    }

    return nullptr;
}