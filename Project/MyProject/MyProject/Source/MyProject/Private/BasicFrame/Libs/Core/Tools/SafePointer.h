#pragma once

/**
 * @file SafePointer.h
 */
// 已经不用了
//#ifndef SAFE_NEW
//#define SAFE_NEW new
//#endif
//
//#ifndef SAFE_DELETE
//#define SAFE_DELETE(ptr) \
//{ \
//	if(ptr) \
//	{ \
//		delete(ptr); \
//		ptr = nullptr; \
//	} \
//}
//#endif
//
//#ifndef SAFE_DELETE_ARRAY
//#define SAFE_DELETE_ARRAY(ptr) \
//{ \
//	if(ptr) \
//	{ \
//		delete[] (ptr); \
//		ptr = nullptr; \
//	} \
//}
//#endif
//
//#ifndef SAFE_RELEASE
//#define SAFE_RELEASE(ptr) \
//{ \
//	if(ptr) \
//	{ \
//		(ptr)->Release(); \
//		ptr = nullptr; \
//	} \
//}
//#endif

#ifndef MY_SAFE_DELETE
#define MY_SAFE_DELETE(ptr) \
{ \
	if(ptr) \
	{ \
		delete(ptr); \
		ptr = nullptr; \
	} \
}
#endif

#ifndef MY_SAFE_DELETE_ARRAY
#define MY_SAFE_DELETE_ARRAY(ptr) \
{ \
	if(ptr) \
	{ \
		delete[] (ptr); \
		ptr = nullptr; \
	} \
}
#endif

#ifndef MY_SAFE_DISPOSE
#define MY_SAFE_DISPOSE(ptr) \
{ \
	if(ptr) \
	{ \
		(ptr)->dispose(); \
		MY_DELETE(ptr); \
		ptr = nullptr; \
	} \
}
#endif