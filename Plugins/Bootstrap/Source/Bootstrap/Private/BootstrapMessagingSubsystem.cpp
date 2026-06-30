// Fill out your copyright notice in the Description page of Project Settings.

#include "BootstrapMessagingSubsystem.h"

#include "NativeGameplayTags.h"
#include "Messaging/CommonGameDialog.h"
#include "CommonLocalPlayer.h"
#include "PrimaryGameLayout.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_UI_LAYER_MODAL, "UI.Layer.Modal");

void UBootstrapMessagingSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    Super::Initialize(Collection);

    ConfirmationDialogClassPtr = ConfirmationDialogClass.LoadSynchronous();
    ErrorDialogClassPtr = ErrorDialogClass.LoadSynchronous();
}

void UBootstrapMessagingSubsystem::ShowConfirmation(UCommonGameDialogDescriptor *DialogDescriptor,
                                                    FCommonMessagingResultDelegate ResultCallback)
{
    if (UCommonLocalPlayer *LocalPlayer = GetLocalPlayer<UCommonLocalPlayer>())
    {
        if (UPrimaryGameLayout *RootLayout = LocalPlayer->GetRootUILayout())
        {
            RootLayout->PushWidgetToLayerStack<UCommonGameDialog>(
                TAG_UI_LAYER_MODAL, ConfirmationDialogClassPtr,
                [DialogDescriptor, ResultCallback](UCommonGameDialog &Dialog)
                { Dialog.SetupDialog(DialogDescriptor, ResultCallback); });
        }
    }
}

void UBootstrapMessagingSubsystem::ShowError(UCommonGameDialogDescriptor *DialogDescriptor,
                                             FCommonMessagingResultDelegate ResultCallback)
{
    if (UCommonLocalPlayer *LocalPlayer = GetLocalPlayer<UCommonLocalPlayer>())
    {
        if (UPrimaryGameLayout *RootLayout = LocalPlayer->GetRootUILayout())
        {
            RootLayout->PushWidgetToLayerStack<UCommonGameDialog>(
                TAG_UI_LAYER_MODAL, ErrorDialogClassPtr, [DialogDescriptor, ResultCallback](UCommonGameDialog &Dialog)
                { Dialog.SetupDialog(DialogDescriptor, ResultCallback); });
        }
    }
}