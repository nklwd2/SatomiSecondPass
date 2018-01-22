// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "PSEventAggregator.generated.h"
#pragma once


USTRUCT()
struct FGameFrameworkEvent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FName eventName;
};

USTRUCT()
struct FGameFrameworkEventSubscription : public FGameFrameworkEvent
{

	GENERATED_USTRUCT_BODY()
	
	FName functionName;

	//FunctionPtrType
	//TMemFunPtrType<true, UserClass, void(ParamTypes..., VarTypes...)>::Type InFunc eventstuffDelegate;
	//TBaseDynamicDelegate<FWeakObjectPtr, RetValType, ParamTypes...> eventDelegate;
};

USTRUCT()
struct FGameFrameworkEventPublication : public FGameFrameworkEvent
{

	GENERATED_USTRUCT_BODY()
	//FMulticastDelegateBase  eventMulticastDelegate;
};

USTRUCT()
struct FGameFrameworkEventNotification : public FGameFrameworkEvent
{

	GENERATED_USTRUCT_BODY()
};