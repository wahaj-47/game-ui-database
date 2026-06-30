#pragma once

#include "Modules/ModuleManager.h"

class FBootstrapEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};