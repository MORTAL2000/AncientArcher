#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../player/Player.h"

static float TIMEBETWEENFOOTSTEPS = 2.0f;

struct Movement {
  bool positionChanged = false; // for footsteps

  bool forward = false, back = false;
  bool left = false, right = false;
  bool boost = false;

  bool jumped = false;
  bool canJumpAgain = true;
  bool onGround = true;
  bool falling = false;

  float timeSinceLastStep = 0;

  float lastOnGroundHeight = 0.5f;
  float currentGroundHeight = 0.5f;

};

class Controls {

public:
  Controls();
  ~Controls();

  void mouseMovement(float xpos, float ypos);

  void keyboardInput(Player *player);

private:

  bool firstMouse;

  float lastX, lastY;

  float mouseSensitivity;

};

