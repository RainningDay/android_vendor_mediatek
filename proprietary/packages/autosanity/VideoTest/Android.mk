ifeq ($(strip $(MTK_AUTO_TEST)),yes)

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_CERTIFICATE := platform

LOCAL_JAVA_LIBRARIES := android.test.runner
LOCAL_JAVA_LIBRARIES += mediatek-framework
LOCAL_STATIC_JAVA_LIBRARIES := librobotium4

# Include all test java files.
LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := VideoPlaybackTest

LOCAL_INSTRUMENTATION_FOR := Gallery2

include $(BUILD_PACKAGE)

endif
