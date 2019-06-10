#include "Game.h"
#include <CollisionHandler.h>
#include <glm/glm.hpp>
#include <iostream>
#include <Display.h>
#include <TextureLoader.h>
#include <Global.h>
#include <mearly.h>

//--- GLOBALS ---//
Display g_display(" MMO ", Display::MouseControlType::FPP);
//              Starting Position           YAW    PITCH  FOV
//Camera g_camera(glm::vec3(0.f, 1.0f, 0.f), 0, 0, 45.f);
Camera g_camera(glm::vec3(0.f, 1.0f, 0.f), 0, 0, 75.f);
Lighting g_lighting;
//--- END GLOBALS ---//

Game::Game()
{
	int __textures_allowed = 0, __totalTexturesAllowed = 0;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &__textures_allowed);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &__totalTexturesAllowed);
	std::cout << "//--GRAPHIC CARD INFO--//\nMax textures per shader:  " << __textures_allowed << "\n";
	std::cout << "Max total textures:  " << __totalTexturesAllowed << "\n";

	player = new FirstPersonPlayer();
	prims = new PrimativeRenderer();

  player->addPointLight(glm::vec3(0, 0, 0), prims->getShader());

	sky = new SkyboxRenderer();

	g_lighting.updateConstantLightAmbient(glm::vec3(.12, 0.12, 0.12));
	//g_lighting.updateConstantLightDirection(glm::vec3(-1, -.93, -1));
	g_lighting.updateConstantLightDiffuse(glm::vec3(.48, .48, .48));
	g_lighting.updateConstantLightSpecular(glm::vec3(.3, .3, .3));

	g_lighting.setConstantLight(prims->getShader());

	TextureLoader tLoader;
	unsigned int texIDGrass = tLoader.load2DTexture("../AncientArcher/cpp/pckgs/primatives/grass.png");
	unsigned int texIDDirt = tLoader.load2DTexture("../AncientArcher/cpp/pckgs/primatives/dirt.png");
	unsigned int texIDLightBricks = tLoader.load2DTexture("../AncientArcher/cpp/pckgs/primatives/light_bricks.png");
	unsigned int texIDMosaicBricks = tLoader.load2DTexture("../AncientArcher/cpp/pckgs/primatives/mosaic_bricks.png");


	// grass + dirt layer
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Entity e(
					ENTITYTYPE::CUBE,
					glm::vec3(i * 2, -3.f - .5f * k, j * 2),
					glm::vec3(2.f, .5f, 2.f),
					k < 1 ? texIDGrass : texIDDirt,
					true,
					false
				);
				prims->addToPrimativeEntities(e);
			}
		}
	}

	// bridge
	for (int i = 10; i < 24; i++)
	{
		for (int j = 5; j < 8; j++)
		{
			Entity e(
				ENTITYTYPE::CUBE,
				glm::vec3(i * 2, -3.f, j * 2),
				glm::vec3(2.f, 2.0f, 2.f),
				texIDLightBricks,
				true,
				false
			);

			prims->addToPrimativeEntities(e);
			if (j == 5 || j == 7)  //side railings
			{
				Entity e(
					ENTITYTYPE::CUBE,
					glm::vec3(i * 2.f, -1.75f, j * 2.f),
					glm::vec3(2.0f, 0.5f, .25f),
					texIDLightBricks,
					true,
					false
				);
				prims->addToPrimativeEntities(e);
			}
		}
	}

	// reverse other bridge thingy railings
	for (int i = 10; i < 24; i++)
	{
		for (int j = 5; j < 8; j++)
		{

			if (j == 5 || j == 7)  //secondary
			{
				Entity e(
					ENTITYTYPE::CUBE,
					glm::vec3(
						j * 2,
						-3.5f,
						i * 2),
					glm::vec3(2.0f, 1.0f, 2.0f),
					texIDLightBricks,
					true,
					false
				);
				prims->addToPrimativeEntities(e);
			}
		}
	}

	// other land of maze
	for (int i = 24; i < 44; i++)
	{
    {// l/r walls
      Entity e(
        ENTITYTYPE::CUBE,
        glm::vec3(i * 2, -3.f, 0),
        glm::vec3(2.f, 2.f, 1.f),
        texIDMosaicBricks,
        true,
        false
      );
      prims->addToPrimativeEntities(e);
    }

    {
      Entity e2(
        ENTITYTYPE::CUBE,
        glm::vec3(i * 2, -3.f, 19),
        glm::vec3(2.f, 2.f, 1.f),
        texIDMosaicBricks,
        true,
        false
      );
      prims->addToPrimativeEntities(e2);
    }

		for (int j = 0; j < 10; j++)
		{

			for (int k = 0; k < 2; k++)
			{
				// ground
				Entity e(
					ENTITYTYPE::CUBE,
					glm::vec3(i * 2, -4.f - .5f * k, j * 2),
					glm::vec3(2.f, .5f, 2.f),
					k < 1 ? texIDGrass : texIDDirt,
					true,
					false
				);
				prims->addToPrimativeEntities(e);
			}
		}
	}

	// bridge
	for (int i = 10; i < 24; i++)
	{
		for (int j = 5; j < 8; j++)
		{
			Entity e(
				ENTITYTYPE::CUBE,
				glm::vec3(i * 2, -3.f, j * 2),
				glm::vec3(2.f, 2.0f, 2.f),
				texIDLightBricks,
				true,
				false
			);
			prims->addToPrimativeEntities(e);
			if (j == 5 || j == 7)  //side railings
			{
				Entity e(
					ENTITYTYPE::SPHERE,
					glm::vec3(i * 2, -2.f, j * 2),
					glm::vec3(2.0f, 1.0f, .5f),
					texIDLightBricks,
					true,
					false
				);
				prims->addToPrimativeEntities(e);
			}
		}
	}

	// few random blocks off to the side
	for (int i = 24; i < 44; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Entity e(
					ENTITYTYPE::CUBE,
					glm::vec3(i * 2, -4.f - .5f * k, j * 2),
					glm::vec3(2.f, .5f, 2.f),
					k < 1 ? texIDGrass : texIDDirt,
					true,
					false
				);
				prims->addToPrimativeEntities(e);
			}
		}
	}

	//Moving Blocks
	for (int i = 0; i < 4; i++)  //ground
	{
		for (int j = 0; j < 5; j++)
		{
			Entity e(
				ENTITYTYPE::CUBE,
				glm::vec3(48.f, (1.f * j) - 3.25f, (1.f* i) + 9.f),
				glm::vec3(1.f, 1.f, 1.f),
				texIDMosaicBricks,
				true,
				false
			);
			prims->addToMovingEntities(e);

		}
	}

}
