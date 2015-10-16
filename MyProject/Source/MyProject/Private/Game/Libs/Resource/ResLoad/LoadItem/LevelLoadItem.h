#ifndef __LevelLoadItem_H
#define __LevelLoadItem_H

#include "LoadItem.h"
#include <string>

/**
* @brief 从本地磁盘加载 umap 扩展类型的资源
*/
class LevelLoadItem : public LoadItem
{
public:
	LevelLoadItem();
	~LevelLoadItem();

	void setLevelName(std::string levelName);
};

#endif