#pragma once
#include <glm/glm.hpp>
class PrimativeManager {
public:
  PrimativeManager();
  ~PrimativeManager();
  
  //void drawCube();
  void drawCube(float deltaTime);
  void drawCube(glm::vec3 location);
  void drawCube(glm::vec3 xyzlocation, glm::vec3 xyzsize);

  void drawPlane(glm::vec3 location);
  void drawPlane(glm::vec3 location, glm::vec3 scale);
  void drawPlane(glm::vec3 location, glm::vec3 scale, glm::vec3 rotation);

private:

  void loadCube();
  void loadPlane();

  //std::map<std::string, unsigned int> objects;

  bool cubeLoaded;
  bool planeLoaded;

  unsigned int cubeVAO, cubeVBO;
  unsigned int planeVAO, planeVBO;


};

