#http://aigo.iteye.com/blog/2288694
#http://www.cnblogs.com/hesiming/archive/2011/03/15/1984444.html
LOCAL_PATH := $(call my-dir)

###########################
#
# shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := LuaSocket

LOCAL_MODULE_FILENAME := libLuaSocket

MY_PROJECT_ROOT_PATH = $(LOCAL_PATH)

LOCAL_C_INCLUDES := $(MY_PROJECT_ROOT_PATH)/src \
					$(MY_PROJECT_ROOT_PATH)/../lua-5.3.1/src

#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(MY_PROJECT_ROOT_PATH)/src/auxiliar.h \
	$(MY_PROJECT_ROOT_PATH)/src/auxiliar.c \
	$(MY_PROJECT_ROOT_PATH)/src/buffer.h \
	$(MY_PROJECT_ROOT_PATH)/src/buffer.c \
	$(MY_PROJECT_ROOT_PATH)/src/except.h \
	$(MY_PROJECT_ROOT_PATH)/src/except.c \
	$(MY_PROJECT_ROOT_PATH)/src/inet.h \
	$(MY_PROJECT_ROOT_PATH)/src/inet.c \
	$(MY_PROJECT_ROOT_PATH)/src/io.h \
	$(MY_PROJECT_ROOT_PATH)/src/io.c \
	$(MY_PROJECT_ROOT_PATH)/src/luasocket.h \
	$(MY_PROJECT_ROOT_PATH)/src/luasocket.c \
	$(MY_PROJECT_ROOT_PATH)/src/options.h \
	$(MY_PROJECT_ROOT_PATH)/src/options.c \
	$(MY_PROJECT_ROOT_PATH)/src/select.h \
	$(MY_PROJECT_ROOT_PATH)/src/select.c \
	$(MY_PROJECT_ROOT_PATH)/src/tcp.h \
	$(MY_PROJECT_ROOT_PATH)/src/tcp.c \
	$(MY_PROJECT_ROOT_PATH)/src/timeout.h \
	$(MY_PROJECT_ROOT_PATH)/src/timeout.c \
	$(MY_PROJECT_ROOT_PATH)/src/udp.h \
	$(MY_PROJECT_ROOT_PATH)/src/udp.c \
	$(MY_PROJECT_ROOT_PATH)/src/usocket.h \
	$(MY_PROJECT_ROOT_PATH)/src/usocket.c \
	 \
	$(MY_PROJECT_ROOT_PATH)/src/mime.h \
	$(MY_PROJECT_ROOT_PATH)/src/mime.c

# 编译标志
LOCAL_CFLAGS += -DTEST_DEF -fPIC -DANDROID
#LOCAL_CXXFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_CPPFLAGS += -DGL_GLEXT_PROTOTYPES

#添加需要链接的系统库，如ndk编译，需要链接的log/android等
#LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

#LOCAL_LDFLAGS += -L$(LOCAL_PATH)/../lua-5.3.1/libs/$(TARGET_ARCH_ABI)/libLua.so
#LOCAL_LDFLAGS += -L$(LOCAL_PATH)/../lua-5.3.1/obj/local/$(TARGET_ARCH_ABI)/libLua.a

# 链接标志
LOCAL_LDFLAGS := -Wl,--unresolved-symbols=ignore-all

# 连接静态库
# LOCAL_STATIC_LIBRARIES += libLua

# 连接动态库
#LOCAL_SHARED_LIBRARIES += libLua

# 这个地方空白一定要用空格，不要用 Tab ，否则会出现错误
ifeq ($(MY_DEBUG),DEBUG)
    APP_OPTIM := debug
    $(info "Debug Mode")
else
    APP_OPTIM := release
    $(info "Release Mode")
endif

include $(BUILD_SHARED_LIBRARY)

#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

# 依赖第三方库，检查这个库必须存在
include $(CLEAR_VARS)
 
LOCAL_MODULE := libLua
LOCAL_SRC_FILES := $(LOCAL_PATH)/../lua-5.3.1/libs/$(TARGET_ARCH_ABI)/libLua.so
#LOCAL_SRC_FILES := $(LOCAL_PATH)/../lua-5.3.1/obj/local/$(TARGET_ARCH_ABI)/libLua.a

include $(PREBUILT_SHARED_LIBRARY)
#include $(PREBUILT_STATIC_LIBRARY)