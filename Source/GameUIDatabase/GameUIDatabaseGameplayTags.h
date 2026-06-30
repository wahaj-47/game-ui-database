// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace GameUIDatabaseGameplayTags
{
    GAMEUIDATABASE_API FGameplayTag FindTagByString(const FString &TagString, bool bMatchPartialString = false);

    GAMEUIDATABASE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Game);
    GAMEUIDATABASE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_GameMenu);
    GAMEUIDATABASE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Menu);
    GAMEUIDATABASE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Modal);
} // namespace GameUIDatabaseGameplayTags