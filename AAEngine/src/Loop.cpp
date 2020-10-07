/*
Loop
----------------------------------------------------------------------
Copyright (c) 2019-2020, Matthew Early matthewjearly@gmail.com
All rights reserved.
Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the
following conditions are met:
* Redistributions of source code must retain the above
	copyright notice, this list of conditions and the
	following disclaimer.
* Redistributions in binary form must reproduce the above
	copyright notice, this list of conditions and the
	following disclaimer in the documentation and/or other
	materials provided with the distribution.
* Neither the name of the Matthew Early, nor the names of its
	contributors may be used to endorse or promote products
	derived from this software without specific prior
	written permission of the assimp team.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
----------------------------------------------------------------------
*/
#include "../include/Loop.h"
#include "../include/Controls.h"
#include "../include/Camera.h"
#include "../include/vendor/glad/glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

namespace AA
{
Loop* Loop::getMainLoop()
{
	static Loop* loop = new Loop();
	return loop;
}
int Loop::runMainLoop()
{
	begin();
	while (!glfwWindowShouldClose(DISPLAY->getWindow()))
	{
		deltaUpdate();
		render();
	}
	return 0;
}

void Loop::shutdown()
{
	//DISPLAY->resetStateDataToDefault();
	DISPLAY->closeWindow();
}

Loop::Loop()
{
	initEngine();
}

//Loop::Loop(const char* title)
//{
//	initEngine();
//	setWindowTitle(title);
//}

const Camera& Loop::getCamera(int camId) const
{
	for (const auto& cam : mCameras)
	{
		if (cam.getID() == camId)
		{
			return cam;
		}
	}

	// if it didn't find it and return above ^^^^^^^^  show error message in console
	//std::cout << "cam ID by the ID [" << camId << "] was not found. unable to get const AACamera\n";

	exit(-1);
}

Camera& Loop::getCamera(int camId)
{
	for (auto& cam : mCameras)
	{
		if (cam.getID() == camId)
		{
			return cam;
		}
	}

	// if it didn't find it and return above ^^^^^^^^  show error message in console
	//std::cout << "cam ID by the ID [" << camId << "] was not found. unable to get AACamera\n";
	exit(-1);
}

const OGLShader& Loop::getShader(int shadId) const
{
	for (const auto& shad : mShaders)
	{
		if (shad.getID() == shadId)
		{
			return shad;
		}
	}

	// if it didn't find it and return above ^^^^^^^^  show error message in console
	//std::cout << "shad ID by the ID [" << shadId << "] was not found.\n";
	exit(-1);
}

OGLShader& Loop::getShader(int shadId)
{
	for (auto& shad : mShaders)
	{
		if (shad.getID() == shadId)
		{
			return shad;
		}
	}

	// if it didn't find it and return above ^^^^^^^^  show error message in console
	//std::cout << "shad ID by the ID [" << shadId << "] was not found.\n";
	exit(-1);
}

const GameObject& Loop::getGameObject(int objId) const
{
	for (const auto& obj : mGameObjects)
	{
		if (obj.getObjectId() == objId)
		{
			return obj;
		}
	}

	// if it didn't find it and return above ^^^^^^^^  show error message in console
	//std::cout << "game object ID by the ID [" << objId << "] was not found.\n";
	exit(-1);
}

GameObject& Loop::getGameObject(int objId)
{
	for (auto& obj : mGameObjects)
	{
		if (obj.getObjectId() == objId)
		{
			return obj;
		}
	}

	// if it didn't find it and return above ^^^^^^^^  show error message in console
	//std::cout << "game object ID by the ID [" << objId << "] was not found.\n";
	exit(-1);
}

const MouseReporting Loop::getMouseReportingMode() const
{
	return DISPLAY->mMouseReporting;
}

const int Loop::getCursorMode() const
{
	return DISPLAY->getCursorMode();
}
int Loop::addCamera()
{
	Camera tmpCam;
	const int return_id = tmpCam.getID();

	mCameras.push_back(tmpCam);

	return return_id;
}

int Loop::addShader(const char* vert_path, const char* frag_path)
{
	const OGLShader tmpShader(vert_path, frag_path);
	const int return_id = tmpShader.getID();
	mShaders.push_back(tmpShader);
	return return_id;
}

int Loop::addObject(const char* path, int camId, int shadId)
{
	GameObject tmpObject(path, camId, shadId);
	const int return_id = tmpObject.getObjectId();

	mGameObjects.push_back(tmpObject);

	return return_id;
}

int Loop::addObject(const char* path, int cam_id, int shad_id, const std::vector<InstanceDetails>& details)
{
	// todo: optimize. check if it is an object we already have loaded and use it again if so

	GameObject tmpObject(path, cam_id, shad_id, details);

	const int return_id = tmpObject.getObjectId();

	mGameObjects.push_back(tmpObject);

	return return_id;
}

void Loop::setSkybox(const std::shared_ptr<Skybox>& skybox) noexcept
{
	mSkybox = skybox;
}

void Loop::addToOnBegin(void(*function)())
{
	onBegin.push_back(function);
}

void Loop::addToDeltaUpdate(void(*function)(float))
{
	onDeltaUpdate.push_back(function);
}

void Loop::addToTimedOutKeyHandling(bool(*function)(KeyboardInput&))
{
	onTimeoutKeyHandling.push_back(function);
}

void Loop::addToScrollHandling(void(*function)(ScrollInput&))
{
	onScrollHandling.push_back(function);
}

void Loop::addToKeyHandling(void(*function)(KeyboardInput&))
{
	onKeyHandling.push_back(function);
}

void Loop::addToMouseHandling(void(*function)(MouseInput&))
{
	onMouseHandling.push_back(function);
}

void Loop::addToUpdate(void(*function)())
{
	onUpdate.push_back(function);
}

void Loop::addToSlowUpdate(void(*function)())
{
	onSlowDeltaUpdate.push_back(function);
}

void Loop::setCursorToEnabled(bool isHardwareRendered)
{
	if (isHardwareRendered)
	{
		DISPLAY->setCursorToHidden();
	}
	else
	{
		DISPLAY->setCursorToVisible();
	}
}

void Loop::setCursorToDisabled()
{
	DISPLAY->setCursorToDisabled();
}
void Loop::setToPerspectiveMouseHandling()
{
	DISPLAY->setCurorPosToPerspectiveCalc();
}
void Loop::setToStandardMouseHandling()
{
	DISPLAY->setCurorPosToStandardCalc();
}
void Loop::setWindowTitle(const char* title)
{
	DISPLAY->setWindowTitle(title);
}
void Loop::setRenderDistance(int camId, float amt) noexcept
{
	for (auto& cam : mCameras)
	{
		if (cam.getID() == camId)
		{
			cam.setRenderDistance(amt);
			return;
		}
	}

	// if code gets here there is an error, camId not found
	//std::cout << "cam not found for id [" << camId << "].\n";
}

void Loop::setProjectionMatrix(int shadId, int camId)
{
	getShader(shadId).use();
	getShader(shadId).setMat4("projection", getCamera(camId).getProjectionMatrix());
}

// -- PRIVATE FUNCTIONS --

void Loop::begin()
{
	DISPLAY->keepWindowOpen();

	for (auto& oB : onBegin)
	{
		oB();
	}

	setProjectionMatToAllShadersFromFirstCam_hack();
}

void Loop::deltaUpdate()
{
	CONTROLS->pullButtonStateEvents();

	// update engine run delta times
	mCurrentFrameTime = static_cast<float>(glfwGetTime());
	mDeltaTime = mCurrentFrameTime - mLastFrameTime;
	mLastFrameTime = mCurrentFrameTime;

	// go through all updates that need access to delta time
	for (auto& oDU : onDeltaUpdate)
	{
		oDU(mDeltaTime);
	}

	// process keyboard input
	for (auto& oKH : onKeyHandling) { oKH(CONTROLS->mButtonState); }

	// absorb scroll wheel
	for (auto& oSH : onScrollHandling) { oSH(CONTROLS->mMouseWheelScroll); }

	// reset scroll wheel to 0's after processing scroll wheel
	CONTROLS->mMouseWheelScroll.xOffset = 0;
	CONTROLS->mMouseWheelScroll.yOffset = 0;

	// handle mouse position
	for (auto& oMH : onMouseHandling) { oMH(CONTROLS->mMousePosition); }

	// Snap cursor to the middle of the screen if it is in perspective and cursor is disabled (FPP mode)
	if (getMouseReportingMode() == MouseReporting::PERSPECTIVE && getCursorMode() == GLFW_CURSOR_DISABLED)
	{
		//deb(CONTROLS->mMousePosition.xOffset);
		//deb(CONTROLS->mMousePosition.yOffset);

		CONTROLS->mMousePosition.xOffset = 0;
		CONTROLS->mMousePosition.yOffset = 0;
	}
	//else if (getMouseReportingMode() == MouseReporting::STANDARD && getCursorMode() == GLFW_CURSOR_NORMAL) // standard and normal
	//{
		// dont snap the position
		//showmousepos(PointerXOffset, PointerYOffset);
		//std::cout << "X: " << PointerXOffset << " Y: " << PointerYOffset << '\n';
	//}

	// run through user prefered updates
	for (auto& oU : onUpdate) { oU(); }

	// delayed updates for things you don't want spammed.
	// update accum time for delayed updates
	mSlowUpdateTimeout += mDeltaTime;
	// check to see if its time to process delayed updates
	if (mSlowUpdateTimeout > mSlowUpdateWaitLength)
	{
		// process all delayed updates
		for (auto& oSU : onSlowDeltaUpdate)
		{
			oSU();
		}
		// we should also process whether the window size changed here
		if (DISPLAY->mWindowSizeChanged)
		{
			// notify shader/cams
			setProjectionMatToAllShadersFromFirstCam_hack();

			// don't process again
			DISPLAY->mWindowSizeChanged = false;
		}
		// reset timeout length to 0
		mSlowUpdateTimeout = 0.f;
	}

	// needs updated, we'll use it in update with keyboard functions before the loop is done.
	// note that the keyboard processing cant be here because we have yet to run processSystemKeys()
	mNonSpammableKeysTimeout += mDeltaTime;

	// only be executable after a timeout has been met, sort of like a cooldown
	if (mNonSpammableKeysTimeout > mNoSpamWaitLength)
	{
		// process unspammable keys
		for (auto& oTOK : onTimeoutKeyHandling)
		{
			// if we get a true we stop processing
			if (oTOK(CONTROLS->mButtonState)) {
				//std::cout << "timeout key press detected. reseting timeoutkeytimer\n";
				mNonSpammableKeysTimeout = 0.f;
				break;
			}
		}
	}
}

void Loop::render()
{
	DISPLAY->clearBackBuffer();

	for (auto& obj : mGameObjects)
	{
		// get the id of the shader for this object
		const int shaderID = obj.getShaderId();

		// switch to the shader
		getShader(shaderID).use();

		// get the camera id for this object
		const int cameraID = obj.getCameraId();

		// set the view matrix from the cam for this object
		getShader(shaderID).setMat4("view", getCamera(cameraID).getViewMatrix());

		// draw using the shader for it
		obj.draw(getShader(shaderID));
	}

	// draw skybox if one was specified
	if (mSkybox) { mSkybox->render(mCameras.front()); }

	DISPLAY->swapWindowBuffers();
}

void Loop::initEngine()
{
	resetEngine();

	DISPLAY->initFromEngine();

	// Init OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  // init glad (for opengl context) -- must be after initDisplay
	{
		//std::cout << "failed to init glad @ file " __FILE__ << " line " << __LINE__ << '\n';
		exit(-1);
	}
}

void Loop::resetEngine() noexcept
{
	//clear all vectors
	mCameras.clear();
	mShaders.clear();
	mGameObjects.clear();
	onBegin.clear();
	onDeltaUpdate.clear();
	onKeyHandling.clear();
	onTimeoutKeyHandling.clear();
	onScrollHandling.clear();
	onMouseHandling.clear();
	onUpdate.clear();
	onSlowDeltaUpdate.clear();

	// reset all state data
	mNonSpammableKeysTimeout = 0.f;
	mSlowUpdateTimeout = 0.f;
	mNoSpamWaitLength = .5667f;
	mSlowUpdateWaitLength = .5667f;

	mLastFrameTime = 0.f;
	mCurrentFrameTime = 0.f;
	mDeltaTime = 0.f;
}

void Loop::setProjectionMatToAllShadersFromFirstCam_hack()
{
	// set proj matries hack from first cam
	for (auto& shad : mShaders)
	{
		//shad.setMat4("projection", mCameras.front().getProjectionMatrix());
		const int sID = shad.getID();
		//std::cout << "shad id: " << sID << '\n';

		const int cID = mCameras.front().getID();
		//std::cout << "shad id: " << sID << '\n';

		setProjectionMatrix(sID, cID);  //set shader (sID) from cam (cID)
	}

	// if there is a skybox
	if (mSkybox)
	{
		// if there is a camera
		if (mCameras.size() > 0) {
			// set the projection matrix on the skybox from the first cam proj matrix
			mSkybox->setProjectionMatrix(mCameras.front());
		}
	}
}
}  // end namespace AA