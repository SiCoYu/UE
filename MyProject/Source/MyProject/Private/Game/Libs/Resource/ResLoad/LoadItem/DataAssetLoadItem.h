#pragma once

#include "Engine/DataAsset.h"
#include "DataAssetLoadItem.generated.h"

/**
 * @brief ����ǰ��� UE �Ĵ����ʽ������Ŀǰ���ǲ���ʹ�ã���ô�Զ�����
 */
UCLASS(config = Game)
class UDataAssetLoadItem : public UDataAsset
{
	GENERATED_BODY()

public:
	void loadFile(const FString& Filename);
};