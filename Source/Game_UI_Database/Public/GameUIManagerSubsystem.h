// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"

#include "GameUIManagerSubsystem.generated.h"

class UGameRootLayout;

/**
 *
 */
UCLASS()
class GAME_UI_DATABASE_API UGameUIManagerSubsystem : public ULocalPlayerSubsystem
{
    GENERATED_BODY()

public:
    UGameUIManagerSubsystem() {};

    virtual void PlayerControllerChanged(APlayerController *NewPlayerController) override;
    UGameRootLayout *GetRootLayout() const { return RootLayout; }

private:
    TSubclassOf<UGameRootLayout> GetLayoutWidgetClass();

    UPROPERTY(Transient)
    TObjectPtr<UGameRootLayout> RootLayout = nullptr;
};
