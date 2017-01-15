#pragma once

#include "GameFramework/SaveGame.h"		// USaveGame
#include "MySaveGame.generated.h"

/**
 * @brief �־û�����
 * @ref http://www.yangqiu.cn/gh_e7524b8b5862/1479653.html
 * SaveGame
 UE����Ҵ浵���������ˣ�������UObject�����л����ƣ�������ֻ��Ҫ�̳���USaveGame�����������Ҫ����Щ�����ֶΣ�Ȼ������ṹ�Ϳ������л����������ġ���Ҵ浵Ҳ����Ϸ��һ���ǳ������Ĺ��ܣ��������һ���ֻ�ṩ�����д�ļ��Ľӿڣ���һ��Ļ��������һЩ���л����ƣ������õ�������ø����ܵ���UEΪ��������ͼ���ṩ��SaveGame��ͳһ�ӿڣ�����ֻ�ù��������л������ݡ�
 USaveGame��ʵ����Ϊ���ṩ��UEһ��UObject���󣬱�������Ҫ��������Ŀ��ƣ���������������˵ļ�����������ֱ�Ӱ�����ȫ������չʾ������

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

��UGameplayStatics��Ϊ��¶����ͼ�Ľӿ�ʵ�ֲ��֣����ڲ���ʵ���ǣ�

�����ڴ���д��һЩSavegameFileVersion֮��Ŀ����ļ�ͷ��Ȼ�������л�USaveGame���󣬽��Ż��ҵ�ISaveGameSystem�ӿڣ����������������ʵ���ļ��ı��档Ŀǰ��Ĭ��ʵ����FGenericSaveGameSystem�����ڲ�Ҳֻ��ת����ֱ�ӵ��ļ���д�ӿ���ȥ������Ҳ����ʵ���Լ���SaveGameSystem��������д�ļ����������紫�䣬���浽��ͬ�ĵط�ȥ���������ڲ�����OnlineSubsystem��Storage�ӿڣ�ֱ�Ӱ���Ҵ浵���浽Steam�ƴ洢��Ҳ���ԡ�
��˿ɼ�����������Ҵ浵����߽ǵ�С�£�UE��Ϊһ��������Ϸ���������������棬Ϊ�˷����Լ���Ҳͬʱ�츣���ǹ�󿪷��ߣ��Ѿ�ʵ������ôһ�����ƵĻ��ơ�
���ڴ浵���ݹ������߼������ظ����䣬������Щ��Ҫֱ����ȫ�ִ���������߼���Ҳ����ֱ����SaveGame��д������ʵ�֡�����ʵ��AddCoin�ӿڣ���������ʵ�֣����ڿ����Զ��帽��һЩ�߼���USaveGame���Կ�����һ��ȫ�ֳ־����ݵ�ҵ���߼��ࡣ��GameInstance����������־��ǣ�GameInstance���������ʱ�����ݣ�SaveGame���ǳ־õġ�������һ�����֣���ʱ�Ͳ��������Щ���Է��������Щ����ʵ���������ˡ�
ע��һ�£�SaveGameToSlot���SlotName�������Ϊ�浵���ļ�����UserIndex��������ʶ���ĸ�����ڴ浵��UserIndex��Ԥ���ģ���Ŀǰ��UEʵ���ﲢû���õ���ֻ��Ԥ����һЩƽ̨�ṩ�㹻����Ϣ����Ҳ�������������Ϣ��Ϊ�����ͬ������ɲ�ͬ������ļ���ʲô�ġ���ISaveGameSystem��IPlatformFeaturesModule�ṩ��ģ��ӿڣ�����ģ��Ļ��ƣ������������½���˵�ɣ�Ŀǰ���Լ����Ϊһ�������������ṩ��һЩƽ̨��صĽӿڶ���
 */

UCLASS()
class UMySaveGame : public USaveGame
{
	GENERATED_UCLASS_BODY()
};