
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/TextureRenderTarget2D.h"

#include "TestTextureShaderLibray.generated.h"


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
class UTestTextureShaderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		static void DrawTestTextureShaderRenderTarget(AActor* ContextActor,  //能获取World的Actor
			UTextureRenderTarget2D* RenderTarget,  //渲染目标
			FTestTextureShaderStructData StructData,          //颜色
			UTexture* Texture                  //纹理
		);

};