#include "MyProject.h"
#include "SoundParam.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SoundParam, GObject)

SoundParam::SoundParam()
{
    
}

// 所有都执行完成后调用
void SoundParam::init()
{
    this->onInit();
}

void SoundParam::onInit()
{
    //base.onInit();

    this->mPath = "";
    this->mIsLoop = true;
    this->volume = 1.0f;
    this->soundtype = 1;
    this->mUniqueId = 0;
}

void SoundParam::dispose()
{
    //this->onClear();
    //this->onDestroy();
}

MY_END_NAMESPACE