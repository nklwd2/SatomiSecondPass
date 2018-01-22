// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EventPublisherInterface.generated.h"


UINTERFACE()
class PROJECTSATOMI_API UEventPublisherInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROJECTSATOMI_API IEventPublisherInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	template<typename T> void SubscribeToPublisher(FName eventName, FName functionToBind);

//	virtual void SubscribeToPublisherImpl();

	/*virtual void UnsubscribeFromPublisher(FName, functionpointer);*/
};

