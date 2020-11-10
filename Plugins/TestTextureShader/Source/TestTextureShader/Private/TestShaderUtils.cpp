#include "TestShaderUtils.h"

FIndexBufferRHIRef UTestShaderUtils::CreateIndexBuffer(const uint16* Indices, uint16 NumIndices)
{
	TResourceArray<uint16, INDEXBUFFER_ALIGNMENT> IndexBuffer;

	IndexBuffer.AddUninitialized(NumIndices);
	FMemory::Memcpy(IndexBuffer.GetData(), Indices, NumIndices * sizeof(uint16));

	// Create index buffer. Fill buffer with initial data upon creation
	FRHIResourceCreateInfo CreateInfo(&IndexBuffer);
	FIndexBufferRHIRef IndexBufferRHI = RHICreateIndexBuffer(sizeof(uint16), IndexBuffer.GetResourceDataSize(), BUF_Static, CreateInfo);

	return IndexBufferRHI;
}