class MyRectangle {
private:
  float x, y, halfSizeX, halfSizeY; //coordinates of rectangle
  uint color; //code of color
  float renderScale;
  float speed; //speed of moving

  //not to write after memory
  uint CheckValue(uint min, uint val, uint max) {
    if (val < min)
      return min;
    else if (val > max)
      return max;
    return val;
  }

  //drawing in computer's axes
  void DrawRectangleInPixels(int x0, int y0, int x1, int y1, int color);

public:
  MyRectangle(float x0, float y0, float halfSizeX0, float halfSizeY0, uint color0, float speed0) {
    x = x0; y = y0; halfSizeX = halfSizeX0; halfSizeY = halfSizeY0;
    renderScale = 0.01f; //const
    color = color0, speed = speed0;
  }

  //drawing in mathematical scales
  void DrawRectangle(Render_t* renderState) {

    x *= (renderState->height * renderScale);
    y *= (renderState->height * renderScale);
    halfSizeX *= (renderState->height * renderScale);
    halfSizeY *= (renderState->height * renderScale);

    x += renderState->width / 2.f;
    y += renderState->height / 2.f;

    int x0 = (int)(x - halfSizeX);
    int y0 = (int)(y - halfSizeY);
    int x1 = (int)(x + halfSizeX);
    int y1 = (int)(y + halfSizeY);

    DrawRectangleInPixels(x0, y0, x1, y1, color);
  }

  //moving object
  void AddToX(float dt) {
    x += (speed * dt);
  }
};