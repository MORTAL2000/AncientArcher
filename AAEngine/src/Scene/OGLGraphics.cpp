/*
OGLGraphics
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
#include "../../include/Scene/OGLGraphics.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <stb_image.h>
#include <glad/glad.h>
#include <memory>
#include <string>
#include <cstddef>
#include "../../include/Scene/GameObject.h"
#include <iostream>
//#include "Vertex.h"

namespace AA
{
OGLGraphics* OGLGraphics::getInstance()
{
	static OGLGraphics* OGLgraphics = new OGLGraphics();
	return OGLgraphics;
}
OGLGraphics::OGLGraphics() {};

/** Render the meshes with the shader. Assumes Camera View Matrix is already set.
 *  @param[in] meshes to draw.
 *  @param[in] details about instances of the mesh to also render.
 *  @param[in] shader to use for mesh rendering pipeline.
 */
void OGLGraphics::Render(const std::vector<MeshDrawInfo>& meshes, const std::vector<InstanceDetails>& details)
{
	// turn on depth test in case something else turned it off
	glEnable(GL_DEPTH_TEST);

	// draw all the instances with their differing model matrices and shaders
	for (const auto& d : details)
	{
		// if different shader, switch to it, update it
		static std::shared_ptr<OGLShader> last_shader;
		if (last_shader != d.mShader)  // first instance should always set this to start
		{
			last_shader.reset();
			last_shader = d.mShader;
			last_shader->use();
			last_shader->setMat4("model", d.ModelMatrix);
			for (const auto& m : meshes)
			{
				uint32_t i = 0;
				for (const auto& texs : m.textureDrawIds)
				{
					glActiveTexture(GL_TEXTURE0 + i);
					const std::string tex_type = texs.second;
					glUniform1i(glGetUniformLocation(last_shader->GetID(), ("material." + tex_type).c_str()), i);
					glBindTexture(GL_TEXTURE_2D, texs.first);
				}
				glBindVertexArray(m.vao);
				glDrawElements(GL_TRIANGLES, m.numElements, GL_UNSIGNED_INT, nullptr);
				i++;
			}
#ifdef _DEBUG
			std::cout << "draw from diff shader\n";
#endif
		}
		else // same shader
		{
			last_shader->use();
			last_shader->setMat4("model", d.ModelMatrix);
			for (const auto& m : meshes)
			{
				uint32_t i = 0;
				for (const auto& texs : m.textureDrawIds)
				{
					glActiveTexture(GL_TEXTURE0 + i);
					const std::string tex_type = texs.second;
					glUniform1i(glGetUniformLocation(last_shader->GetID(), ("material." + tex_type).c_str()), i);
					glBindTexture(GL_TEXTURE_2D, texs.first);
				}
				glBindVertexArray(m.vao);
				glDrawElements(GL_TRIANGLES, m.numElements, GL_UNSIGNED_INT, nullptr);
				i++;
			}
#ifdef _DEBUG
			std::cout << "draw from last shader\n";
#endif
		}
	}

	glBindVertexArray(0);          // unbind vert array
	glActiveTexture(GL_TEXTURE0);  // reset to first texture
}
}  // end namespace AA