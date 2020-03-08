#pragma once
#include <assimp\matrix4x4.h>
#include <assimp\quaternion.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <assimp\color4.h>
namespace mearly
{
class Conversions {
public:
  static glm::mat4 aiMat4_to_glmMat4(const aiMatrix4x4& inMat);
  static glm::vec3 aiVec3_to_glmVec3(const aiVector3D& inVec) noexcept;
  static glm::vec4 aiColor4_to_glmVec4(const aiColor4D& inVec) noexcept;
  static glm::quat aiQuat_to_glmQuat(const aiQuaternion& inQuat) noexcept;
};

}  // end namespace mearly
