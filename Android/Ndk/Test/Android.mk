LOCAL_PATH := $(call my-dir)

###########################
#
# shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := Lua

LOCAL_MODULE_FILENAME := libLua

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/Src/TestA \
	$(LOCAL_PATH)/Src/TestB
	
LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/Src/TestC

#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/Src/TestA/*.cpp) \
	$(LOCAL_PATH)/Src/TestB/TestB.cpp)
	
LOCAL_SRC_FILES += \
	$(LOCAL_PATH)/Src/TestC/TestC.cpp

#LOCAL_CFLAGS += -DTEST_DEF -fPIC
#LOCAL_CXXFLAGS += -DGL_GLEXT_PROTOTYPES
LOCAL_CPPFLAGS += -DGL_GLEXT_PROTOTYPES
#LOCAL_LDLIBS := -ldl -lGLESv1_CM -lGLESv2 -llog -landroid

include $(BUILD_SHARED_LIBRARY)