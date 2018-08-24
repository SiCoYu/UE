#http://aigo.iteye.com/blog/2288694
#http://www.cnblogs.com/hesiming/archive/2011/03/15/1984444.html

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Lua

LOCAL_MODULE_FILENAME := libLua

MY_PROJECT_ROOT_PATH = $(LOCAL_PATH)
MY_THIRD_PARTY_ROOT_PATH = $(MY_PROJECT_ROOT_PATH)/../..

LOCAL_C_INCLUDES := $(MY_PROJECT_ROOT_PATH)/src

#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(MY_PROJECT_ROOT_PATH)/src/lapi.c \
	$(MY_PROJECT_ROOT_PATH)/src/lapi.h \
	$(MY_PROJECT_ROOT_PATH)/src/lauxlib.c \
	$(MY_PROJECT_ROOT_PATH)/src/lauxlib.h \
	$(MY_PROJECT_ROOT_PATH)/src/lbaselib.c \
	$(MY_PROJECT_ROOT_PATH)/src/lbitlib.c \
	$(MY_PROJECT_ROOT_PATH)/src/lcode.c \
	$(MY_PROJECT_ROOT_PATH)/src/lcode.h \
	$(MY_PROJECT_ROOT_PATH)/src/lcorolib.c \
	$(MY_PROJECT_ROOT_PATH)/src/lctype.c \
	$(MY_PROJECT_ROOT_PATH)/src/lctype.h \
	$(MY_PROJECT_ROOT_PATH)/src/ldblib.c \
	$(MY_PROJECT_ROOT_PATH)/src/ldebug.c \
	$(MY_PROJECT_ROOT_PATH)/src/ldebug.h \
	$(MY_PROJECT_ROOT_PATH)/src/ldo.c \
	$(MY_PROJECT_ROOT_PATH)/src/ldo.h \
	$(MY_PROJECT_ROOT_PATH)/src/ldump.c \
	$(MY_PROJECT_ROOT_PATH)/src/lfunc.c \
	$(MY_PROJECT_ROOT_PATH)/src/lfunc.h \
	$(MY_PROJECT_ROOT_PATH)/src/lgc.c \
	$(MY_PROJECT_ROOT_PATH)/src/lgc.h \
	$(MY_PROJECT_ROOT_PATH)/src/linit.c \
	$(MY_PROJECT_ROOT_PATH)/src/liolib.c \
	$(MY_PROJECT_ROOT_PATH)/src/llex.c \
	$(MY_PROJECT_ROOT_PATH)/src/llex.h \
	$(MY_PROJECT_ROOT_PATH)/src/llimits.h \
	$(MY_PROJECT_ROOT_PATH)/src/lmathlib.c \
	$(MY_PROJECT_ROOT_PATH)/src/lmem.c \
	$(MY_PROJECT_ROOT_PATH)/src/lmem.h \
	$(MY_PROJECT_ROOT_PATH)/src/loadlib.c \
	$(MY_PROJECT_ROOT_PATH)/src/lobject.c \
	$(MY_PROJECT_ROOT_PATH)/src/lobject.h \
	$(MY_PROJECT_ROOT_PATH)/src/lopcodes.c \
	$(MY_PROJECT_ROOT_PATH)/src/lopcodes.h \
	$(MY_PROJECT_ROOT_PATH)/src/loslib.c \
	$(MY_PROJECT_ROOT_PATH)/src/lparser.c \
	$(MY_PROJECT_ROOT_PATH)/src/lparser.h \
	$(MY_PROJECT_ROOT_PATH)/src/lprefix.h \
	$(MY_PROJECT_ROOT_PATH)/src/lstate.c \
	$(MY_PROJECT_ROOT_PATH)/src/lstate.h \
	$(MY_PROJECT_ROOT_PATH)/src/lstring.c \
	$(MY_PROJECT_ROOT_PATH)/src/lstring.h \
	$(MY_PROJECT_ROOT_PATH)/src/lstrlib.c \
	$(MY_PROJECT_ROOT_PATH)/src/ltable.c \
	$(MY_PROJECT_ROOT_PATH)/src/ltable.h \
	$(MY_PROJECT_ROOT_PATH)/src/ltablib.c \
	$(MY_PROJECT_ROOT_PATH)/src/ltm.c \
	$(MY_PROJECT_ROOT_PATH)/src/ltm.h \
	$(MY_PROJECT_ROOT_PATH)/src/lua.c \
	$(MY_PROJECT_ROOT_PATH)/src/lua.h \
	$(MY_PROJECT_ROOT_PATH)/src/lua.hpp \
	$(MY_PROJECT_ROOT_PATH)/src/luaconf.h \
	$(MY_PROJECT_ROOT_PATH)/src/lualib.h \
	$(MY_PROJECT_ROOT_PATH)/src/lundump.c \
	$(MY_PROJECT_ROOT_PATH)/src/lundump.h \
	$(MY_PROJECT_ROOT_PATH)/src/lutf8lib.c \
	$(MY_PROJECT_ROOT_PATH)/src/lvm.c \
	$(MY_PROJECT_ROOT_PATH)/src/lvm.h \
	$(MY_PROJECT_ROOT_PATH)/src/lzio.c \
	$(MY_PROJECT_ROOT_PATH)/src/lzio.h

LOCAL_CFLAGS += -DTEST_DEF -fPIC
#LOCAL_CXXFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_CPPFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

# 用于预构建静态库（后面可被连接）
#include $(PREBUILT_STATIC_LIBRARY)

# 用于预构建动态库（后面可被连接）
# include $(PREBUILT_SHARED_LIBRARY)

#TARGET_ARCH := arm
# $(TARGET_ARCH_ABI)/libLua.so
#TARGET_ARCH_ABI := armeabi-v7a
#$(warning "TARGET_ARCH_ABI = $(TARGET_ARCH_ABI), TARGET_ARCH =$(TARGET_ARCH)")

$(warning "warning: TARGET_PLATFORM = $(TARGET_PLATFORM)")
#$(info "info: TARGET_PLATFORM = $(TARGET_PLATFORM)")
#$(message "message: TARGET_PLATFORM = $(TARGET_PLATFORM)")
$(info "info: TARGET_ARCH_ABI = $(TARGET_ARCH_ABI)")

#条件编译
#ifeq ($(TARGET_PRODUCT),generic)
#	copy_from += etc/vold.conf
#endif

# 这个地方空白一定要用空格，不要用 Tab ，否则会出现错误
ifeq ($(MY_DEBUG),DEBUG)
    APP_OPTIM := debug
    $(info "Debug Mode")
else
    APP_OPTIM := release
    $(info "Release Mode")
endif

# 拷贝文件
# PRODUCT_COPY_FILES += $(MY_THIRD_PARTY_ROOT_PATH)/Inc/Lua/lua.h:$(MY_PROJECT_ROOT_PATH)/src/lua.h

# 构建为静态态库
# include $(BUILD_STATIC_LIBRARY)

# 构建为动态态库
include $(BUILD_SHARED_LIBRARY)

#include $(BUILD_EXECUTABLE)

# 拷贝文件
#$(info "src = $(MY_PROJECT_ROOT_PATH)/src/lua.h")
#$(info "dest = $(MY_THIRD_PARTY_ROOT_PATH)/Inc/Lua/lua.h")
#PRODUCT_COPY_FILES += F:/Proj/aaa.h:F:/Proj/TestQQ/project.json