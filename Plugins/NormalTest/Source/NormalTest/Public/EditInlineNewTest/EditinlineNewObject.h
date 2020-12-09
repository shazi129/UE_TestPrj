#pragma once

#include "EditinlineNewObject.generated.h"

UCLASS(EditInlineNew, BlueprintType, Blueprintable)
class UEditinlineNewObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ObjectName;
};
