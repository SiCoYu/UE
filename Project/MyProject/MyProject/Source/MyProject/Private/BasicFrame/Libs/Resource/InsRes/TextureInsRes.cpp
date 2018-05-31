#include "MyProject.h"
#include "TextureInsRes.h"
#include "ResItem.h"
#include "Engine/Texture.h"	// UTexture

MY_BEGIN_NAMESPACE(MyNS)

TextureInsRes::TextureInsRes()
{

}

UTexture* TextureInsRes::getTexture()
{
	return this->mTexture;
}

void TextureInsRes::initImpl(ResItem* res)
{
	// 获取资源单独保存
	this->mTexture = Cast<UTexture>(res->getObject(res->getPrefabName()));

	Super::initImpl(res);
}

void TextureInsRes::unload()
{
	if (this->mTexture != nullptr)
	{
		// 这个接口不知道行不行
		//UtilSysLibWrap::UnloadAsset(this->mMaterial);
		this->mTexture = nullptr;

		// 这个接口肯定可以
		//UtilSysLibWrap.UnloadUnusedAssets();
	}

	Super::unload();
}

MY_END_NAMESPACE