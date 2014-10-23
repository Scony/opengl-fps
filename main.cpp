#include <GL/gl.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Bar.h"
#include "Window.h"
#include "Camera.h"

Window window;
Bar fpsBar;

// camera(eye,center,nose,ghost_mode_on?)
Camera camera(glm::vec3(0.0f,0.0f,0.0f),
	      glm::vec3(0.0f,0.0f,5.0f),
	      glm::vec3(0.0f,1.0f,0.0f),
	      false);		// try true

bool flag = false;

void displayFrame(void)
{
  glClearColor(1,1,1,1);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3d(0.0f,0.0f,0.0f);
  glm::mat4 M = glm::mat4(1.0f);
  M = glm::translate(M,glm::vec3(0.0f,0.0f,5.0f));
  glm::mat4 V = camera.lookAt();
  glm::mat4 P = glm::perspective(50.0f,window.getAspect(),1.0f,100.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(P));
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(V*M));

  if(flag)
    glutSolidCube(1.0f);
  else
    glutWireCube(1.0f);

  fpsBar.display();

  glutSwapBuffers();
}

void nextFrame(void)
{
  static int lastTime = 0;
  int actTime = glutGet(GLUT_ELAPSED_TIME);
  int interval = actTime - lastTime;
  lastTime = actTime;

  fpsBar.update(interval/1000.0);
  camera.update(interval/1000.0);

  glutPostRedisplay();
}

void reShape(int width, int height)
{
  glViewport(0,0,width,height);
  window.resize(width,height);
}

void keyDown(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 'f':
      glutFullScreen();
      break;
    case 'x':
      exit(0);
      break;
    case 'v':
      flag = true;
      break;
    case 'w':
      camera.keyDown(0);
      break;
    case 's':
      camera.keyDown(1);
      break;
    case 'a':
      camera.keyDown(2);
      break;
    case 'd':
      camera.keyDown(3);
      break;
    }
}

void keyUp(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 'v':
      flag = false;
      break;
    case 'w':
      camera.keyUp(0);
      break;
    case 's':
      camera.keyUp(1);
      break;
    case 'a':
      camera.keyUp(2);
      break;
    case 'd':
      camera.keyUp(3);
      break;
    }
}

void mouseMotion(int x, int y)
{
  bool warpPointer = false;
  if(x != window.getWidth()/2)
    {
      camera.rotX(window.getWidth()/2-x);
      x = window.getWidth()/2;
      warpPointer = true;
    }
  if(y != window.getHeight()/2)
    {
      camera.rotY(window.getHeight()/2-y);
      y = window.getHeight()/2;
      warpPointer = true;
    }
  if(warpPointer)
    glutWarpPointer(x,y);
}

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(window.getWidth(),window.getHeight());
  glutInitWindowPosition(window.getLeft(),window.getTop());
  glutCreateWindow("Program OpenGL");        
  glutDisplayFunc(displayFrame);
  glutIdleFunc(nextFrame);
  glutReshapeFunc(reShape);
  glutWarpPointer(window.getWidth()/2, window.getHeight()/2);
  glutPassiveMotionFunc(mouseMotion);
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutIgnoreKeyRepeat(1);
  glutSetCursor(GLUT_CURSOR_NONE);
		
  glutMainLoop();
  return 0;
}
