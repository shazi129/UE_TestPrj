#include "Common/MyGlobalShaderBase.h"

FMyGlobalShaderBase::FMyGlobalShaderBase() {}

FMyGlobalShaderBase::FMyGlobalShaderBase(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
}

bool FMyGlobalShaderBase::ShouldCache(EShaderPlatform Platform)
{
	return true;
}

bool FMyGlobalShaderBase::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{ 
	return true;
}

void FMyGlobalShaderBase::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
	OutEnvironment.SetDefine(TEXT("TEST_MICRO"), 1);
}