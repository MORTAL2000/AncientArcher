#pragma once
#include "../../pckgs/skybox/SkyboxRenderer.h"
#include "../../pckgs/primatives/PrimativeRenderer.h"
#include "../../pckgs/monospaceFont/TextRenderer.h"
#include "../pckgs/sideScrollerPlayer/SideScrollPlayer.h"
#include "../pckgs/masterRenderer/MasterRenderer.h"

class Game {
public:

  SideScrollPlayer* sideScrollPlayer;
  PrimativeRenderer* primativeRenderer;
  SkyboxRenderer* skyboxRenderer;
  TextRenderer* textRenderer;

  MasterRenderer masterRenderer;

  Game();

  void mainLoop();

private:

  float lastFrame = 0.0f;

  float deltaTime = 0.0f;

};
