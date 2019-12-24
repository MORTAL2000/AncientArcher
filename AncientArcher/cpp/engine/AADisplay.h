#pragma once
#include "AAControls.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\ext\vector_float3.hpp>

class AADisplay
{

public:

  static AADisplay* getInstance();

  ~AADisplay();

  int getScreenWidth();
  int getScreenHeight();
  bool getIsWindowFullScreen();
  GLFWwindow* getWindow();

  void setCursorToVisible();
  void setCursorToHidden();
  void setCursorToDisabled();
  void setWindowClearColor(glm::vec3 rgb);
  void setWindowSize(int width, int height, int xpos = 0, int ypos = 0);
  void setWindowTitle(const char* name);
  
  void toggleCursor();
  void closeWindow();

  friend class AAEngine;

  void reshapeWindowHandler(GLFWwindow* window, int width, int height);
  void mouseHandler(GLFWwindow* window, float xpos, float ypos);
  void scrollHandler(GLFWwindow* window, float xpos, float ypos);

private:

  enum class CursorMode { VISIBLE, HIDDEN, FPS } mCursorMode;

  void toggleFullScreen();
  void setFullscreenToOn();
  void setFullscreenToOff();

  void keepWindowOpen();

  void clearBackBuffer() const;
  void swapWindowBuffers() const;

  bool mWindowIsFullScreen = false;
  int mWindowWidth = 800, mWindowHeight = 600;
  int mXPos = 0, mYPos = 0;
  
  GLFWwindow* mWindow = nullptr;
  glm::vec3 mWindowClearColor = glm::vec3(0.35f, 0.15f, 0.35f);
  
  void initGLFW();
  void initReshapeWindowHandler();
  void initMouseHandler();
  void initMouseScrollHandler();
  void initFromEngine();

};
