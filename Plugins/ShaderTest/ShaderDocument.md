```cpp
//设置环境变量
static inline void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, 
                                                FShaderCompilerEnvironment& OutEnvironment)
{
    FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);

    OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_X"), NUM_THREADS_PER_GROUP_DIMENSION);
    OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_Y"), NUM_THREADS_PER_GROUP_DIMENSION);
    OutEnvironment.SetDefine(TEXT("THREADGROUPSIZE_Z"), 1);
}

//对应的shader
[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)]
void MainComputeShader(uint3 ThreadId : SV_DispatchThreadID)
{
    ...
}
```

