/*
Camera
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
#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace AA
{
enum class RenderProjection { ORTHO, PERSPECTIVE };

class Camera
{
public:
	Camera(int width, int height);
	void UpdateCameraVectors();

	// setters
	void SetViewportSize(int w, int h);
	void SetToPerspective() noexcept;
	void SetCurrentPosition(glm::vec3 pos);
	void SetCurrentPitch(float pitch);
	void SetCurrentYaw(float yaw);
	void ShiftCurrentPosition(const glm::vec3& offset);
	void ShiftYawAndPitch(float yawOffset, float pitchOffset);

	// experimental
	void SetToOrtho() noexcept;
	void SetOrthoFieldSize(float left, float right, float bottom, float top) noexcept;
	void SetOrthoFieldSize(glm::vec4 lrbt) noexcept;
	void SetMaxRenderDistance(float distance) noexcept;
	void ResetViewportVars();

	// getters
	const glm::vec3& GetLocation() const noexcept;
	glm::mat4        GetViewMatrix() const;
	glm::mat4        GetProjectionMatrix() const;
	const glm::vec3* GetPosition() const noexcept;
	const glm::vec3* GetFront() const noexcept;
	const glm::vec3* GetRight() const noexcept;
	float            GetYaw() const noexcept;
	float            GetPitch() const noexcept;
	float            GetRenderDistance() const noexcept;

	const int&       GetID() const noexcept;

private:
	int              mViewportWidth;
	int              mViewportHeight;
	glm::vec3        mFront;
	glm::vec3        mRight;
	glm::vec3        mUp;
	glm::vec3        mPosition;
	float            mFieldOfView;
	float            mYaw;
	float            mPitch;
	float            mMaxRenderDistance;
	bool             mProjectionChanged;
	glm::vec4        mOrthoFieldSize;
	int              mUniqueViewportID;
	RenderProjection mRenderProjection;

};
} // end namespace AA
