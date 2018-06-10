#ifndef __ResLoadState_H
#define __ResLoadState_H

#include "ResLoadStateCV.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ResLoadState
{
protected:
	ResLoadStateCV mResLoadState;

public:
	ResLoadState();

	void init();
	void dispose();

	ResLoadStateCV getResLoadState();
	void setResLoadState(ResLoadStateCV value);
	void reset();
    // 是否加载完成，可能成功可能失败
	bool hasLoaded();
	bool hasSuccessLoaded();
	bool hasFailed();
    // 没有加载或者正在加载中
	bool hasNotLoadOrLoading();
	void setSuccessLoaded();
	void setFailed();
	void setLoading();
	// 成功实例化
	void setSuccessIns();
	// 实例化失败
	void setInsFailed();
	// 正在实例化
	void setInsing();
	// 是否成功实例化
	bool hasSuccessIns();
	// 是否实例化失败
	bool hasInsFailed();
	// 是否正在实例化
	bool hasInsing();
	void copyFrom(ResLoadState* rhv);
};

MY_END_NAMESPACE

#endif