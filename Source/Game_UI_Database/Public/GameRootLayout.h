// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "GameRootLayout.generated.h"

class UCommonActivatableWidgetContainerBase;

/**
 *
 */
UCLASS(Abstract, meta = (DisableNativeTick))
class GAME_UI_DATABASE_API UGameRootLayout : public UCommonUserWidget
{
    GENERATED_BODY()

public:
    UGameRootLayout(const FObjectInitializer &ObjectInitializer);

    template <typename ActivatableWidgetT = UCommonActivatableWidget>
    ActivatableWidgetT *PushWidgetToLayerStack(FGameplayTag LayerName, UClass *ActivatableWidgetClass)
    {
        return PushWidgetToLayerStack<ActivatableWidgetT>(LayerName, ActivatableWidgetClass,
                                                          [](ActivatableWidgetT &) {});
    }

    template <typename ActivatableWidgetT = UCommonActivatableWidget>
    ActivatableWidgetT *PushWidgetToLayerStack(FGameplayTag LayerName, UClass *ActivatableWidgetClass,
                                               TFunctionRef<void(ActivatableWidgetT &)> InitInstanceFunc)
    {
        static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived,
                      "Only CommonActivatableWidgets can be used here");

        if (UCommonActivatableWidgetContainerBase *Layer = GetLayerWidget(LayerName))
        {
            return Layer->AddWidget<ActivatableWidgetT>(ActivatableWidgetClass, InitInstanceFunc);
        }

        return nullptr;
    }

    UCommonActivatableWidgetContainerBase *GetLayerWidget(FGameplayTag LayerName);

protected:
    UFUNCTION(BlueprintCallable, Category = "Layer")
    void RegisterLayer(UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerTag,
                       UCommonActivatableWidgetContainerBase *LayerWidget);

private:
    UPROPERTY(Transient, meta = (Categories = "UI.Layer"))
    TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> Layers;
};
