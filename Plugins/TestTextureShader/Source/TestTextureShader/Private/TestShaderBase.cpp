#include "TestShaderBase.h"

FTestShaderBase::FTestShaderBase() {}

FTestShaderBase::FTestShaderBase(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
}

bool FTestShaderBase::ShouldCache(EShaderPlatform Platform)
{
	return true;
}

bool FTestShaderBase::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{ 
	return true;
}

void FTestShaderBase::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
	OutEnvironment.SetDefine(TEXT("TEST_MICRO"), 1);
}