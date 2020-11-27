// #include "TestComputeShaderLibray.h"
// #include "MyComputeShader.h"
// 
// static void UseComputeShader_RenderThread(
// 	FRHICommandListImmediate& RHICmdList,
// 	FTextureRenderTargetResource* OutputRenderTargetResource,
// 	ERHIFeatureLevel::Type FeatureLevel
// )
// {
// 	check(IsInRenderingThread());
// 
// 	TShaderMapRef<FMyComputeShader> ComputeShader(GetGlobalShaderMap(FeatureLevel));
// 	RHICmdList.SetComputeShader(ComputeShader.GetComputeShader());
// 
// 	//ComputeShader->SetSurfaces(RHICmdList,)  
// 	int32 SizeX = OutputRenderTargetResource->GetSizeX();
// 	int32 SizeY = OutputRenderTargetResource->GetSizeY();
// 	FRHIResourceCreateInfo CreateInfo;
// 	FTexture2DRHIRef Texture = RHICreateTexture2D(SizeX, SizeY, PF_R32_UINT, 1, 1, TexCreate_ShaderResource | TexCreate_UAV, CreateInfo);
// 	//OutputRenderTargetResource->UA  
// 	FUnorderedAccessViewRHIRef TextureUAV = RHICreateUnorderedAccessView(Texture);
// 	ComputeShader->SetSurfaces(RHICmdList, ComputeShader.GetComputeShader(), TextureUAV);
// 
// 	DispatchComputeShader(RHICmdList, ComputeShader, SizeX / 32, SizeY / 32, 1);
// 
// 
// 	//FLinearColor Color = FLinearColor::White;  
// 	//FMyShaderStructData data;  
// 	//data.ColorOne = FLinearColor::White;  
// 	//data.ColorTwo = FLinearColor::White;  
// 	//data.Colorthree = FLinearColor::White;  
// 	//data.ColorFour = FLinearColor::White;  
// 	//DrawTestShaderRenderTarget_RenderThread(RHICmdList, OutputRenderTargetResource, FeatureLevel, Color, Texture, data);  
// 
// 	ComputeShader->UnbindBuffers(RHICmdList, ComputeShader.GetComputeShader());
// 
// 	//OutputRenderTargetResource->TextureRHI = Texture;  
// 
// 
// 	//create a bitmap  
// 	TArray<FColor> Bitmap;
// 
// 	//To access our resource we do a custom read using lockrect  
// 	uint32 LolStride = 0;
// 	char* TextureDataPtr = (char*)RHICmdList.LockTexture2D(Texture, 0, EResourceLockMode::RLM_ReadOnly, LolStride, false);
// 
// 	for (uint32 Row = 0; Row < Texture->GetSizeY(); ++Row)
// 	{
// 		uint32* PixelPtr = (uint32*)TextureDataPtr;
// 
// 		//Since we are using our custom UINT format, we need to unpack it here to access the actual colors  
// 		for (uint32 Col = 0; Col < Texture->GetSizeX(); ++Col)
// 		{
// 			uint32 EncodedPixel = *PixelPtr;
// 			uint8 r = (EncodedPixel & 0x000000FF);
// 			uint8 g = (EncodedPixel & 0x0000FF00) >> 8;
// 			uint8 b = (EncodedPixel & 0x00FF0000) >> 16;
// 			uint8 a = (EncodedPixel & 0xFF000000) >> 24;
// 			Bitmap.Add(FColor(r, g, b, a));
// 
// 			PixelPtr++;
// 		}
// 
// 		// move to next row:  
// 		TextureDataPtr += LolStride;
// 	}
// 
// 	RHICmdList.UnlockTexture2D(Texture, 0, false);
// 
// 	// if the format and texture type is supported  
// 	if (Bitmap.Num())
// 	{
// 		// Create screenshot folder if not already present.  
// 		IFileManager::Get().MakeDirectory(*FPaths::ScreenShotDir(), true);
// 
// 		const FString ScreenFileName(FPaths::ScreenShotDir() / TEXT("VisualizeTexture"));
// 
// 		uint32 ExtendXWithMSAA = Bitmap.Num() / Texture->GetSizeY();
// 
// 		// Save the contents of the array to a bitmap file. (24bit only so alpha channel is dropped)  
// 		FFileHelper::CreateBitmap(*ScreenFileName, ExtendXWithMSAA, Texture->GetSizeY(), Bitmap.GetData());
// 
// 		UE_LOG(LogConsoleResponse, Display, TEXT("Content was saved to \"%s\""), *FPaths::ScreenShotDir());
// 	}
// 	else
// 	{
// 		UE_LOG(LogConsoleResponse, Error, TEXT("Failed to save BMP, format or texture type is not supported"));
// 	}
// 
// 
// }
// 
// void UTestComputeShaderLibrary::DrawTestComputeShaderRenderTarget(
// 	AActor* ContextActor,  //能获取World的Actor
// 	UTextureRenderTarget2D* RenderTarget  //渲染目标
// )
// {
// // 	check(IsInGameThread());
// // 
// // 	if (!RenderTarget)
// // 	{
// // 		return;
// // 	}
// // 
// // 	FTextureRenderTargetResource* TextureRenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
// // 	ERHIFeatureLevel::Type FeatureLevel = ContextActor->GetWorld()->Scene->GetFeatureLevel();
// // 
// // 	ENQUEUE_RENDER_COMMAND(CaptureCommand)
// // 		(
// // 			[TextureRenderTargetResource, FeatureLevel](FRHICommandListImmediate& RHICmdList)
// // 			{
// // 				UseComputeShader_RenderThread
// // 				(
// // 					RHICmdList,
// // 					TextureRenderTargetResource,
// // 					FeatureLevel
// // 				);
// // 			}
// // 	);
// }