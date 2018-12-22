#include "Controls.h"
#include <glm/glm.hpp>
#include "Constraints.h"
#include "Player.h"
#include "Sound.h"
#include "Game.h"
#include <iostream>
#include "Camera.h"

extern Camera camera;

Controls::Controls() {
  firstMouse = true;
  mouseSensitivity = 0.08f;
}

Controls::~Controls() {}

void Controls::mouseMovement(double xpos, double ypos) {

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  camera.Yaw += xoffset;
  camera.Pitch += yoffset;

  if (camera.Pitch > 89.0f) {
    camera.Pitch = 89.0f;
  } else if (camera.Pitch < -89.0f) {
    camera.Pitch = -89.0f;
  }

  camera.updateCameraVectors();

}

void Controls::keyboardInput(GLFWwindow * window, Player *player, Pickups *pickups, float dtime, float gametime) {

  movedir.positionChanged = true;  //for footsteps

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {


    //swing sword  or shoot bow
    if (player->getLastAttackTime() + player->getAttackSpeed() < gametime) {

      switch (player->getSelectedWeapon()) {
      case 0:
        playpunchsound();
        break;
      case 1:
        playswordswingsound();
        player->swinging = true;
        break;
      case 2:
        playbowsound();
        break;
      }
      
      player->setTimeSinceLastAttack(gametime);
    }
  }

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    if (movedir.onGround) {
      movedir.boost = true;
    }
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    if (movedir.onGround) {
      movedir.back = false;
      movedir.forward = true;
      movedir.positionChanged = true;
    }
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    if (movedir.onGround) {
      movedir.forward = false;
      movedir.back = true;
      movedir.positionChanged = true;

    }
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    if (movedir.onGround) {
      movedir.right = false;
      movedir.left = true;
      movedir.positionChanged = true;

    }
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    if (movedir.onGround) {
      movedir.left = false;
      movedir.right = true;
      movedir.positionChanged = true;

    }
  }

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    if (movedir.onGround && movedir.canJumpAgain) {  //can jump again is to make the spacebar spam by holding it down not work
      movedir.jumped = true;
      movedir.canJumpAgain = false;
    }
  }

  if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
    player->selectWeapon(0);
  }

  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
    player->selectWeapon(1);
  }

  if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
    player->selectWeapon(2);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
    movedir.forward = false;
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
    movedir.back = false;
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
    movedir.left = false;
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
    movedir.right = false;
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    movedir.boost = false;
  }

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
    movedir.canJumpAgain = true;
  }

  if (movedir.back || movedir.forward || movedir.left || movedir.right) {

    float velocity = player->getRunSpeed() * dtime;  // MOVEMENT SPEED CALC : based on player stats

    if (movedir.boost && !movedir.back) {
      velocity += velocity;   //faster move forward while holding shift
    }

    //todo: half speed if moving sideways along with forward or back

    if (movedir.back || movedir.forward) {  // locks moving foward and backwards to the x and z axii. note that you can use the camera.Front instead of movefront to do a fly type thing while the y is unlocked or you are jumping
      glm::vec3 moveFront = { camera.Front.x, 0.0f, camera.Front.z };
      if (movedir.forward) camera.Position += moveFront * velocity;
      if (movedir.back) camera.Position -= moveFront * velocity;
    }

    if (movedir.right) camera.Position += camera.Right * velocity;
    if (movedir.left) camera.Position -= camera.Right * velocity;

    /* clamp to level - x */
    if (camera.Position.x > world_width) {
      if (movedir.forward) camera.Position.x -= camera.Front.x * velocity;
      if (movedir.back)    camera.Position.x += camera.Front.x * velocity;
      if (movedir.right)   camera.Position.x -= camera.Right.x * velocity;
      if (movedir.left)    camera.Position.x += camera.Right.x * velocity;
    } else if (camera.Position.x < 0.0f) {
      if (movedir.forward) camera.Position.x -= camera.Front.x * velocity;
      if (movedir.back)    camera.Position.x += camera.Front.x * velocity;
      if (movedir.right)   camera.Position.x -= camera.Right.x * velocity;
      if (movedir.left)    camera.Position.x += camera.Right.x * velocity;
    }

    /* clamp to level - z */
    if (camera.Position.z > world_width) {
      if (movedir.forward) camera.Position.z -= camera.Front.z * velocity;
      if (movedir.back)    camera.Position.z += camera.Front.z * velocity;
      if (movedir.right)   camera.Position.z -= camera.Right.z * velocity;
      if (movedir.left)    camera.Position.z += camera.Right.z * velocity;
    } else if (camera.Position.z < 0.0f) {
      if (movedir.forward) camera.Position.z -= camera.Front.z * velocity;
      if (movedir.back)    camera.Position.z += camera.Front.z * velocity;
      if (movedir.right)   camera.Position.z -= camera.Right.z * velocity;
      if (movedir.left)    camera.Position.z += camera.Right.z * velocity;
    }


    // FOOTSTEP SOUNDS
    if (movedir.timeSinceLastStep > TIMEBETWEENFOOTSTEPS || (movedir.boost && !movedir.back && movedir.timeSinceLastStep > TIMEBETWEENFOOTSTEPS - 0.5f)) {
      if (movedir.positionChanged && movedir.onGround) {
        playfootstepsound();
        movedir.timeSinceLastStep = 0;
      }
    } else {
      movedir.timeSinceLastStep += dtime;
    }

    // LEGPOWER PICKUP                       
    if (pickups->speedBoostAvail) {
      if (
        //y because boost loc is only x and y
        camera.Position.z >= pickups->speedBoostLoc.y - 1 &&
        camera.Position.z <= pickups->speedBoostLoc.y + 1 &&
        camera.Position.x >= pickups->speedBoostLoc.x - 1 &&
        camera.Position.x <= pickups->speedBoostLoc.x + 1) {
        player->increaseLegPower(15.0f);
        pickups->speedBoostAvail = false;
        playsuccesssound();

      }
    }  
    
    // ATTACKSPEED PICKUP                       
    if (pickups->attackBoostAvail) {
      if (
        //y because boost loc is only x and y
        camera.Position.z >= pickups->attackBoostLoc.y - 1 &&
        camera.Position.z <= pickups->attackBoostLoc.y + 1 &&
        camera.Position.x >= pickups->attackBoostLoc.x - 1 &&
        camera.Position.x <= pickups->attackBoostLoc.x + 1) {
        player->increaseAttackSpeed(0.5f);  // subtract 500. off the ms timer
        pickups->attackBoostAvail = false;
        playsuccesssound();

      }
    }

  }

  /* Jump System */
  if (movedir.jumped) {   // Jump Start
    movedir.onGround = false;
    movedir.jumped = false;
    playgruntsound();
  } else if (!movedir.onGround && !movedir.falling) {  // Jump Rising
    camera.Position.y += camera.WorldUp.y * player->getRisingSpeed() * dtime;  // RISING SPEED CALC: jump speed based on LegPower Player Stat
    if (camera.Position.y > player->getJumpHeight() + camera.camstart[1]) {  // MAX HEIGHT CALC: jump height based on LegPower Player Stat
      movedir.falling = true;
      //todo: added gravity to falling y = 1/2at^2 + vt  
    }
  } else if (movedir.falling && !movedir.onGround) {   // currently going down
    camera.Position.y -= camera.WorldUp.y * 5.2f * dtime;  // GRAVITY PULL DOWN CALC: static value, todo: make dynamic based on falling time
    if (camera.Position.y <= camera.camstart[1]) {
      movedir.onGround = true;
      movedir.falling = false;
      playlandingsound();
    }
  }

  if (movedir.onGround) {
    camera.Position.y = camera.camstart[1];
  }


}