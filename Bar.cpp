#include "Bar.h"

Bar::Bar()
{
  fps = 0;
  time = 0;
  frames = 0;
}

void Bar::update(float time)
{
  this->time += time;
  frames++;
  if(this->time > 1)
    {
      fps = frames / this->time--;
      frames -= fps;
    }
}

void Bar::display()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-2.0f,2.0f,-2.0f,2.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(glm::translate(glm::mat4(1.0f),glm::vec3(0,0,0.9999f))));
  glColor3d(0.0f,0.0f,0.0f);

  float tmp [] =
    {
      -2,1.7, -2,2, 2,2, 2,1.7
    };
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2,GL_FLOAT,0,tmp);
  glDrawArrays(GL_QUADS,0,4);
  glDisableClientState(GL_VERTEX_ARRAY);

  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(glm::translate(glm::mat4(1.0f),glm::vec3(0,0,1))));
  char napis[255];
  sprintf(napis,"FPS: %.2f",fps);
  glColor3d(1.0f,1.0f,0.0f);
  drawString(-2,1.8,napis);
}

void Bar::drawString(float x, float y, char * string)
{
  glRasterPos2f(x,y);
  int len = strlen(string);
  for(int i = 0; i < len; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
}
