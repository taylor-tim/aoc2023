// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logging/StructuredLog.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "HttpHelper.generated.h"

/**
 * 
 */
UCLASS()
class AOC2023_API UHttpHelper final : public UObject
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
	static FString HttpRetriever(FString Url, FString Cookie, FString OutPath = TEXT("")) {
        FString Content = TEXT("default");
        FHttpModule& httpModule = FHttpModule::Get();

        TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = httpModule.CreateRequest();

        pRequest->SetVerb(TEXT("GET"));
        pRequest->SetHeader(TEXT("Content-Type"), TEXT("text/html; charset=utf-8"));
        pRequest->SetHeader(TEXT("Cookie"), FString::Printf(TEXT("session=%s"), *Cookie));
        pRequest->SetURL(Url);

        pRequest->OnProcessRequestComplete().BindLambda(
            [&](
                FHttpRequestPtr pRequest,
                FHttpResponsePtr pResponse,
                bool connectedSuccessfully) mutable {

            if (connectedSuccessfully && pResponse != nullptr) {
                Content = pResponse->GetContentAsString();
                UE_LOG(LogTemp, Warning, TEXT("Got result: %i chars of content"), Content.Len());
                if (OutPath.Len() > 0)
                {
		            FFileHelper::SaveStringToFile(Content, *OutPath);
                }
                // UE_LOG(LogTemp, Warning, TEXT("Got result: %s"), *Result);
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("Connection failed."));
            }
        });

        pRequest->ProcessRequest();
        return Content;
	}

};
