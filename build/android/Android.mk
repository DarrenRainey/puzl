########################################################################

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

PUZL_ROOT         := puzl

PUZL_ROOT_CPP     := $(PUZL_ROOT)/language/cpp

PUZL_CORE	      := $(PUZL_ROOT_CPP)/platform/core
PUZL_CORE_INCLUDE := $(PUZL_CORE)/include
PUZL_CORE_SRC     := $(PUZL_CORE)/src
PUZL_CORE_UTILITY := $(PUZL_CORE_SRC)/utility
PUZL_CORE_VIDEO   := $(PUZL_CORE_SRC)/video
PUZL_CORE_INPUT   := $(PUZL_CORE_SRC)/input
PUZL_CORE_AUDIO   := $(PUZL_CORE_SRC)/audio
PUZL_CORE_NETWORK := $(PUZL_CORE_SRC)/network

PUZL_CORE_SRC_FILES := $(PUZL_CORE_AUDIO)/CoreAudioSample.cpp      \
					   $(PUZL_CORE_AUDIO)/CoreAudioSystem.cpp      \
					   $(PUZL_CORE_INPUT)/CoreInputDevice.cpp      \
					   $(PUZL_CORE_INPUT)/CoreInputJoystick.cpp    \
					   $(PUZL_CORE_INPUT)/CoreInputKeyboard.cpp    \
					   $(PUZL_CORE_INPUT)/CoreInputMouse.cpp       \
					   $(PUZL_CORE_INPUT)/CoreInputSystem.cpp      \
					   $(PUZL_CORE_VIDEO)/CoreVideoImage.cpp       \
					   $(PUZL_CORE_VIDEO)/BlockGraphic.cpp     	   \
					   $(PUZL_CORE_VIDEO)/CharacterGraphic.cpp     \
					   $(PUZL_CORE_VIDEO)/CoreVideoDisplay.cpp     \
					   $(PUZL_CORE_VIDEO)/CoreVideoSprite.cpp      \
					   $(PUZL_CORE_VIDEO)/CoreVideoSystem.cpp      \
					   $(PUZL_CORE_UTILITY)/Operation.cpp          \
					   $(PUZL_CORE_UTILITY)/CoreGameShell.cpp

PUZL_ANDROID	      := $(PUZL_ROOT_CPP)/platform/android
PUZL_ANDROID_INCLUDE  := $(PUZL_ANDROID)/include
PUZL_ANDROID_SRC      := $(PUZL_ANDROID)/src
PUZL_ANDROID_UTILITY  := $(PUZL_ANDROID_SRC)/utility
PUZL_ANDROID_VIDEO    := $(PUZL_ANDROID_SRC)/video
PUZL_ANDROID_INPUT    := $(PUZL_ANDROID_SRC)/input
PUZL_ANDROID_AUDIO    := $(PUZL_ANDROID_SRC)/audio
PUZL_ANDROID_NETWORK  := $(PUZL_ANDROID_SRC)/network

PUZL_ANDROID_SRC_FILES := $(PUZL_ANDROID_AUDIO)/AndroidAudioSample.cpp      \
					      $(PUZL_ANDROID_AUDIO)/AndroidAudioSystem.cpp      \
					      $(PUZL_ANDROID_INPUT)/AndroidInputJoystick.cpp    \
					      $(PUZL_ANDROID_INPUT)/AndroidInputKeyboard.cpp    \
					      $(PUZL_ANDROID_INPUT)/AndroidInputMouse.cpp       \
					      $(PUZL_ANDROID_INPUT)/AndroidInputSystem.cpp      \
					      $(PUZL_ANDROID_VIDEO)/AndroidVideoImage.cpp       \
					      $(PUZL_ANDROID_VIDEO)/AndroidVideoDisplay.cpp     \
					      $(PUZL_ANDROID_VIDEO)/AndroidVideoSprite.cpp      \
					      $(PUZL_ANDROID_VIDEO)/AndroidVideoSystem.cpp      \
					      $(PUZL_ANDROID_UTILITY)/AndroidGameShell.cpp


LOCAL_C_INCLUDES := $(PUZL_ROOT_CPP) $(PUZL_CORE_INCLUDE) $(PUZL_ANDROID_INCLUDE)
LOCAL_SRC_FILES  :=  $(PUZL_CORE_SRC_FILES) $(PUZL_ANDROID_SRC_FILES)

LOCAL_LDLIBS    := -llog -lGLESv1_CM# -lGLESv2
LOCAL_CFLAGS    := -Werror -DPUZL_PLATFORM_android

LOCAL_MODULE     := libpuzl

include $(BUILD_SHARED_LIBRARY)

########################################################################

include $(LOCAL_PATH)/Game.mk

########################################################################
#LOCAL_STATIC_LIBRARIES := <module_name>
#include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
