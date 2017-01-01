template< class T >
T EngineApi::Max(const TArray<T>& Values, int32* MaxIndex)
{
	const T MaxValue = FMath::Max<T>(Values, &MaxIndex);
	return MaxValue;
}

template< class T >
T* EngineApi::CreateWidget(UWorld* World, UClass* UserWidgetClass)
{
	return ::CreateWidget<T>(World, UserWidgetClass);
}

template< class T >
T* EngineApi::CreateWidget(APlayerController* OwningPlayer, UClass* UserWidgetClass)
{
	return ::CreateWidget<T>(OwningPlayer, UserWidgetClass);
}

template< class T >
T* EngineApi::CreateWidget(UGameInstance* OwningGame, UClass* UserWidgetClass)
{
	return ::CreateWidget<T>(OwningGame, UserWidgetClass);
}

template<class T>
TSubclassOf<T> EngineApi::FindClass(const TCHAR* ClassToFind)
{
	ConstructorHelpers::FClassFinder<T> findClass(ClassToFind);
	return findClass.Class;
}

template<class T>
T* EngineApi::FindObject(const TCHAR* ObjectToFind)
{
	ConstructorHelpers::FObjectFinder<T> findObject(ObjectToFind);
	return findObject.Object;
}

template< class T >
T* EngineApi::FindObject(UObject* Outer, const TCHAR* Name, bool ExactClass)
{
	return ::FindObject<T>(Outer, Name, ExactClass);
}

template< class T >
T* EngineApi::LoadObject(UObject* Outer, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, UPackageMap* Sandbox)
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
UClass* EngineApi::LoadClass(UObject* Outer, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, UPackageMap* Sandbox)
{
	UClass* LoadedClass = ::LoadClass<T>(Outer, Name, Filename, LoadFlags, Sandbox);
	if (LoadedClass)
	{
		LoadedClass->AddToRoot();
	}
	return LoadedClass;
}

template< class T >
T* EngineApi::DuplicateObject(T const* SourceObject, UObject* Outer, const FName Name)
{
	return ::DuplicateObject(SourceObject, Outer, Namer);
}

template< class T >
T* EngineApi::NewObject(UObject* Outer, UClass* Class, FName Name, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults, FObjectInstancingGraph* InInstanceGraph)
{
	return ::NewObject<T>(Outer, Class, Name, Flags, Template, bCopyTransientsFromClassDefaults, InInstanceGraph);
}

template< class T >
T* EngineApi::NewObject(UObject* Outer)
{
	return ::NewObject<T>(Outer);
}

template< class T >
T* EngineApi::NewObject(UObject* Outer, FName Name, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults, FObjectInstancingGraph* InInstanceGraph)
{
	return ::NewObject<T>(Outer, Name, Flags, Template, bCopyTransientsFromClassDefaults, InInstanceGraph);
}

template< class T >
T* EngineApi::FindSceneActor(const TCHAR* Name)
{
	T* actor = nullptr;
	for (TActorIterator<T> ActorItr(EngineApi::GetWorld()); ActorItr; ++ActorItr)
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
T* EngineApi::FindSceneObject(const TCHAR* Name)
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

double EngineApi::Seconds()
{
	double StartTime = FPlatformTime::Seconds();
	return StartTime;
}

FWorldContext* EngineApi::GetWorldContextFromPIEInstance(const int32 PIEInstance)
{
	FWorldContext* worldContext = GEngine->GetWorldContextFromPIEInstance(PIEInstance);
	return worldContext;
}

UWorld* EngineApi::GetGlobalWorld()
{
	return GWorld;
}

void EngineApi::SetTransientMasterVolume(float size)
{
	UWorld* GameInstanceWorld = EngineApi::GetGlobalWorld();
	if (FAudioDevice* GameInstanceAudioDevice = GameInstanceWorld->GetAudioDevice())
	{
		GameInstanceAudioDevice->SetTransientMasterVolume(0.0f);
	}
}