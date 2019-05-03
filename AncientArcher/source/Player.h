#pragma once
#include<glm/glm.hpp>
#include "Entity.h"
class Entity;
struct Movement {

  bool positionChanged = false;

  bool forward = false, back = false;
  bool left = false, right = false;
  bool boost = false;

  bool jumped = false;
  bool canJumpAgain = true;
  bool onGround = true;
  bool falling = false;

  float lastOnGroundHeight = 0.0f;
  float currentGroundHeight = 0.0f;

  float intendedLocation[3] = { 0.0f, 0.0f, 0.0f };

  bool canJump() { return canJumpAgain && onGround && !falling; };
  bool canBoost() { return forward && !back; };
  bool isMoving() { return back || forward || left || right || jumped || !onGround; };
  bool isBoosted() { return forward && boost; };

};

class Player {
public:

  Player();
  Player(float leg_power);

  void update(float deltaTime);

    // accessors
  float getRunSpeed() const;
  float getRisingSpeed() const;
  float getJumpHeight() const;

    // mutators
  void increaseLegPower(float add);

  Entity *getEntity() const;

private:

  Entity *playerEntity;

  const float BASE_PLAYER_SPEED = 3.0f;
  const float BASE_PLAYER_JUMP_HEIGHT = 0.8f;

    // player stats
  float legPower;
  const float LEGPOWER_CAP = 100.0f;

  void processCommands(float deltaTime);

  static constexpr const float STAT_DIVISOR = 40.0f; 

};
