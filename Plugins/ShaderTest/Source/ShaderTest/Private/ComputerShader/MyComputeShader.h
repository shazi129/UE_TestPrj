#pragma once

#include "GlobalShader.h"

class FMyComputeShader : public FGlobalShader
{
	DECLARE_SHADER_TYPE(FMyComputeShader, Global);

private:
	FShaderResourceParameter OutputSurface;

public:
	FMyComputeShader() {}
	FMyComputeShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	static bool ShouldCache(EShaderPlatform Platform);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Platform,
		                                       FShaderCompilerEnvironment& OutEnvironment);

	void SetSurfaces(FRHICommandList& RHICmdList, const FComputeShaderRHIRef& ComputeShaderRHIRef, FUnorderedAccessViewRHIRef OutputSurfaceUAV);

	void UnbindBuffers(FRHICommandList& RHICmdList, const FComputeShaderRHIRef& ComputeShaderRHIRef);
};