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

#endif