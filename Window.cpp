#include "Window.h"

Window::Window()
{
  width = 500;
  height = 500;
  left = 0;
  top = 0;
  aspect = (float) width / height;
}

Window::Window(int width, int height)
{
  this->width = width;
  this->height = height;
  left = 0;
  top = 0;
  aspect = (float) width / height;
}

Window::Window(int width, int height, int left, int top)
{
  this->width = width;
  this->height = height;
  this->left = left;
  this->top = top;
  aspect = (float) width / height;
}

void Window::resize(int width, int height)
{
  this->width = width;
  this->height = height;
  aspect = (float) width / height;
}

int Window::getWidth()
{
  return width;
}

int Window::getHeight()
{
  return height;
}

int Window::getLeft()
{
  return left;
}

int Window::getTop()
{
  return top;
}

float Window::getAspect()
{
  return aspect;
}
