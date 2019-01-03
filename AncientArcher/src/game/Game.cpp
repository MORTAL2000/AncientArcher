#include "Game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../camera/Camera.h"
#include "../displayManager/Display.h"
#include "../controls/Controls.h"
#include "../shaders/Shader.h"
#include "../util/TextureBank.h"
#include "../lighting/Lighting.h"
#include "../Constraints.h"


Display display;
Shader shader("../AncientArcher/src/shaders/vertex.shader", "../AncientArcher/src/shaders/fragment.shader");
Camera camera;
Controls controls;
TextureBank texBank;
Lighting lights;

Game::Game() {

  //display = new Display();

  //camera = new Camera();

  //controls = new Controls();   //default controls

  //shader = new Shader("../AncientArcher/shaders/vertex.shader", "../AncientArcher/shaders/fragment.shader", "../AncientArcher/shaders/geometry.shader");

  player = new Player();   //default character

  /* load 16 textures */
  texBank.loadTexture("../AncientArcher/res/texture/00-pixelized_grass.png");
  texBank.loadTexture("../AncientArcher/res/texture/01-pixelized_stone.png");
  texBank.loadTexture("../AncientArcher/res/texture/02-pixelized_wood.png");
  texBank.loadTexture("../AncientArcher/res/texture/03-pixelized_shrub.png");
  texBank.loadTexture("../AncientArcher/res/texture/04-pixelized_portal.png");
  texBank.loadTexture("../AncientArcher/res/texture/05-pixelized_darkstone.png");
  texBank.loadTexture("../AncientArcher/res/texture/06-pixelized_water_droplet.png");
  texBank.loadTexture("../AncientArcher/res/texture/07-pixelized_gravel.png");
  texBank.loadTexture("../AncientArcher/res/texture/08-pixelized_water.png");
  texBank.loadTexture("../AncientArcher/res/texture/09-pixelized_player.png");
  texBank.loadTexture("../AncientArcher/res/texture/10-pixelized_mud.png");
  texBank.loadTexture("../AncientArcher/res/texture/11-pixelized_darkwood.png");
  texBank.loadTexture("../AncientArcher/res/texture/12-pickup_speedboost.png");
  texBank.loadTexture("../AncientArcher/res/texture/13-pixelized_snow.png");
  texBank.loadTexture("../AncientArcher/res/texture/14-maze_metal.png");
  texBank.loadTexture("../AncientArcher/res/texture/15-pickup_attackboost.png");

  // only render the objects not line of sight blocked by other objects 
  //glEnable(GL_CULL_FACE);

  renderer.enableGLDepthTest();

  camera.updateProjectionMatrix();

  shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);  // white light
  //shader.setVec3("lightColor", 1.0f, 0.2f, 0.2f);  // red light
  //shader.setVec3("lightColor", 0.35f, 0.35f, 0.5f);  // asdf light
  //shader.setVec3("lightPos", world_width/2, world_height - 1.0f, world_width/2);  // top light
}

Game::~Game() {

}
