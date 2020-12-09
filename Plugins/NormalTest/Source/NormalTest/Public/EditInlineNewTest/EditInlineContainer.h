#pragma once

#include "EditinlineNewObject.h"
#include "EditInlineContainer.generated.h"

UCLASS()
class AEditInlineContainer : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UEditinlineNewObject*> ObjectList;
};