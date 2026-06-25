// Fill out your copyright notice in the Description page of Project Settings.

#include "UIManagerSubsystem.h"

#include "CommonLocalPlayer.h"
#include "Engine/GameInstance.h"
#include "GameFramework/HUD.h"
#include "PrimaryGameLayout.h"
#include "GameUIPolicy.h"

UUIManagerSubsystem::UUIManagerSubsystem() {}

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    Super::Initialize(Collection);
    TickHandle =
        FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UUIManagerSubsystem::Tick), 0.0f);
}

void UUIManagerSubsystem::Deinitialize()
{
    Super::Deinitialize();
    FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UUIManagerSubsystem::Tick(float DeltaTime)
{
    SyncRootLayoutVisibilityToShowHUD();
    return true;
}

void UUIManagerSubsystem::SyncRootLayoutVisibilityToShowHUD()
{
    if (const UGameUIPolicy *Policy = GetCurrentUIPolicy())
    {
        for (const ULocalPlayer *LocalPlayer : GetGameInstance()->GetLocalPlayers())
        {
            bool bShouldShowUI = true;

            if (const APlayerController *PC = LocalPlayer->GetPlayerController(GetWorld()))
            {
                const AHUD *HUD = PC->GetHUD();

                if (HUD && !HUD->bShowHUD)
                {
                    bShouldShowUI = false;
                }
            }

            if (UPrimaryGameLayout *RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(LocalPlayer)))
            {
                const ESlateVisibility DesiredVisibility =
                    bShouldShowUI ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
                if (DesiredVisibility != RootLayout->GetVisibility())
                {
                    RootLayout->SetVisibility(DesiredVisibility);
                }
            }
        }
    }
}