/*
GameObject
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
#include <glm\gtx\transform.hpp>
#include <vector>
#include <memory>
#include <string>
#include "Camera.h"
#include "shaderSys/OGLShader.h"
#include "InstanceDetails.h"
#include "MeshDrawInfo.h"
namespace AA
{
class GameObject
{
public:

	GameObject(const char* path, int camId, int shadId);
	GameObject(const char* path, int camId, int shadId, std::vector<InstanceDetails> details);

	// getters
	const glm::vec3& getLocation() const;
	const glm::vec3& getLocation(int which) const;
	int getModelMatrix(const int& which, glm::mat4& out_mat4) const;
	const int getShaderId() const noexcept;
	const int getCameraId() const noexcept;
	const int getObjectId() const noexcept;
	const std::size_t getInstanceCount() const noexcept;

	// setters
	void setCamera(int id) noexcept;
	void setShader(int id) noexcept;

	// modifiers
	void scaleTo(glm::vec3 amt, int which);
	void scaleTo(glm::vec3 amt);
	void rotateTo(float angle, glm::vec3 axis, int which);
	void rotateTo(float angle, glm::vec3 axis);
	void translateTo(glm::vec3 amt, int which);
	void translateTo(glm::vec3 amt);
	void advanceScale(glm::vec3 amt);
	void advanceScale(glm::vec3 amt, int which);
	void advanceRotation(float angleAmtRadians);
	void advanceRotation(float angleAmtRadians, int which);
	void advanceTranslate(glm::vec3 amt);
	void advanceTranslate(glm::vec3 amt, int which);
	void changeRotateAxis(glm::vec3 axis);
	void changeRotateAxis(glm::vec3 axis, int which);

	bool isSingleInstance() const;

	friend class Loop;

private:

	// only AAWorld can call draw
	void draw(const OGLShader& modelShader);

	int mCameraID = -1;
	int mShaderID = -1;
	int mObjectID = -1;

	std::vector<MeshDrawInfo> mMeshes;
	std::vector<InstanceDetails> mInstanceDetails;  // for instancing multiple objects, sized to the number of this object in our world

	// helpers
	void updateModelMatrix(int which);
};
}  // end namespace AA