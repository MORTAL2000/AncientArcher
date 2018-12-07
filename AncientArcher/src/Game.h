#pragma once
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <Shader.h>
#include <Camera.h>
#include <Controls.h>

static float lastFrame = 0.0f;

class Game {
public:
  Game();
  ~Game();

  Camera *camera;
  Controls *control;

  void mainLoop();

  void reshapeWindow(GLFWwindow *window, int w, int h);
  void mouseHandler(GLFWwindow* window, double xpos, double ypos);

private:

  float deltaTime = 0.0f;

  GLFWwindow *window;
  Shader *shader;

  unsigned int VAO, VBO, EBO;
  unsigned int texture001, texture002, texture003, texture004, texture005, texture006, texture007;
 
  void setupReshapeWindow();
  void setupMouseHandler();

};
