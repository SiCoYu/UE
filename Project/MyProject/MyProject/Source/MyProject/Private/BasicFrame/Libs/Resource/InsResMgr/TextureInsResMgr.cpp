#include "MyProject.h"
#include "TextureInsResMgr.h"
#include "TextureInsRes.h"

TextureInsResMgr::TextureInsResMgr()
{

}

TextureInsRes* TextureInsResMgr::getAndSyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndSyncLoad<TextureInsRes>(path, handle);
}

TextureInsRes* TextureInsResMgr::getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle)
{
	return Super::getAndAsyncLoad<TextureInsRes>(path, handle);
}