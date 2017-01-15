#pragma once

#include "GameFramework/SaveGame.h"		// USaveGame
#include "MySaveGame.generated.h"

/**
 * @brief 持久化保存
 * @ref http://www.yangqiu.cn/gh_e7524b8b5862/1479653.html
 * SaveGame
 UE连玩家存档都帮你做了！得益于UObject的序列化机制，现在你只需要继承于USaveGame，并添加你想要的那些属性字段，然后这个结构就可以序列化保存下来的。玩家存档也是游戏中一个非常常见的功能，差的引擎一般就只提供给你读写文件的接口，好一点的会继续给你一些序列化机制，而更好的则会服务得更加周到。UE为我们在蓝图里提供了SaveGame的统一接口，让你只用关心想序列化的数据。
 USaveGame其实就是为了提供给UE一个UObject对象，本身并不需要其他额外的控制，所以它的类是如此的简单以至于我能直接把它的全部声明展示出来：

 UCLASS(abstract, Blueprintable, BlueprintType)
 class ENGINE_API USaveGame : public UObject
 {
 //
 //  @see UGameplayStatics::CreateSaveGameObject
 //  @see UGameplayStatics::SaveGameToSlot
 //  @see UGameplayStatics::DoesSaveGameExist
 //  @see UGameplayStatics::LoadGameFromSlot
 //  @see UGameplayStatics::DeleteGameInSlot
 //
GENERATED_UCLASS_BODY()
	};

而UGameplayStatics作为暴露给蓝图的接口实现部分，其内部的实现是：

先在内存中写入一些SavegameFileVersion之类的控制文件头，然后再序列化USaveGame对象，接着会找到ISaveGameSystem接口，最后交于真正的子类实现文件的保存。目前的默认实现是FGenericSaveGameSystem，其内部也只是转发到直接的文件读写接口上去。但你也可以实现自己的SaveGameSystem，不管是写文件或者是网络传输，保存到不同的地方去。或者是内部调用OnlineSubsystem的Storage接口，直接把玩家存档保存到Steam云存储中也可以。
因此可见，单单是玩家存档这件边角的小事，UE作为一个深受游戏开发淬炼过的引擎，为了方便自己，也同时造福我们广大开发者，已经实现了这么一套完善的机制。
关于存档数据关联的逻辑，再重复几句，对于那些需要直接在全局处理的数据逻辑，也可以直接在SaveGame中写方法来实现。比如实现AddCoin接口，对外隐藏实现，对内可以自定义附加一些逻辑。USaveGame可以看作是一个全局持久数据的业务逻辑类。跟GameInstance里的数据区分就是，GameInstance里面的是临时的数据，SaveGame里是持久的。清晰这一点区分，到时就不会纠结哪些属性放在哪里，哪些方法实现在哪里了。
注意一下，SaveGameToSlot里的SlotName可以理解为存档的文件名，UserIndex是用来标识是哪个玩家在存档。UserIndex是预留的，在目前的UE实现里并没有用到，只是预留给一些平台提供足够的信息。你也可以利用这个信息来为多个不同玩家生成不同的最后文件名什么的。而ISaveGameSystem是IPlatformFeaturesModule提供的模块接口，关于模块的机制，等引擎流程章节再说吧，目前可以简单理解为一个单件对象里提供了一些平台相关的接口对象。
 */

UCLASS()
class UMySaveGame : public USaveGame
{
	GENERATED_UCLASS_BODY()
};