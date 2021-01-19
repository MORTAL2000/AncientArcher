#include "pch.h"
#include "CppUnitTest.h"
#include "CppUnitTestLogger.h"
#include <AncientArcher.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AAUnitTest
{
TEST_CLASS(AAUnitTest)
{
public:

	TEST_METHOD(A_BaseRun)
	{
		static float timeholder_A = 0.f;

		AA::Engine->AddToDeltaUpdate([](float dt) {
			timeholder_A += dt;
			if (timeholder_A > 3.f)
			{
				AA::Engine->Shutdown();
			}
			});
		Assert::AreEqual(AA::Engine->Run(), 0);
	}

	TEST_METHOD(B_BaseReset)
	{
		AA::Engine->SoftReset();

		static float timeholder_B = 0.f;

		AA::Engine->AddToDeltaUpdate([](float dt) {
			timeholder_B += dt;
			if (timeholder_B > 3.f)
			{
				AA::Engine->Shutdown();
			}
			});
		Assert::AreEqual(AA::Engine->Run(), 0);
	}

	TEST_METHOD(C_BaseCamAndModelTest)
	{
		AA::Engine->SoftReset();
		static int cam = AA::Engine->AddCamera(AA::Engine->GetWindowWidth(), AA::Engine->GetWindowHeight());
		int shader = AA::Engine->AddShader(AA::SHADERTYPE::DIFF);

		//AA::Engine->AddObject("E:\\storage\\Models\\dovecote.fbx", cam, shader);

		int dovecote = AA::Engine->AddObject("E:\\storage\\Models\\dovecote.fbx", cam, shader);
		AA::Engine->GetGameObject(dovecote).setTranslation(glm::vec3(0, 0, 0));

		//AA::Engine->GetGameObject(chicken).setScale(glm::vec3(.2,.2,.2));

		AA::Engine->GetCamera(cam).setCurrentPosition(glm::vec3(0, 250, 0));
		AA::Engine->GetCamera(cam).setCurrentPitch(0.f);
		AA::Engine->GetCamera(cam).setCurrentYaw(90.f);

		//AA::Engine->SetMaxRenderDistance(cam, 4000.f);

		AA::Engine->AddToDeltaUpdate([](float dt) {
			//AA::Engine->GetCamera(cam).shiftYawAndPitch(dt*100, 0);
			AA::Engine->GetCamera(cam).shiftCurrentPosition(glm::vec3(0, 0, -dt * 200));
			if (AA::Engine->GetCamera(cam).getLocation().z < -2000)
			{
				AA::Engine->Shutdown();
			}
			});

		Assert::AreEqual(AA::Engine->Run(), 0);

	}
};
}
