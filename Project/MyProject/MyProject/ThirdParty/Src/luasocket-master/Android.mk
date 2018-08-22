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

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src \
					$(LOCAL_PATH)/../lua-5.3.1/src

#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/src/auxiliar.h \
	$(LOCAL_PATH)/src/auxiliar.c \
	$(LOCAL_PATH)/src/buffer.h \
	$(LOCAL_PATH)/src/buffer.c \
	$(LOCAL_PATH)/src/except.h \
	$(LOCAL_PATH)/src/except.c \
	$(LOCAL_PATH)/src/inet.h \
	$(LOCAL_PATH)/src/inet.c \
	$(LOCAL_PATH)/src/io.h \
	$(LOCAL_PATH)/src/io.c \
	$(LOCAL_PATH)/src/luasocket.h \
	$(LOCAL_PATH)/src/luasocket.c \
	$(LOCAL_PATH)/src/options.h \
	$(LOCAL_PATH)/src/options.c \
	$(LOCAL_PATH)/src/select.h \
	$(LOCAL_PATH)/src/select.c \
	$(LOCAL_PATH)/src/tcp.h \
	$(LOCAL_PATH)/src/tcp.c \
	$(LOCAL_PATH)/src/timeout.h \
	$(LOCAL_PATH)/src/timeout.c \
	$(LOCAL_PATH)/src/udp.h \
	$(LOCAL_PATH)/src/udp.c \
	$(LOCAL_PATH)/src/usocket.h \
	$(LOCAL_PATH)/src/usocket.c \
	 \
	$(LOCAL_PATH)/src/mime.h \
	$(LOCAL_PATH)/src/mime.c

LOCAL_CFLAGS += -DTEST_DEF -fPIC -DANDROID
#LOCAL_CXXFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_CPPFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

LOCAL_LDFLAGS += -L$(LOCAL_PATH)/../lua-5.3.1/libs/x86_64 -llibLua

# 连接静态库
# LOCAL_STATIC_LIBRARIES += libLua

# 连接动态库
#LOCAL_SHARED_LIBRARIES += libLua

include $(BUILD_SHARED_LIBRARY)