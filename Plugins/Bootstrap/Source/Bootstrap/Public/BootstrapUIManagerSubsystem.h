// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUIManagerSubsystem.h"
#include "BootstrapUIManagerSubsystem.generated.h"

class FSubsystemCollectionBase;

/**
 *
 */
UCLASS()
class BOOTSTRAP_API UBootstrapUIManagerSubsystem : public UGameUIManagerSubsystem
{
    GENERATED_BODY()

public:
    UBootstrapUIManagerSubsystem();

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;
    virtual void Deinitialize() override;

private:
    bool Tick(float DeltaTime);
    void SyncRootLayoutVisibilityToShowHUD();

    FTSTicker::FDelegateHandle TickHandle;
};
