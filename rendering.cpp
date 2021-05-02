//fill screen with one color
void ClearScreen(uint color){
uint* pixel = (uint*)renderState.buff; //first pixel
  for (int y = 0; y < renderState.height; y++) {
    for (int x = 0; x < renderState.width; x++) {
      *pixel++ = color;
    }
  }
}

void MyRectangle::DrawRectangleInPixels(int x0, int y0, int x1, int y1, int color) {

  //checking values
  x0 = CheckValue(0, x0, renderState.width);
  x1 = CheckValue(0, x1, renderState.width);
  y0 = CheckValue(0, y0, renderState.height);
  y1 = CheckValue(0, y1, renderState.height);


  //first pixel = buffer_start + x0 + y_pos*width
  for (int y = y0; y < y1; y++) {
    uint* pixel = (uint*)renderState.buff + x0 + y * renderState.width;
    for (int x = x0; x < x1; x++)
      *pixel++ = color;

  }
}

