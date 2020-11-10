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

FIndexBufferRHIRef CreateIndexBuffer(const uint16* Indices, uint16 NumIndices)
{
	TResourceArray<uint16, INDEXBUFFER_ALIGNMENT> IndexBuffer;

	IndexBuffer.AddUninitialized(NumIndices);
	FMemory::Memcpy(IndexBuffer.GetData(), Indices, NumIndices * sizeof(uint16));

	// Create index buffer. Fill buffer with initial data upon creation
	FRHIResourceCreateInfo CreateInfo(&IndexBuffer);
	FIndexBufferRHIRef IndexBufferRHI = RHICreateIndexBuffer(sizeof(uint16), IndexBuffer.GetResourceDataSize(), BUF_Static, CreateInfo);

	return IndexBufferRHI;
}