// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Messaging/CommonMessagingSubsystem.h"
#include "BootstrapMessagingSubsystem.generated.h"

class FSubsystemCollectionBase;
class UCommonGameDialog;
class UCommonGameDialogDescriptor;

/**
 *
 */
UCLASS()
class BOOTSTRAP_API UBootstrapMessagingSubsystem : public UCommonMessagingSubsystem
{
    GENERATED_BODY()

public:
    UBootstrapMessagingSubsystem() {}

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void
    ShowConfirmation(UCommonGameDialogDescriptor *DialogDescriptor,
                     FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate()) override;
    virtual void ShowError(UCommonGameDialogDescriptor *DialogDescriptor,
                           FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate()) override;

private:
    UPROPERTY()
    TSubclassOf<UCommonGameDialog> ConfirmationDialogClassPtr;

    UPROPERTY()
    TSubclassOf<UCommonGameDialog> ErrorDialogClassPtr;

    UPROPERTY(config, EditAnywhere)
    TSoftClassPtr<UCommonGameDialog> ConfirmationDialogClass;

    UPROPERTY(config, EditAnywhere)
    TSoftClassPtr<UCommonGameDialog> ErrorDialogClass;
};
