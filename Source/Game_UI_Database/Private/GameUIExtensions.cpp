// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUIExtensions.h"

#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "GameRootLayout.h"
#include "GameUIManagerSubsystem.h"

int32 UGameUIExtensions::InputSuspensions = 0;

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

void UGameUIExtensions::PopContentFromLayer(UCommonActivatableWidget *ActivatableWidget)
{
    if (!ActivatableWidget)
    {
        // Ignore request to pop an already deleted widget
        return;
    }

    if (const ULocalPlayer *LocalPlayer = ActivatableWidget->GetOwningLocalPlayer())
    {
        if (const UGameUIManagerSubsystem *UIManager = LocalPlayer->GetSubsystem<UGameUIManagerSubsystem>())
        {
            if (UGameRootLayout *RootLayout = UIManager->GetRootLayout())
            {
                RootLayout->FindAndRemoveWidgetFromLayer(ActivatableWidget);
            }
        }
    }
}

ULocalPlayer *UGameUIExtensions::GetLocalPlayerFromController(APlayerController *PlayerController)
{
    if (PlayerController)
    {
        return Cast<ULocalPlayer>(PlayerController->Player);
    }

    return nullptr;
}

FName UGameUIExtensions::SuspendInputForPlayer(APlayerController *PlayerController, FName SuspendReason)
{
    return SuspendInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendReason);
}

FName UGameUIExtensions::SuspendInputForPlayer(ULocalPlayer *LocalPlayer, FName SuspendReason)
{
    if (UCommonInputSubsystem *CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
    {
        InputSuspensions++;
        FName SuspendToken = SuspendReason;
        SuspendToken.SetNumber(InputSuspensions);

        CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, true);
        CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, true);
        CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, true);

        return SuspendToken;
    }

    return NAME_None;
}

void UGameUIExtensions::ResumeInputForPlayer(APlayerController *PlayerController, FName SuspendToken)
{
    ResumeInputForPlayer(PlayerController ? PlayerController->GetLocalPlayer() : nullptr, SuspendToken);
}

void UGameUIExtensions::ResumeInputForPlayer(ULocalPlayer *LocalPlayer, FName SuspendToken)
{
    if (SuspendToken == NAME_None)
    {
        return;
    }

    if (UCommonInputSubsystem *CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
    {
        CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, false);
        CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, false);
        CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, false);
    }
}