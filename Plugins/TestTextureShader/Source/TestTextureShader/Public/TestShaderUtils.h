// #ifndef _U_TEST_SHADER_UTILS_
// #define _U_TEST_SHADER_UTILS_

#include "TestShaderUtils.generated.h"

UCLASS()
class UTestShaderUtils : public UObject
{
	GENERATED_BODY()

public:
	static FIndexBufferRHIRef CreateIndexBuffer(const uint16* Indices, uint16 NumIndices);
};

//#endif