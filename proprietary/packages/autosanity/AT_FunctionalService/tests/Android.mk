# Copyright 2008, The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq ($(strip $(MTK_AUTO_TEST)), yes)
	LOCAL_PATH:= $(call my-dir)
	include $(CLEAR_VARS)

	# We only want this apk build for tests.
	LOCAL_MODULE_TAGS := tests
	#LOCAL_MODULE_TAGS := optional
	LOCAL_CERTIFICATE := platform

	LOCAL_JAVA_LIBRARIES := android.test.runner \
	robotium

	# Include all test java files.
	LOCAL_SRC_FILES := $(call all-java-files-under, src)

	# Notice that we don't have to include the src files of Browser because, by
	# running the tests using an instrumentation targeting Browser, we
	# automatically get all of its classes loaded into our environment.

	LOCAL_PACKAGE_NAME := FunctionalSTests

	LOCAL_INSTRUMENTATION_FOR := FunctionalTestService

	include $(BUILD_PACKAGE)
endif
