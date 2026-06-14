// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameUIExtensions.generated.h"

enum class ECommonInputType : uint8;

class UUserWidget;

/**
 *
 */
UCLASS()
class GAME_UI_DATABASE_API UGameUIExtensions : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UGameUIExtensions() {};

    UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions",
              meta = (WorldContext = "WidgetContextObject"))
    static ECommonInputType GetOwningPlayerInputType(const UUserWidget *WidgetContextObject);

    UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions",
              meta = (WorldContext = "WidgetContextObject"))
    static bool IsOwningPlayerUsingTouch(const UUserWidget *WidgetContextObject);

    UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions",
              meta = (WorldContext = "WidgetContextObject"))
    static bool IsOwningPlayerUsingGamepad(const UUserWidget *WidgetContextObject);
};
