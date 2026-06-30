// Copyright Epic Games, Inc. All Rights Reserved.

#include "BootstrapEditor.h"

#include "BootstrapUIManagerSubsystem.h"
#include "BootstrapMessagingSubsystem.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FBootstrapEditorModule"

void FBootstrapEditorModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin
    // file per-module

    if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        ISettingsSectionPtr SettingsMessaging = SettingsModule->RegisterSettings(
            "Project", "Game", "Bootstrap UI Messaging", LOCTEXT("BootstrapUIMessaging", "Bootstrap UI Messaging"),
            LOCTEXT("BootstrapUIMessagingDesc", "Settings for Bootstrap Messaging System"),
            GetMutableDefault<UBootstrapMessagingSubsystem>());
        if (SettingsMessaging.IsValid())
            GetMutableDefault<UBootstrapMessagingSubsystem>()->SaveConfig();

        ISettingsSectionPtr SettingsManager = SettingsModule->RegisterSettings(
            "Project", "Game", "Bootstrap UI Manager", LOCTEXT("BootstrapUIManager", "Bootstrap UI Manager"),
            LOCTEXT("BootstrapUIManagerDesc", "Settings for Bootstrap UI Manager"),
            GetMutableDefault<UBootstrapUIManagerSubsystem>());
        if (SettingsManager.IsValid())
            GetMutableDefault<UBootstrapUIManagerSubsystem>()->SaveConfig();
    }
}

void FBootstrapEditorModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.

    if (ISettingsModule *SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "Bootstrap UI Messaging");
        SettingsModule->UnregisterSettings("Project", "Plugins", "Bootstrap UI Manager");
    }
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FBootstrapEditorModule, BootstrapEditor);
