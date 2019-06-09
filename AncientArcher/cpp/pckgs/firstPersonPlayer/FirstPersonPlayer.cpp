#include "FirstPersonPlayer.h"
#include <Controls.h>
#include <Camera.h>
#include <Sound.h>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <TextureLoader.h>

extern Controls g_controls;    // from display.cpp (engine)
extern Camera g_camera;        // from game.cpp    (game)

FirstPersonPlayer::FirstPersonPlayer()
{
  model = std::make_unique<PrimativeRenderer>();
  light = std::make_unique<Lighting>();
  legPower = 10.0f;
  jumpTimer = 0.0f;
}

FirstPersonPlayer::FirstPersonPlayer(float leg_power)
{
  model = std::make_unique<PrimativeRenderer>();

  TextureLoader tLoader;
  unsigned int texID = tLoader.load2DTexture("../AncientArcher/cpp/pckgs/firstPersonPlayer/foot.png");

  Entity e(
    ENTITYTYPE::CUBE,
    glm::vec3(0, 1, 0),
    glm::vec3(.008f, 2.0f,.008f),
    texID,
    true,
    true
  );
  model.get()->addToPrimativeEntities(e);

  light = std::make_unique<Lighting>();
  light->setConstantLight(model.get()->getShader());

  g_camera.setPosition(glm::vec3(0, 2.011f, 0));

  legPower = leg_power;
  jumpTimer = 0.0f;
}


void FirstPersonPlayer::render() const
{
  if (model)
  { 
    model.get()->render();
  }
}

/**
 * Adds a point light at the player location specified.
 */
void FirstPersonPlayer::addPointLight(glm::vec3 pos, Shader* shader)
{
  light->addPointLight(pos, shader);
}

/**
 * Moves the first point light to the newpos.
 */
void FirstPersonPlayer::movePlayerLight(glm::vec3 newpos, Shader* shader)
{
  light->movePointLight(0, newpos, shader);
}

void FirstPersonPlayer::increaseLegPower(float add) {
  if (legPower < 100.00f) {
    legPower += add;
    if (legPower > 100.00f) {
      legPower = 100.00f;
    }
  }
}

void FirstPersonPlayer::update(float deltaTime)
{
  g_controls.fppKeyboardIn(this);

  //glm::vec3 playerIntendedLocation = g_camera.Position;
  float velocity;
  moves.positionChanged = true;

  velocity = getRunSpeed() * deltaTime;  // MOVEMENT SPEED CALC : based on player stats
  if (moves.forward) {  // half speed if moving left or right while forward
    if (moves.left || moves.right) {
      velocity = getRunSpeed() / 2 * deltaTime;
    }
  }

  if (moves.boost && moves.forward) {  // boost while moving forward
    velocity *= 2.0;  // velocity power
  }

}

float FirstPersonPlayer::getRunSpeed() const {
  return (legPower / STAT_DIVISOR) + BASE_PLAYER_SPEED;
}

float FirstPersonPlayer::getRisingSpeed() const {
  return (legPower / STAT_DIVISOR) + BASE_PLAYER_JUMP_SPEED;
}

float FirstPersonPlayer::getJumpHeight() const {
  return (legPower / STAT_DIVISOR) + BASE_PLAYER_JUMP_HEIGHT;
}

