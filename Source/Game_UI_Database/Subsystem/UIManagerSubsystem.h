// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"
#include "UIManagerSubsystem.generated.h"

class FSubsystemCollectionBase;

/**
 *
 */
UCLASS()
class GAME_UI_DATABASE_API UUIManagerSubsystem : public UGameUIManagerSubsystem
{
    GENERATED_BODY()

public:
    UUIManagerSubsystem();

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;
    virtual void Deinitialize() override;

private:
    bool Tick(float DeltaTime);
    void SyncRootLayoutVisibilityToShowHUD();

    FTSTicker::FDelegateHandle TickHandle;
};
