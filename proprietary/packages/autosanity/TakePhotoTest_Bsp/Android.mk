ifeq ($(MTK_BSP_PACKAGE) , yes)
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

#LOCAL_CERTIFICATE := platform

LOCAL_JAVA_LIBRARIES := android.test.runner

LOCAL_STATIC_JAVA_LIBRARIES := librobotium4

# Include all test java files.
LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := TakePhotoTest_Bsp

LOCAL_INSTRUMENTATION_FOR := Camera2

include $(BUILD_PACKAGE)
endif
