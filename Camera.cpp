#include "Camera.h"

Camera::Camera(bool ghost)
{
  eye = glm::vec3(0.0f,0.0f,0.0f);
  center = glm::vec3(0.0f,0.0f,1.0f);
  nose = glm::vec3(0.0f,1.0f,0.0f);

  angleX = 0;
  angleY = 0;
  this->ghost = ghost;

  for(int i = 0; i < 4; i++)
    keyPressed[i] = false;
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 nose, bool ghost)
{
  this->eye = eye;
  this->center = center;
  this->nose = nose;

  angleX = 0;
  angleY = 0;
  this->ghost = ghost;

  for(int i = 0; i < 4; i++)
    keyPressed[i] = false;
}

glm::mat4 Camera::lookAt()
{
  return glm::lookAt(eye, center, nose);
}

void Camera::keyDown(int key)
{
  if(key >= 0 && key <= 3)
    keyPressed[key] = true;
}

void Camera::keyUp(int key)
{
  if(key >= 0 && key <= 3)
    keyPressed[key] = false;
}

void Camera::update(float interval)
{
  if(keyPressed[0])		// forward
    {
      glm::vec3 dir = ghost ? glm::normalize(center-eye) : glm::normalize(glm::vec3(center.x,eye.y,center.z)-eye);
      eye += dir*interval;
      center += dir*interval;
    }
  if(keyPressed[1])		// backward
    {
      glm::vec3 dir = ghost ? glm::normalize(center-eye) : glm::normalize(glm::vec3(center.x,eye.y,center.z)-eye);
      eye -= dir*interval;
      center -= dir*interval;
    }
  if(keyPressed[2])		// right strafe
    {
      glm::vec3 dir = glm::normalize(center-eye);
      glm::vec3 side = glm::cross(nose,dir);
      eye += side*interval;
      center += side*interval;
    }
  if(keyPressed[3])		// left strafe
    {
      glm::vec3 dir = glm::normalize(center-eye);
      glm::vec3 side = glm::cross(nose,dir);
      eye -= side*interval;
      center -= side*interval;
    }
  if(angleX != 0)		// x rotation
    {
      glm::mat4 rot = glm::translate(glm::mat4(1.0f),eye);
      rot = glm::rotate(rot,angleX*interval*5,nose);
      rot = glm::translate(rot,-eye);
      center = glm::vec3(rot*glm::vec4(center,1.0f));
      angleX = 0;
    }
  if(angleY != 0)		// y rotation
    {
      glm::vec3 dir = glm::normalize(eye-center);
      glm::vec3 side = glm::cross(nose,dir);
      glm::mat4 rot = glm::translate(glm::mat4(1.0f),eye);
      rot = glm::rotate(rot,angleY*interval*5,side);
      rot = glm::translate(rot,-eye);
      glm::vec3 neu = glm::vec3(rot*glm::vec4(center,1.0f));

      glm::vec3 oldDir2d = glm::normalize(glm::vec3(center.x,0.0f,center.z)-glm::vec3(eye.x,0.0f,eye.z));
      glm::vec3 newDir2d = glm::normalize(glm::vec3(neu.x,0.0f,neu.z)-glm::vec3(eye.x,0.0f,eye.z));
      float angle3d = acos(glm::dot(glm::normalize(neu-eye),glm::normalize(nose)))*180/3.14159265;
      if(angle3d > 1 && angle3d < 179 && sgn(oldDir2d.x) == sgn(newDir2d.x) && sgn(oldDir2d.z) == sgn(newDir2d.z))
	center = neu;

      angleY = 0;
    }
}

void Camera::rotX(int angle)
{
  angleX += angle;
}

void Camera::rotY(int angle)
{
  angleY += angle;
}

int Camera::sgn(float value)
{
  return (value == 0 ? 0 : (value > 0 ? 1 : -1));
}
