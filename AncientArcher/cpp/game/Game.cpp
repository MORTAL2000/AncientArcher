#include "Game.h"
#include <CollisionHandler.h>
#include <glm/glm.hpp>
#include <iostream>
#include <Display.h>
#include <TextureLoader.h>
#include <Global.h>
#include <mearly.h>
#define DEBUG FALSE;

//--- GLOBALS ---//
Display g_display(" MMO ", Display::MouseControlType::FPP);
//              Starting Position           YAW    PITCH  FOV
Camera g_camera(glm::vec3(0.f, 1.0f, 0.f), 0, 0, 45.f);
Lighting g_lighting;
std::vector<Entity> g_entities;
//--- END GLOBALS ---//

Game::Game()
{
#ifdef DEBUG
  int __textures_allowed = 0, __totalTexturesAllowed = 0;
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &__textures_allowed);
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &__totalTexturesAllowed);
  std::cout << "//--GRAPHIC CARD INFO--//\nMax textures per shader:  " << __textures_allowed << "\n";
  std::cout << "Max total textures:  " << __totalTexturesAllowed << "\n";
#endif

  player = new FirstPersonPlayer(100.0f);
  prims = new PrimativeRenderer();

  g_lighting.setConstantLight(prims->getShader());

  TextureLoader texLoader;
  unsigned int groundTextureId = texLoader.load2DTexture("../AncientArcher/cpp/pckgs/primatives/grass.png");

  // ------------ SET FLOOR ------------ //
  float planeCollisionThickness = 0.18f;
  float currentGroundLevel = -0.02f;

  for (int i = 0; i < 4; i++) {
    Entity floor1(
      ENTITYTYPE::PLANE,
      glm::vec3(i * ENGINE_LOGIC_CHECKING_DISTANCE, currentGroundLevel, ENGINE_LOGIC_CHECKING_DISTANCE / 2.0f),
      glm::vec3(ENGINE_LOGIC_CHECKING_DISTANCE, planeCollisionThickness, ENGINE_LOGIC_CHECKING_DISTANCE),
      groundTextureId,
      true,
      true
    );
    g_entities.push_back(floor1);

    Entity floor2(
      ENTITYTYPE::PLANE,
      glm::vec3(i * ENGINE_LOGIC_CHECKING_DISTANCE, currentGroundLevel, ENGINE_LOGIC_CHECKING_DISTANCE * 1.5f),
      glm::vec3(ENGINE_LOGIC_CHECKING_DISTANCE, planeCollisionThickness, ENGINE_LOGIC_CHECKING_DISTANCE),
      groundTextureId,
      true,
      true
    );
    g_entities.push_back(floor2);

    Entity floor3(
      ENTITYTYPE::PLANE,
      glm::vec3(i * ENGINE_LOGIC_CHECKING_DISTANCE, currentGroundLevel, ENGINE_LOGIC_CHECKING_DISTANCE * 2.5f),
      glm::vec3(ENGINE_LOGIC_CHECKING_DISTANCE, planeCollisionThickness, ENGINE_LOGIC_CHECKING_DISTANCE),
      groundTextureId,
      true,
      true
    );
    g_entities.push_back(floor3);

    Entity floor4(
      ENTITYTYPE::PLANE,
      glm::vec3(i * ENGINE_LOGIC_CHECKING_DISTANCE, currentGroundLevel, ENGINE_LOGIC_CHECKING_DISTANCE * 3.5f),
      glm::vec3(ENGINE_LOGIC_CHECKING_DISTANCE, planeCollisionThickness, ENGINE_LOGIC_CHECKING_DISTANCE),
      groundTextureId,
      true,
      true
    );
    g_entities.push_back(floor4);
  }


  unsigned int bricksTextureId = texLoader.load2DTexture("../AncientArcher/cpp/pckgs/primatives/light_bricks.png");

  // ------------ PLACE RANDOMIZED NON-COLLIDING BOXES ------------ //
  bool okayToSpawn = true;
  int countTotalCollisions = 0;
  for (int i = 0; i < 500; ++i) {

    Entity* e;

    if (i % 3 == 0) {
      e = new Entity(
        ENTITYTYPE::CUBE,
        glm::vec3(mearly::NTKR(3.f, ENGINE_LOGIC_CHECKING_DISTANCE * 3.5),
          mearly::NTKR(7.01f, 15.0f), mearly::NTKR(3.f, ENGINE_LOGIC_CHECKING_DISTANCE * 3.5)),
        glm::vec3(mearly::NTKR(2.5f, 4.5f), mearly::NTKR(0.3f, 6.5f), mearly::NTKR(2.5f, 4.5f)),
        bricksTextureId,
        true,
        true
      );
    }
    else if (i % 3 == 1) {
      e = new Entity(
        ENTITYTYPE::CUBE,
        glm::vec3(mearly::NTKR(3.f, ENGINE_LOGIC_CHECKING_DISTANCE * 3.5), mearly::NTKR(2.01f, 8.0f), mearly::NTKR(3.f, ENGINE_LOGIC_CHECKING_DISTANCE * 3.5)),
        glm::vec3(mearly::NTKR(0.5f, 8.0f), mearly::NTKR(0.5f, 5.0f), mearly::NTKR(0.5f, 8.0f)),
        bricksTextureId,
        true,
        true
      );
    }
    else {
      e = new Entity(
        ENTITYTYPE::CUBE,
        glm::vec3(mearly::NTKR(3.f, ENGINE_LOGIC_CHECKING_DISTANCE * 3.5), 1.08f, mearly::NTKR(3.f, ENGINE_LOGIC_CHECKING_DISTANCE * 3.5)),
        glm::vec3(2.f, 2.f, 2.f),
        bricksTextureId,
        true,
        true
      );
    }

    //static CollisionHandler collisionHandler;

    //for (auto const& f : g_entities) {
    //  if (collisionHandler.AABB_vs_AABB_3D(e->collider->impasse, f.collider->impasse)) {
    //    okayToSpawn = false;
    //    countTotalCollisions++;
    //    break;
    //  }
    //}

    if (okayToSpawn) {
      g_entities.push_back(*e);
    }
    //else  // !okayToSpawn
    //{
    //  i--;
    //  okayToSpawn = false;  // try again
    //}

  }
  std::cout << "total collisions: " << countTotalCollisions << "\ntotal entities: " << g_entities.size() << "\n";

  sky = new SkyboxRenderer();
}
