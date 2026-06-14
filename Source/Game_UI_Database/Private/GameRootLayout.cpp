// Fill out your copyright notice in the Description page of Project Settings.

#include "GameRootLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UGameRootLayout::UGameRootLayout(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {}

void UGameRootLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase *LayerWidget)
{
    if (!IsDesignTime())
    {
        /**
         * Transition duration is set to 0 to avoid transitions when the widget is added to the layer.
         * Because if it's not 0, the transition effect will cause focus to not transition properly to
         * the new widgets when using gamepad always.
         */
        LayerWidget->SetTransitionDuration(0.0);
        Layers.Add(LayerTag, LayerWidget);
    }
}

void UGameRootLayout::FindAndRemoveWidgetFromLayer(UCommonActivatableWidget *ActivatableWidget)
{
    // We're not sure what layer the widget is on so go searching.
    for (const auto &LayerKVP : Layers)
    {
        LayerKVP.Value->RemoveWidget(*ActivatableWidget);
    }
}

UCommonActivatableWidgetContainerBase *UGameRootLayout::GetLayerWidget(FGameplayTag LayerName)
{
    return Layers.FindRef(LayerName);
}