#define isDown(x) (input.buttons[x].is_down)
#define isPressed(x) (input.buttons[x].is_down && input.buttons[x].changed)

//is button being pressed, was it pressed a moment ago
typedef struct {
  bool is_down;
  bool changed;
}ButtonState;

enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_LEFT,
  BUTTON_RIGHT,

  BUTTON_COUNT, //automatically gets the num of buttons' amount
};

typedef struct {
  ButtonState buttons[BUTTON_COUNT];
}Input;