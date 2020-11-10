
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/TextureRenderTarget2D.h"

#include "TestTextureShaderLibray.generated.h"

UCLASS()
class UTestTextureShaderLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		static void DrawTestTextureShaderRenderTarget(AActor* ContextActor,  //�ܻ�ȡWorld��Actor
			UTextureRenderTarget2D* RenderTarget,  //��ȾĿ��
			FLinearColor LinearColor,          //��ɫ
			UTexture* Texture                  //����
		);

};