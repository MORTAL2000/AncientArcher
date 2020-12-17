/*
CollisionHandler
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
#include "ColliderBox.h"
#include "ColliderSphere.h"
namespace AA
{
class CollisionHandler
{
public:
	static CollisionHandler* Get();

	bool AABB_vs_AABB_3D(const ColliderBox& a, const ColliderBox& b);
	bool point_vs_AABB_3D(const glm::vec3& pt, const ColliderBox& b);
	bool line_vs_AABB_3D(const glm::vec3& startpt, const glm::vec3& endpt, const ColliderBox& b);

	bool sphere_vs_AABB_3D(const ColliderSphere& sphere, const ColliderBox& box);

	bool sphere_vs_Sphere_3D(const ColliderSphere* sphere, const ColliderSphere* other);
	bool point_vs_Sphere_3D(const glm::vec3& point, const ColliderSphere& sphere);
	bool line_vs_Sphere_3D(const glm::vec3& startpoint, const glm::vec3& endpoint, const ColliderSphere& sphere);

private:
	CollisionHandler();
};
} // end namespace AA