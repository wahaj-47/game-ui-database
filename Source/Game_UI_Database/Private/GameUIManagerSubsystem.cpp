// Fill out your copyright notice in the Description page of Project Settings.

#include "GameUIManagerSubsystem.h"
#include "GameRootLayout.h"
#include "GameUISettings.h"
#include "Engine/LocalPlayer.h"

void UGameUIManagerSubsystem::PlayerControllerChanged(APlayerController *NewPlayerController)
{
    Super::PlayerControllerChanged(NewPlayerController);

    UE_LOG(LogTemp, Warning, TEXT("PlayerControllerChanged: %s"), *GetNameSafe(NewPlayerController));

    TSubclassOf<UGameRootLayout> LayoutClass = GetLayoutWidgetClass();
    if (ensure(LayoutClass && !LayoutClass->HasAnyClassFlags(CLASS_Abstract)))
    {
        UE_LOG(LogTemp, Warning, TEXT("Creating Root Layout"));
        RootLayout = CreateWidget<UGameRootLayout>(NewPlayerController, LayoutClass);
        UE_LOG(LogTemp, Warning, TEXT("Adding Root Layout To Screen"));
        RootLayout->AddToPlayerScreen(1000);
    }
}

TSubclassOf<UGameRootLayout> UGameUIManagerSubsystem::GetLayoutWidgetClass()
{
    const UGameUISettings *Settings = GetDefault<UGameUISettings>();
    return Settings->RootLayoutClass.LoadSynchronous();
}
