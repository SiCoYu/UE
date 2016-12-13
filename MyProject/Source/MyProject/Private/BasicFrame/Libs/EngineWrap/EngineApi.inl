template< class T >
T* EngineApi::CreateWidget(UWorld* World, UClass* UserWidgetClass)
{
	return CreateWidget(World, UserWidgetClass);
}

template< class T >
T* EngineApi::CreateWidget(APlayerController* OwningPlayer, UClass* UserWidgetClass)
{
	return CreateWidget(OwningPlayer, UserWidgetClass);
}

template< class T >
T* EngineApi::CreateWidget(UGameInstance* OwningGame, UClass* UserWidgetClass)
{
	return CreateWidget(OwningGame, UserWidgetClass);
}