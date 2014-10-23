#ifndef SCONY_CAMERA
#define SCONY_CAMERA

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>

class Camera
{
  glm::vec3 eye;
  glm::vec3 center;
  glm::vec3 nose;
  int angleX;
  int angleY;
  bool ghost;
  bool keyPressed[4];
  int sgn(float value);
public:
  Camera(bool ghost = true);
  Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 nose, bool ghost = true);
  glm::mat4 lookAt();
  void keyDown(int key);
  void keyUp(int key);
  void update(float interval);
  void rotX(int angle);
  void rotY(int angle);
};

#endif
