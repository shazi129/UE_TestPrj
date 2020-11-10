
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
		static void DrawTestTextureShaderRenderTarget(AActor* ContextActor,  //能获取World的Actor
			UTextureRenderTarget2D* RenderTarget,  //渲染目标
			FLinearColor LinearColor,          //颜色
			UTexture* Texture                  //纹理
		);

};