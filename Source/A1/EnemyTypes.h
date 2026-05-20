#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle        UMETA(DisplayName = "Default"),
	Frozen      UMETA(DisplayName = "Frozen")
};