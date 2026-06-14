// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace GameUIDatabaseGameplayTags
{
    GAME_UI_DATABASE_API FGameplayTag FindTagByString(const FString &TagString, bool bMatchPartialString = false);

    GAME_UI_DATABASE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Game);
    GAME_UI_DATABASE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_GameMenu);
    GAME_UI_DATABASE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Menu);
    GAME_UI_DATABASE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(UI_Layer_Modal);
} // namespace GameUIDatabaseGameplayTags