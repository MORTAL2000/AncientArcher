/*
InstanceDetails
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
#include <glm\ext\vector_float3.hpp>
#include "ColliderSphere.h"
#include "OGLShader.h"
namespace AA
{
struct InstanceDetails
{
	void updateModelMatrix();

	InstanceDetails(std::shared_ptr<OGLShader> shader, std::shared_ptr<Camera> cam);

	InstanceDetails(std::shared_ptr<OGLShader> shader, std::shared_ptr<Camera> cam, glm::vec3 scale, glm::vec3 rot, glm::vec3 transl);

	//InstanceDetails(int shader, int cameraid);
	//InstanceDetails(int shader, int cameraid, glm::vec3 scale, glm::vec3 rot, glm::vec3 transl);

	// updateModelMatrix uses these
	glm::vec3 Scale = glm::vec3(1);
	glm::vec3 Rotation = glm::vec3(0); // radians on each of xyz
	glm::vec3 Translate = glm::vec3(0);

	// final result
	glm::mat4 ModelMatrix = glm::mat4(1);

	// for if the unit has collision
	ColliderSphere* mColliderSphere = nullptr;

	std::shared_ptr<OGLShader> mShader;
	std::shared_ptr<Camera> mCamera;

};
}  // end namespace AA
