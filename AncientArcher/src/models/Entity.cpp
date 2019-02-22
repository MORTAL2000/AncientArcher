#include "Entity.h"

Entity::Entity(ENTITYTYPE t, glm::vec3 loc, glm::vec3 sc, int texID, bool isImpassable)
{
  gameItem.type = t;
  gameItem.location[0] = loc.x;
  gameItem.location[1] = loc.y;
  gameItem.location[2] = loc.z;
  gameItem.scale[0] = sc.x;
  gameItem.scale[1] = sc.y;
  gameItem.scale[2] = sc.z;
  gameItem.textureID = texID;
  if (isImpassable) {
    collider = new Collider(loc, sc);
  }
  else {
    collider = nullptr;
  }
}

void Entity::moveby(glm::vec3 amount)
{
  this->gameItem.location[0] += amount.x;
  this->gameItem.location[1] += amount.y;
  this->gameItem.location[2] += amount.z;
}