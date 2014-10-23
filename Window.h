#ifndef WINDOW_H
#define WINDOW_H

class Window
{
  int width;
  int height;
  int left;
  int top;
  float aspect;
public:
  Window();
  Window(int width, int height);
  Window(int width, int height, int left, int top);
  void resize(int width, int height);
  int getWidth();
  int getHeight();
  int getLeft();
  int getTop();
  float getAspect();
};

#endif
