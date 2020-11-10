
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
		static void DrawTestTextureShaderRenderTarget(AActor* ContextActor,  //�ܻ�ȡWorld��Actor
			UTextureRenderTarget2D* RenderTarget,  //��ȾĿ��
			FTestTextureShaderStructData StructData,          //��ɫ
			UTexture* Texture                  //����
		);

};