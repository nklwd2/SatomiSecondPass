#include "ProjectSatomi.h"
#include "EventPublisherInterface.h"

UEventPublisherInterface::UEventPublisherInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 
}
 
//This is required for compiling, would also let you know if somehow you called
//the base event/function rather than the over-rided version
/*FString IToStringInterface::ToString()
{
	return "IToStringInterface::ToString()";
}*/

template<typename T>
void IEventPublisherInterface::SubscribeToPublisher(FName eventName, FName functionToBind){
	
}