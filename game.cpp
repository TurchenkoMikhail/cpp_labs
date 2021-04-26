#define isDown(x) (input->buttons[x].is_down)
#define isPressed(x) (input->buttons[x].is_down && input->buttons[x].changed)

float pos = 0.f;

void Simulate(Input* input, float dt) {

  ClearScreen(0x8B00FF);
  DrawRectangle(0, 0, 85, 45, 0xCC99FE);

  float speed = 10.f;

  if (isDown(BUTTON_RIGHT)) {
    pos += speed * dt;
    input->buttons[BUTTON_RIGHT].is_down = false;
  }
  if (isDown(BUTTON_LEFT)) {
    pos -= speed * dt;
    input->buttons[BUTTON_LEFT].is_down = false;
  }

  DrawRectangle(0, 0, 1, 1, 0xA52A2A); //ball
  DrawRectangle(pos, -40, 12, 2.5, 0xA52A2A); //carriage
}