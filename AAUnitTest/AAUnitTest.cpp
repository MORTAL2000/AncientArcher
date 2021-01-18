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

	TEST_METHOD(aBaseRunTest)
	{
		Assert::AreEqual(AA::Engine->Run(), 0);
	}

	TEST_METHOD(BaseCamAndModelTest)
	{
		int cam = AA::Engine->AddCamera(AA::Engine->GetWindowWidth(), AA::Engine->GetWindowHeight());
		int shader = AA::Engine->AddShader(AA::SHADERTYPE::DIFF);
		AA::Engine->AddObject("E:\\storage\\Models\\dovecote.fbx", cam, shader);
		Assert::AreEqual(AA::Engine->Run(), 0);
	}

	//TEST_METHOD(ScreenFullScreenTest)
	//{
	//	Logger::WriteMessage("Setting Screen to FullScreen.");
	//	AA::Engine->SetWindowSize('f');
	//	Assert::AreEqual(1920, AA::Engine->GetWindowWidth());
	//	Assert::AreEqual(1080, AA::Engine->GetWindowHeight());
	//}

};
}
