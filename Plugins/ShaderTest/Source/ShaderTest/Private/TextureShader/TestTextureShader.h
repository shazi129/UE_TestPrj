#pragma once

#include "RHICommandList.h"
#include "Common/MyShaderTypes.h"
#include "Common/TestShaderUtils.h"
#include "Common/MyGlobalShaderBase.h"

class FTestTextureShaderVS : public FMyGlobalShaderBase
{
	DECLARE_SHADER_TYPE(FTestTextureShaderVS, Global);



public:
	FTestTextureShaderVS() {}

	FTestTextureShaderVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FMyGlobalShaderBase(Initializer)
	{

	}

};

class FTestTextureShaderPS : public FMyGlobalShaderBase
{
	DECLARE_SHADER_TYPE(FTestTextureShaderPS, Global);

private:
	LAYOUT_FIELD(FShaderParameter, MySimpleColor);
	LAYOUT_FIELD(FShaderResourceParameter, MyTexture);
	LAYOUT_FIELD(FShaderResourceParameter, MyTextureSampler);

public:
	FTestTextureShaderPS() {}

	FTestTextureShaderPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	void SetParameter(FRHICommandListImmediate& RHICommandList, FPixelShaderRHIRef pixelShaderRef, const FTestTextureShaderStructData& StructData, FTextureReferenceRHIRef& SimpleTexure);

};