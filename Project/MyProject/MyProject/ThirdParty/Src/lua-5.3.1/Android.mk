#http://aigo.iteye.com/blog/2288694
#http://www.cnblogs.com/hesiming/archive/2011/03/15/1984444.html
LOCAL_PATH := $(call my-dir)

###########################
#
# shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := Lua

LOCAL_MODULE_FILENAME := libLua

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src

#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/src/lapi.c \
	$(LOCAL_PATH)/src/lapi.h \
	$(LOCAL_PATH)/src/lauxlib.c \
	$(LOCAL_PATH)/src/lauxlib.h \
	$(LOCAL_PATH)/src/lbaselib.c \
	$(LOCAL_PATH)/src/lbitlib.c \
	$(LOCAL_PATH)/src/lcode.c \
	$(LOCAL_PATH)/src/lcode.h \
	$(LOCAL_PATH)/src/lcorolib.c \
	$(LOCAL_PATH)/src/lctype.c \
	$(LOCAL_PATH)/src/lctype.h \
	$(LOCAL_PATH)/src/ldblib.c \
	$(LOCAL_PATH)/src/ldebug.c \
	$(LOCAL_PATH)/src/ldebug.h \
	$(LOCAL_PATH)/src/ldo.c \
	$(LOCAL_PATH)/src/ldo.h \
	$(LOCAL_PATH)/src/ldump.c \
	$(LOCAL_PATH)/src/lfunc.c \
	$(LOCAL_PATH)/src/lfunc.h \
	$(LOCAL_PATH)/src/lgc.c \
	$(LOCAL_PATH)/src/lgc.h \
	$(LOCAL_PATH)/src/linit.c \
	$(LOCAL_PATH)/src/liolib.c \
	$(LOCAL_PATH)/src/llex.c \
	$(LOCAL_PATH)/src/llex.h \
	$(LOCAL_PATH)/src/llimits.h \
	$(LOCAL_PATH)/src/lmathlib.c \
	$(LOCAL_PATH)/src/lmem.c \
	$(LOCAL_PATH)/src/lmem.h \
	$(LOCAL_PATH)/src/loadlib.c \
	$(LOCAL_PATH)/src/lobject.c \
	$(LOCAL_PATH)/src/lobject.h \
	$(LOCAL_PATH)/src/lopcodes.c \
	$(LOCAL_PATH)/src/lopcodes.h \
	$(LOCAL_PATH)/src/loslib.c \
	$(LOCAL_PATH)/src/lparser.c \
	$(LOCAL_PATH)/src/lparser.h \
	$(LOCAL_PATH)/src/lprefix.h \
	$(LOCAL_PATH)/src/lstate.c \
	$(LOCAL_PATH)/src/lstate.h \
	$(LOCAL_PATH)/src/lstring.c \
	$(LOCAL_PATH)/src/lstring.h \
	$(LOCAL_PATH)/src/lstrlib.c \
	$(LOCAL_PATH)/src/ltable.c \
	$(LOCAL_PATH)/src/ltable.h \
	$(LOCAL_PATH)/src/ltablib.c \
	$(LOCAL_PATH)/src/ltm.c \
	$(LOCAL_PATH)/src/ltm.h \
	$(LOCAL_PATH)/src/lua.c \
	$(LOCAL_PATH)/src/lua.h \
	$(LOCAL_PATH)/src/lua.hpp \
	$(LOCAL_PATH)/src/luaconf.h \
	$(LOCAL_PATH)/src/lualib.h \
	$(LOCAL_PATH)/src/lundump.c \
	$(LOCAL_PATH)/src/lundump.h \
	$(LOCAL_PATH)/src/lutf8lib.c \
	$(LOCAL_PATH)/src/lvm.c \
	$(LOCAL_PATH)/src/lvm.h \
	$(LOCAL_PATH)/src/lzio.c \
	$(LOCAL_PATH)/src/lzio.h

LOCAL_CFLAGS += -DTEST_DEF -fPIC
#LOCAL_CXXFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_CPPFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

# 用于预构建静态库（后面可被连接）
#include $(PREBUILT_STATIC_LIBRARY)

# 用于预构建动态库（后面可被连接）
# include $(PREBUILT_SHARED_LIBRARY)

# 构建为静态态库
# include $(BUILD_STATIC_LIBRARY)

# 构建为动态态库
include $(BUILD_SHARED_LIBRARY)

#TARGET_ARCH := arm

#TARGET_ARCH_ABI := armeabi-v7a

#include $(BUILD_EXECUTABLE)