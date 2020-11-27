#include "TextureShader/TestTextureShader.h"


BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FSimpleUniformStruct, )
SHADER_PARAMETER(FVector4, ColorOne)
SHADER_PARAMETER(FVector4, ColorTwo)
SHADER_PARAMETER(FVector4, ColorThree)
SHADER_PARAMETER(FVector4, ColorFour)
SHADER_PARAMETER(int32, ColorIndex)
END_GLOBAL_SHADER_PARAMETER_STRUCT()
IMPLEMENT_GLOBAL_SHADER_PARAMETER_STRUCT(FSimpleUniformStruct, "SimpleUniformStruct");


FTestTextureShaderPS::FTestTextureShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FMyGlobalShaderBase(Initializer)
{
	MySimpleColor.Bind(Initializer.ParameterMap, TEXT("SampleColor"));
	MyTexture.Bind(Initializer.ParameterMap, TEXT("MyTextrue"));
	MyTextureSampler.Bind(Initializer.ParameterMap, TEXT("MyTextureSampler"));
}

void FTestTextureShaderPS::SetParameter(FRHICommandListImmediate& RHICommandList, FPixelShaderRHIRef pixelShaderRef, const FTestTextureShaderStructData& StructData, FTextureReferenceRHIRef& SimpleTexure)
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

IMPLEMENT_SHADER_TYPE(, FTestTextureShaderVS, TEXT("/Plugin/ShaderTest/Private/TestTextureShader.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FTestTextureShaderPS, TEXT("/Plugin/ShaderTest/Private/TestTextureShader.usf"), TEXT("MainPS"), SF_Pixel);