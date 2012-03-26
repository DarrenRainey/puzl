#ifndef PUZL_H
#define PUZL_H

#if defined(PUZL_PLATFORM_sdl_opengl)

  #include <puzl/utility/SdlOglGameShell.h>
  typedef SdlOglGameShell GameShell;

  #include <puzl/input/SdlOglInputSystem.h>
  typedef SdlOglInputSystem   InputSystem;
  typedef SdlOglInputKeyboard InputKeyboard;
  typedef SdlOglInputMouse    InputMouse;
  typedef SdlOglInputJoystick InputJoystick;

  #include <puzl/video/SdlOglVideoSystem.h>
  #include <puzl/video/SdlOglVideoImage.h>
  #include <puzl/video/SdlOglVideoSprite.h>
  typedef SdlOglVideoSystem   VideoSystem;
  typedef SdlOglVideoDisplay  VideoDisplay;
  typedef SdlOglVideoImage    VideoImage;
  typedef SdlOglVideoSprite   VideoSprite;

  #include <puzl/audio/SdlOglAudioSystem.h>
  typedef SdlOglAudioSystem   AudioSystem;
  typedef SdlOglAudioSample   AudioSample;

#elif defined(PUZL_PLATFORM_sdl_opengl_js)

#elif defined(PUZL_PLATFORM_android)

  #include <puzl/utility/AndroidGameShell.h>
  typedef AndroidGameShell GameShell;

  #include <puzl/input/AndroidInputSystem.h>
  typedef AndroidInputSystem   InputSystem;
  typedef AndroidInputKeyboard InputKeyboard;
  typedef AndroidInputMouse    InputMouse;
  typedef AndroidInputJoystick InputJoystick;

  #include <puzl/video/AndroidVideoSystem.h>
  #include <puzl/video/AndroidVideoImage.h>
  #include <puzl/video/AndroidVideoSprite.h>
  typedef AndroidVideoSystem   VideoSystem;
  typedef AndroidVideoDisplay  VideoDisplay;
  typedef AndroidVideoImage    VideoImage;
  typedef AndroidVideoSprite   VideoSprite;

  #include <puzl/audio/AndroidAudioSystem.h>
  typedef AndroidAudioSystem   AudioSystem;
  typedef AndroidAudioSample   AudioSample;

#endif

#endif
