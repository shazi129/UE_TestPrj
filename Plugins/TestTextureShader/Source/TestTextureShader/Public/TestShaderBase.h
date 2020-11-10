#ifndef _F_TEST_SHADER_BASE_H_
#define _F_TEST_SHADER_BASE_H_

#include "GlobalShader.h"

static FIndexBufferRHIRef CreateIndexBuffer(const uint16* Indices, uint16 NumIndices);

class FTestShaderBase : public FGlobalShader
{

public:
	FTestShaderBase();

	FTestShaderBase(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	static bool ShouldCache(EShaderPlatform Platform);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
		FShaderCompilerEnvironment& OutEnvironment);
};

#endif