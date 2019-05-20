#include <AAEngine.h>
#include "Game.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

extern Camera camera;

Game::Game() {

  // ----------- GRAPHICS CARD INFORMATION --------- //

  int __textures_allowed = 0;
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &__textures_allowed);
  std::cout << "//--GRAPHIC CARD INFO--//\nMax textures per shader:  " << __textures_allowed << "\n";

  int __totalTexturesAllowed = 0;
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &__totalTexturesAllowed);
  std::cout << "Max total textures:  " << __totalTexturesAllowed << "\n";


  // ---------- FIRST PERSON PLAYER ---------- //
  player = new Player(100.0f);


  // ---------- PRELOAD ENVIRORNMENT DETAILS ---------- //
  primativeRenderer = new PrimativeRenderer();

  player->addPointLight(*camera.getPosition(), primativeRenderer->getShader());

  TextureLoader texLoader;

  unsigned int lightBricksTexID = texLoader.load2DTexture("../AncientArcher/cpp/pckgs/primatives/light_bricks.png");

  // -------- LOAD WORLD BLOCKS --------- //
  Entity* e;
  for (int i = 0; i < 1000; i += 2)
  {
    e = new Entity(
      ENTITYTYPE::CUBE,
      glm::vec3(i, -0.8f, 0.f),
      glm::vec3(2.0f, 1.0f, 2.0f),
      lightBricksTexID,
      true
    );

    primativeRenderer->addToPrimativeEntities(*e);
    delete e;
    e = nullptr;
  }

  // --- TEXT --- //
  textRenderer = new TextRenderer();
  textRenderer->init(
    "../AncientArcher/cpp/pckgs/monospaceFont/bitmaps/monospace_bitmap_font_green.png",                   // path
    48,                                                                                                   // ea glyph width
    94,                                                                                                   // each glyph height
    R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.@!#$%&*()_+=<>|[]{}/\`^;:'"-~ )",   // list of all chars in order
    16                                                                                                    // glyphs per line
    );
  

  // ---- LOAD SKYBOX ---- //
  std::vector<std::string> skyboxFiles =
  {
  "../AncientArcher/cpp/pckgs/skybox/heresy/skybox_heresy_right.png",
  "../AncientArcher/cpp/pckgs/skybox/heresy/skybox_heresy_left.png",
  "../AncientArcher/cpp/pckgs/skybox/heresy/skybox_heresy_top.png",
  "../AncientArcher/cpp/pckgs/skybox/heresy/skybox_heresy_bottom.png",
  "../AncientArcher/cpp/pckgs/skybox/heresy/skybox_heresy_front.png",
  "../AncientArcher/cpp/pckgs/skybox/heresy/skybox_heresy_back.png"
  };

  skyboxRenderer = new SkyboxRenderer(skyboxFiles);

}
