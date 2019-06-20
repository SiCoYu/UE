#ifndef __PlatformDefine_H
#define __PlatformDefine_H

/**
 * @brief 各种平台定义和宏定义
 */

// 是否使用外部的 Socket 库，不使用 UE 自己的 Socket
#define USE_EXTERN_SOCKET
#undef USE_EXTERN_SOCKET			// 测试 UE 自带的库

// 是否使用外部的 Thread 库，不使用 UE 自己的 Thread
#define USE_EXTERN_THREAD
#undef USE_EXTERN_THREAD			// 测试 UE 自带的库

// 是否进行单元测试
#define ENABLE_UNIT_TEST

// 是否加密
#define MSG_ENCRIPT
#undef MSG_ENCRIPT

// 是否压缩
#define MSG_COMPRESS
#undef MSG_COMPRESS

// 编辑器定义
#ifdef WITH_EDITOR
	#ifndef MY_WITH_EDITOR
		#define	MY_WITH_EDITOR
	#endif
#else
	#ifdef MY_WITH_EDITOR
		#undef	MY_WITH_EDITOR
	#endif
#endif

#ifdef UE_BUILD_SHIPPING
	#ifndef MY_UE_BUILD_SHIPPING
		#define	MY_UE_BUILD_SHIPPING
	#endif
#else
	#ifdef MY_UE_BUILD_SHIPPING
		#undef	MY_UE_BUILD_SHIPPING
	#endif
#endif

#ifdef UE_BUILD_TEST
	#ifndef MY_UE_BUILD_TEST
		#define	MY_UE_BUILD_TEST
	#endif
#else
	#ifndef MY_UE_BUILD_TEST
		#undef	MY_UE_BUILD_TEST
	#endif
#endif

// 定义平台类型
#define MY_PLATFORM_WIN32 0
#define MY_PLATFORM_WINRT 1
#define MY_PLATFORM_ANDROID 2
#define MY_PLATFORM_MAC 3
#define MY_PLATFORM_IOS 4

#define MY_PLATFORM MY_PLATFORM_WIN32

#define MY_DEBUG_MODE 1
#define MY_MEMORY_TRACKER 1

#define MY_BEGIN_NAMESPACE(NSName) namespace NSName {
#define MY_END_NAMESPACE }
#define MY_USING_NAMESPACE(NSName) using namespace NSName;

//#define MY_BEGIN_NAMESPACE(NSName)
//#define MY_END_NAMESPACE
//#define MY_USING_NAMESPACE(NSName)

#endif