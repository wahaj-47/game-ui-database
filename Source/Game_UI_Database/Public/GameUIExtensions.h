// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameUIExtensions.generated.h"

enum class ECommonInputType : uint8;

class UUserWidget;
class UCommonActivatableWidget;
class ULocalPlayer;

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

    UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Global UI Extensions")
    static UCommonActivatableWidget *PushContentToLayer_ForPlayer(
        const ULocalPlayer *LocalPlayer, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName,
        UPARAM(meta = (AllowAbstract = false)) TSubclassOf<UCommonActivatableWidget> WidgetClass);
};
