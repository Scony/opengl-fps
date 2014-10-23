#ifndef BAR_H
#define BAR_H

#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>

class Bar
{
  float fps;
  float time;
  float frames;
  void drawString(float x, float y, char * string);
public:
  Bar();
  void update(float time);
  void display();
};

#endif
