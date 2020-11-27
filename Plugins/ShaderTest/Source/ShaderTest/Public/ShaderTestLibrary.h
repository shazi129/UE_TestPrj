#pragma once

/**
*   �����ⲿ�ӿ�  
*/

#include "Common/TestShaderUtils.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShaderTestLibrary.generated.h"

USTRUCT(BlueprintType)
struct FTestTextureShaderStructData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor ColorOne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor ColorTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor ColorThree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor ColorFour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ColorIndex;
};

UCLASS()
class UShaderTestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ShaderTestPlugin")
		static void FirstShaderDrawRenderTarget(UTextureRenderTarget2D* OutputRenderTarget, AActor* Ac, FLinearColor MyColor);

	UFUNCTION(BlueprintCallable, Category = "ShaderTestPlugin")
		static void DrawTestTextureShaderRenderTarget(AActor* ContextActor,  //�ܻ�ȡWorld��Actor
			UTextureRenderTarget2D* RenderTarget,  //��ȾĿ��
			FTestTextureShaderStructData StructData,          //��ɫ
			UTexture* Texture                  //����
		);
};
