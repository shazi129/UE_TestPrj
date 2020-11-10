
#include "TestTextureShaderLibray.h"
#include "TestShaderBase.h"
#include "RHIStaticStates.h"
#include "TestShaderUtils.h"


BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FSimpleUniformStruct, )
SHADER_PARAMETER(FVector4, ColorOne)
SHADER_PARAMETER(FVector4, ColorTwo)
SHADER_PARAMETER(FVector4, ColorThree)
SHADER_PARAMETER(FVector4, ColorFour)
SHADER_PARAMETER(int32, ColorIndex)
END_GLOBAL_SHADER_PARAMETER_STRUCT()
IMPLEMENT_GLOBAL_SHADER_PARAMETER_STRUCT(FSimpleUniformStruct, "SimpleUniformStruct");


class FTestTextureShaderVS : public FTestShaderBase
{
	DECLARE_SHADER_TYPE(FTestTextureShaderVS, Global);



public:
	FTestTextureShaderVS() {}

	FTestTextureShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FTestShaderBase(Initializer)
	{
		
	}

};

class FTestTextureShaderPS : public FTestShaderBase
{
	DECLARE_SHADER_TYPE(FTestTextureShaderPS, Global);

private:
	LAYOUT_FIELD(FShaderParameter, MySimpleColor);
	LAYOUT_FIELD(FShaderResourceParameter, MyTexture);
	LAYOUT_FIELD(FShaderResourceParameter, MyTextureSampler);

public:
	FTestTextureShaderPS() {}

	FTestTextureShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FTestShaderBase(Initializer)
	{
		MySimpleColor.Bind(Initializer.ParameterMap, TEXT("SampleColor"));
		MyTexture.Bind(Initializer.ParameterMap, TEXT("MyTextrue"));
		MyTextureSampler.Bind(Initializer.ParameterMap, TEXT("MyTextureSampler"));
	}

	void SetParameter(FRHICommandListImmediate& RHICommandList, FPixelShaderRHIRef pixelShaderRef, const FTestTextureShaderStructData& StructData, FTextureReferenceRHIRef& SimpleTexure)
	{
		//SetShaderValue(RHICommandList, pixelShaderRef, MySimpleColor, SimpleColor);

		FSimpleUniformStruct ShaderStructData;
		ShaderStructData.ColorOne = StructData.ColorOne;
		ShaderStructData.ColorTwo = StructData.ColorTwo;
		ShaderStructData.ColorThree = StructData.ColorThree;
		ShaderStructData.ColorFour = StructData.ColorFour;
		ShaderStructData.ColorIndex = StructData.ColorIndex;

		SetUniformBufferParameterImmediate(RHICommandList, pixelShaderRef, GetUniformBufferParameter<FSimpleUniformStruct>(), ShaderStructData);

		SetTextureParameter(RHICommandList, pixelShaderRef.GetReference(), MyTexture,
			MyTextureSampler, TStaticSamplerState<SF_Trilinear, AM_Clamp, AM_Clamp, AM_Clamp>::GetRHI(),
			SimpleTexure);
	}

};

IMPLEMENT_SHADER_TYPE(, FTestTextureShaderVS, TEXT("/Plugin/TestTextureShaders/TestTextureShader.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FTestTextureShaderPS, TEXT("/Plugin/TestTextureShaders/TestTextureShader.usf"), TEXT("MainPS"), SF_Pixel);

struct FMyTextureVertex
{
	FVector4 Position;
	FVector2D UV;
};

class FMyTextureVertexDeclaration : public FRenderResource
{
public:
	FVertexDeclarationRHIRef VertexDeclarationRHI;

	virtual void InitRHI() override
	{
		FVertexDeclarationElementList Elements;
		uint32 Stride = sizeof(FMyTextureVertex);
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FMyTextureVertex, Position), VET_Float4, 0, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FMyTextureVertex, UV), VET_Float2, 1, Stride));
		VertexDeclarationRHI = RHICreateVertexDeclaration(Elements);
	}

	virtual void ReleaseRHI() override
	{
		VertexDeclarationRHI.SafeRelease();
	}
};

static FVertexBufferRHIRef CreateVertexBuffer()
{
	TResourceArray<FMyTextureVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
	Vertices.SetNumUninitialized(4);

	Vertices[0].Position = FVector4(1, 1, 0, 1);
	Vertices[0].UV = FVector2D(1, 1);

	Vertices[1].Position = FVector4(-1, 1, 0, 1);
	Vertices[1].UV = FVector2D(0, 1);

	Vertices[2].Position = FVector4(1, -1, 0, 1);
	Vertices[2].UV = FVector2D(1, 0);

	Vertices[3].Position = FVector4(-1, -1, 0, 1);
	Vertices[3].UV = FVector2D(0, 0);

	// Create vertex buffer. Fill buffer with initial data upon creation
	FRHIResourceCreateInfo CreateInfo(&Vertices);
	FVertexBufferRHIRef VertexBufferRHI = RHICreateVertexBuffer(Vertices.GetResourceDataSize(), BUF_Static, CreateInfo);

	return VertexBufferRHI;
}


static void DrawTestTextureShaderRenderTarget_RenderThread(
	FRHICommandListImmediate& RHICmdList,
	FTextureRenderTargetResource* OutTextureRenderTargetResource,
	ERHIFeatureLevel::Type FeatureLevel,
	FName RenderTargetName,
	FTestTextureShaderStructData StructData,
	FTextureReferenceRHIRef TextureReferenceRHI)
{
	check(IsInRenderingThread());

#if WANTS_DRAW_MESH_EVENTS  
	FString EventName;
	RenderTargetName.ToString(EventName);
	SCOPED_DRAW_EVENTF(RHICmdList, SceneCapture, TEXT("DrawTestShader %s"), *EventName);
#else  
	SCOPED_DRAW_EVENT(RHICmdList, DrawUVDisplacementToRenderTarget_RenderThread);
#endif

	FRHITexture2D* RenderTargetTexture = OutTextureRenderTargetResource->GetRenderTargetTexture();

	FRHIRenderPassInfo RPInfo(RenderTargetTexture, ERenderTargetActions::DontLoad_Store, OutTextureRenderTargetResource->TextureRHI);
	RHICmdList.BeginRenderPass(RPInfo, TEXT("DrawTestShader"));


	FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
	TShaderMapRef<FTestTextureShaderVS> VertexShader(GlobalShaderMap);
	TShaderMapRef<FTestTextureShaderPS> PixelShader(GlobalShaderMap);

	FMyTextureVertexDeclaration VertexDec;
	VertexDec.InitRHI();

	// Set the graphic pipeline state.  
	FGraphicsPipelineStateInitializer GraphicsPSOInit;
	RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
	GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
	GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
	GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
	GraphicsPSOInit.PrimitiveType = PT_TriangleList;
	GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = VertexDec.VertexDeclarationRHI;
	GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
	GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
	SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

	//设置视口  
	FIntPoint DrawTargetResolution(OutTextureRenderTargetResource->GetSizeX(), OutTextureRenderTargetResource->GetSizeY());
	RHICmdList.SetViewport(0, 0, 0.0f, DrawTargetResolution.X, DrawTargetResolution.Y, 1.0f);

	//shader参数
	PixelShader->SetParameter(RHICmdList, PixelShader.GetPixelShader(), StructData, TextureReferenceRHI);

	//定点信息
	FVertexBufferRHIRef VertexBufferRHI = CreateVertexBuffer();
	const uint16 Indices[] = { 0, 1, 2, 2, 1, 3 };
	FIndexBufferRHIRef IndexBufferRHI = UTestShaderUtils::CreateIndexBuffer(Indices, 6);

	RHICmdList.SetStreamSource(0, VertexBufferRHI, 0);
	RHICmdList.DrawIndexedPrimitive(IndexBufferRHI, 0, 0, 4, 0, 2, 1);


	RHICmdList.EndRenderPass();
}

void UTestTextureShaderLibrary::DrawTestTextureShaderRenderTarget(AActor* ContextActor,  //能获取World的Actor
	UTextureRenderTarget2D* RenderTarget,  //渲染目标
	FTestTextureShaderStructData StructData,          //颜色
	UTexture* Texture                  //纹理
)
{
	check(IsInGameThread());

	if (!RenderTarget || !ContextActor)
	{
		return;
	}

	FTextureRenderTargetResource* TextureRenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
	FTextureReferenceRHIRef TextureReferenceRHI = Texture->TextureReference.TextureReferenceRHI;

	UWorld* World = ContextActor->GetWorld();
	ERHIFeatureLevel::Type RHIFeatureLevel = World->Scene->GetFeatureLevel();

	FName RenderTargetName = RenderTarget->GetFName();

	ENQUEUE_RENDER_COMMAND(CaptureCommand)(
		[TextureRenderTargetResource, RHIFeatureLevel, StructData, RenderTargetName, TextureReferenceRHI]
	    (FRHICommandListImmediate& RHICmdList)
		{
			DrawTestTextureShaderRenderTarget_RenderThread(
				RHICmdList,
				TextureRenderTargetResource,
				RHIFeatureLevel,
				RenderTargetName,
				StructData,
				TextureReferenceRHI);
		}
	);
}

