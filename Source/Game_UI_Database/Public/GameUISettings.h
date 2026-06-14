// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "GameUISettings.generated.h"

class UGameRootLayout;

/**
 *
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Game UI Settings"))
class GAME_UI_DATABASE_API UGameUISettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "UI")
	TSoftClassPtr<UGameRootLayout> RootLayoutClass;
};
