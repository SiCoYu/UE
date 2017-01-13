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

LOCAL_SRC_FILES := src/lapi.c src/lauxlib.c src/lbaselib.c src/lbitlib.c src/lcode.c src/lcorolib.c src/lctype.c src/ldblib.c src/ldebug.c src/ldo.c src/ldo.h src/ldump.c src/lfunc.c src/lgc.c src/lgc.h src/linit.c src/liolib.c src/llex.c src/llex.h src/lmathlib.c src/lmem.c src/loadlib.c src/lobject.c src/lopcodes.c src/loslib.c src/lparser.c src/lstate.c src/lstring.c src/lstrlib.c src/ltable.c src/ltable.h src/ltablib.c src/ltm.c src/lua.c src/lundump.c src/lutf8lib.c src/lvm.c src/lzio.c 

LOCAL_CFLAGS += -DTEST_DEF -fPIC
#LOCAL_CXXFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_CPPFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_SHARED_LIBRARY)