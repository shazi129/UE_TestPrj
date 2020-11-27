#include "ComputerShader/MyComputeShader.h"

FMyComputeShader::FMyComputeShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
	OutputSurface.Bind(Initializer.ParameterMap, TEXT("OutputSurface"));
}

bool FMyComputeShader::ShouldCache(EShaderPlatform Platform)
{
	return IsFeatureLevelSupported(Platform, ERHIFeatureLevel::SM5);
}

bool FMyComputeShader::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{
	return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5); 
}

void FMyComputeShader::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Platform, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Platform, OutEnvironment);
}

void FMyComputeShader::SetSurfaces(FRHICommandList& RHICmdList, const FComputeShaderRHIRef & ComputeShaderRHIRef, FUnorderedAccessViewRHIRef OutputSurfaceUAV)
{
	if (OutputSurface.IsBound())
		RHICmdList.SetUAVParameter(ComputeShaderRHIRef, OutputSurface.GetBaseIndex(), OutputSurfaceUAV);
}
void FMyComputeShader::UnbindBuffers(FRHICommandList& RHICmdList, const FComputeShaderRHIRef& ComputeShaderRHIRef)
{
	if (OutputSurface.IsBound())
		RHICmdList.SetUAVParameter(ComputeShaderRHIRef, OutputSurface.GetBaseIndex(), FUnorderedAccessViewRHIRef());
}

//IMPLEMENT_SHADER_TYPE(, FMyComputeShader, TEXT("/Plugin/TestTextureShaders/TestComputeShader.usf"), TEXT("MainCS"), SF_Compute);