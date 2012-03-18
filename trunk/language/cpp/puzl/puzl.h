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

#endif
