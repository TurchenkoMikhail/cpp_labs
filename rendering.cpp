//fill screen with one color
void ClearScreen(uint color){
uint* pixel = (uint*)renderState.buff; //first pixel
  for (int y = 0; y < renderState.height; y++) {
    for (int x = 0; x < renderState.width; x++) {
      *pixel++ = color;
    }
  }
}

//not to write after memory
uint CheckValue(uint min, uint val, uint max) {
  if (val < min)
    return min;
  else if (val > max)
    return max;
  return val;
}

void DrawRectangleInPixels(int x0, int y0, int x1, int y1, uint color) {

  //checking values
  x0 = CheckValue(0, x0, renderState.width);
  x1 = CheckValue(0, x1, renderState.width);
  y0 = CheckValue(0, y0, renderState.height);
  y1 = CheckValue(0, y1, renderState.height);


  //first pixel = buffer_start + x0 + y_pos*width
  for (int y = y0; y < y1; y++) {
    uint* pixel = (uint*)renderState.buff + x0 + y*renderState.width;
    for (int x = x0; x < x1; x++) {
      *pixel++ = color;
    }
  }
}

float renderScale = 0.01f;

void DrawRectangle(float x, float y, float halfSizeX, float halfSizeY, uint color) {

  x *= (renderState.height*renderScale);
  y *= (renderState.height*renderScale);
  halfSizeX *= (renderState.height*renderScale);
  halfSizeY *= (renderState.height*renderScale);

  x += renderState.width / 2.f;
  y += renderState.height / 2.f;

  int x0 = x - halfSizeX;
  int y0 = y - halfSizeY;
  int x1 = x + halfSizeX;
  int y1 = y + halfSizeY;

  DrawRectangleInPixels(x0, y0, x1, y1, color);
}