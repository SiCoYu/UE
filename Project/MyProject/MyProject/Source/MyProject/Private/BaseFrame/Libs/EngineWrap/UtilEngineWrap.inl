#ifndef __UtilEngineWrap_H
#error "UtilEngineWrap.inl file can only include in UtilEngineWrap.h"
#endif

MY_BEGIN_NAMESPACE(MyNS)

template< class T >
T UtilEngineWrap::Max(const TArray<T>& Values, int32* MaxIndex)
{
	const T MaxValue = FMath::Max<T>(Values, &MaxIndex);
	return MaxValue;
}

template< class T >
T* UtilEngineWrap::CreateWidget(UWorld* World, UClass* UserWidgetClass)
{
	return ::CreateWidget<T>(World, UserWidgetClass);
}

template< class T >
T* UtilEngineWrap::CreateWidget(APlayerController* OwningPlayer, UClass* UserWidgetClass)
{
	return ::CreateWidget<T>(OwningPlayer, UserWidgetClass);
}

template< class T >
T* UtilEngineWrap::CreateWidget(UGameInstance* OwningGame, UClass* UserWidgetClass)
{
	return ::CreateWidget<T>(OwningGame, UserWidgetClass);
}

template<class T>
TSubclassOf<T> UtilEngineWrap::FindClass(const TCHAR* ClassToFind)
{
	ConstructorHelpers::FClassFinder<T> findClass(ClassToFind);
	return findClass.Class;
}

template<class T>
T* UtilEngineWrap::FindObject(const TCHAR* ObjectToFind)
{
	ConstructorHelpers::FObjectFinder<T> findObject(ObjectToFind);
	return findObject.Object;
}

template< class T >
T* UtilEngineWrap::FindObject(UObject* Outer, const TCHAR* Name, bool ExactClass)
{
	return ::FindObject<T>(Outer, Name, ExactClass);
}

template< class T >
T* UtilEngineWrap::LoadObject(UObject* Outer, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, UPackageMap* Sandbox)
{
	UClass* Class = T::StaticClass();
	Class->GetDefaultObject(); // force the CDO to be created if it hasn't already
	T* ObjectPtr = ::LoadObject<T>(Outer, Name, Filename, LoadFlags, Sandbox);
	if (ObjectPtr)
	{
		ObjectPtr->AddToRoot();
	}
	return ObjectPtr;
}

template< class T >
UClass* UtilEngineWrap::LoadClass(UObject* Outer, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, UPackageMap* Sandbox)
{
	UClass* LoadedClass = ::LoadClass<T>(Outer, Name, Filename, LoadFlags, Sandbox);
	if (LoadedClass)
	{
		LoadedClass->AddToRoot();
	}
	return LoadedClass;
}

template< class T >
T* UtilEngineWrap::DuplicateObject(T const* SourceObject, UObject* Outer, const FName Name)
{
	return ::DuplicateObject(SourceObject, Outer, Namer);
}

template< class T >
T* UtilEngineWrap::NewObject(UObject* Outer, UClass* Class, FName Name, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults, FObjectInstancingGraph* InInstanceGraph)
{
	return ::NewObject<T>(Outer, Class, Name, Flags, Template, bCopyTransientsFromClassDefaults, InInstanceGraph);
}

template< class T >
T* UtilEngineWrap::NewObject(UObject* Outer)
{
	return ::NewObject<T>(Outer);
}

template< class T >
T* UtilEngineWrap::NewObject(UObject* Outer, FName Name, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults, FObjectInstancingGraph* InInstanceGraph)
{
	return ::NewObject<T>(Outer, Name, Flags, Template, bCopyTransientsFromClassDefaults, InInstanceGraph);
}

template< class T >
T* UtilEngineWrap::FindSceneActor(const TCHAR* Name)
{
	T* actor = nullptr;
	for (TActorIterator<T> ActorItr(UtilEngineWrap::GetWorld()); ActorItr; ++ActorItr)
	{
		actor = *ActorItr;

		if(actor->GetFName() != Name)
		{ 
			actor = nullptr;
		}
		else
		{
			break;
		}
	}

	return actor;
}

template< class T >
T* UtilEngineWrap::FindSceneObject(const TCHAR* Name)
{
	T* retObject = nullptr;

	for (TObjectIterator<T> Itr; Itr; ++Itr)
	{
		retObject = *Itr;

		if (retObject->GetFName() != Name)
		{
			retObject = nullptr;
		}
		else
		{
			break;
		}
	}

	return retObject;
}

template<class T>
T* UtilEngineWrap::FindActor(FString name)
{
	for (TActorIterator<T> It(GetWorld()); It; ++It)
	{
		if (It->GetName() == name)
		{
			T* actor = Cast<T>(*It);
			return actor;
		}
	}

	return nullptr;
}

template<class T>
T* UtilEngineWrap::getComponentByClass(AActor* actor)
{
	T* ret = nullptr;

	if (nullptr != actor)
	{
		ret = actor->FindComponentByClass<T>();
	}

	return ret;
}

MY_END_NAMESPACE