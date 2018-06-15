#include "MyProject.h"
#include "TextureInsRes.h"
#include "ResItem.h"
#include "Engine/Texture.h"	// UTexture
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(TextureInsRes, ResInsBase)

TextureInsRes::TextureInsRes()
{

}

UTexture* TextureInsRes::getTexture()
{
	return this->mTexture;
}

void TextureInsRes::_initWithResImpl(ResItem* res)
{
	// 获取资源单独保存
	this->mTexture = Cast<UTexture>(res->getObject(res->getPrefabName()));

	Super::_initWithResImpl(res);
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