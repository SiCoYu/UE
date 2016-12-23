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
T* EngineApi::MDuplicateObject(T const* SourceObject, UObject* Outer, const FName Name)
{
	return DuplicateObject(SourceObject, Outer, Namer);
}