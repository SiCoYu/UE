#pragma once

#ifndef SAFE_NEW
#define SAFE_NEW new
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
{ \
	if(ptr) \
	{ \
		delete(ptr); \
		ptr = nullptr; \
	} \
}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(ptr) \
{ \
	if(ptr) \
	{ \
		delete[] (ptr); \
		ptr = nullptr; \
	} \
}
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(ptr) \
{ \
	if(ptr) \
	{ \
		(ptr)->Release(); \
		ptr = nullptr; \
	} \
}
#endif