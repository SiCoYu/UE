template< class T >
extern T* CreateWidget(UWorld* World, UClass* UserWidgetClass);

template< class T >
T* EngineApi::MCreateWidget(UWorld* World, UClass* UserWidgetClass)
{
	return CreateWidget<T>(World, UserWidgetClass);
}

template< class T >
extern T* CreateWidget(APlayerController* OwningPlayer, UClass* UserWidgetClass);

template< class T >
T* EngineApi::MCreateWidget(APlayerController* OwningPlayer, UClass* UserWidgetClass)
{
	return CreateWidget<T>(OwningPlayer, UserWidgetClass);
}

template< class T >
extern T* CreateWidget(UGameInstance* OwningGame, UClass* UserWidgetClass);

template< class T >
T* EngineApi::MCreateWidget(UGameInstance* OwningGame, UClass* UserWidgetClass)
{
	return CreateWidget<T>(OwningGame, UserWidgetClass);
}

template<class T>
TSubclassOf<T> EngineApi::MFindClass(const TCHAR* ClassToFind)
{
	ConstructorHelpers::FClassFinder<T> findClass(ClassToFind);
	return findClass.Class;
}

template<class T>
T* EngineApi::MFindObject(const TCHAR* ObjectToFind)
{
	ConstructorHelpers::FObjectFinder<T> findObject(ObjectToFind);
	return findObject.Object;
}

template< class T >
T* EngineApi::MFindObject(UObject* Outer, const TCHAR* Name, bool ExactClass)
{
	return FindObject<T>(Outer, Name, ExactClass);
}

template< class T >
T* EngineApi::MDuplicateObject(T const* SourceObject, UObject* Outer, const FName Name)
{
	return DuplicateObject(SourceObject, Outer, Namer);
}

template< class T >
T* EngineApi::MNewObject(UObject* Outer, UClass* Class, FName Name, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults, FObjectInstancingGraph* InInstanceGraph)
{
	return NewObject<T>(Outer, Class, Name, Flags, Template, bCopyTransientsFromClassDefaults, InInstanceGraph);
}

template< class T >
T* EngineApi::MNewObject(UObject* Outer)
{
	return NewObject<T>(Outer);
}

template< class T >
T* EngineApi::MNewObject(UObject* Outer, FName Name, EObjectFlags Flags, UObject* Template, bool bCopyTransientsFromClassDefaults, FObjectInstancingGraph* InInstanceGraph)
{
	return NewObject<T>(Outer, Name, Flags, Template, bCopyTransientsFromClassDefaults, InInstanceGraph);
}