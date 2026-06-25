// Fill out your copyright notice in the Description page of Project Settings.

#include "MessagingSubsystem.h"

#include "Game_UI_Database/GameUIDatabaseGameplayTags.h"
#include "Messaging/CommonGameDialog.h"
#include "CommonLocalPlayer.h"
#include "PrimaryGameLayout.h"

void UMessagingSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    Super::Initialize(Collection);

    ConfirmationDialogClassPtr = ConfirmationDialogClass.LoadSynchronous();
    ErrorDialogClassPtr = ErrorDialogClass.LoadSynchronous();
}

void UMessagingSubsystem::ShowConfirmation(UCommonGameDialogDescriptor *DialogDescriptor,
                                           FCommonMessagingResultDelegate ResultCallback)
{
    if (UCommonLocalPlayer *LocalPlayer = GetLocalPlayer<UCommonLocalPlayer>())
    {
        if (UPrimaryGameLayout *RootLayout = LocalPlayer->GetRootUILayout())
        {
            RootLayout->PushWidgetToLayerStack<UCommonGameDialog>(
                GameUIDatabaseGameplayTags::UI_Layer_Modal, ConfirmationDialogClassPtr,
                [DialogDescriptor, ResultCallback](UCommonGameDialog &Dialog)
                { Dialog.SetupDialog(DialogDescriptor, ResultCallback); });
        }
    }
}

void UMessagingSubsystem::ShowError(UCommonGameDialogDescriptor *DialogDescriptor,
                                    FCommonMessagingResultDelegate ResultCallback)
{
    if (UCommonLocalPlayer *LocalPlayer = GetLocalPlayer<UCommonLocalPlayer>())
    {
        if (UPrimaryGameLayout *RootLayout = LocalPlayer->GetRootUILayout())
        {
            RootLayout->PushWidgetToLayerStack<UCommonGameDialog>(
                GameUIDatabaseGameplayTags::UI_Layer_Modal, ErrorDialogClassPtr,
                [DialogDescriptor, ResultCallback](UCommonGameDialog &Dialog)
                { Dialog.SetupDialog(DialogDescriptor, ResultCallback); });
        }
    }
}