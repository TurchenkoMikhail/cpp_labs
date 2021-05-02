#include "windows.h"

typedef unsigned int uint;

typedef struct {
  int height, width;
  void* buff;
  BITMAPINFO buffBitMapInfo;
}Render_t;

bool RUN = true; //global
Render_t renderState; //global rendering
#include "rendering.cpp" //must be included after renderState
#include "actions.cpp"
#include "game.cpp"

//messages to window
LRESULT CALLBACK WindowCallBack(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {

  LRESULT result = (LRESULT)0;

  if (uMsg == WM_CLOSE || uMsg == WM_DESTROY)
    RUN = false; //stop execution
  else if (uMsg == WM_SIZE) { //changind size of screen
    RECT rect;
    GetClientRect(hwnd, &rect);

    //calculating size
    renderState.width = rect.right - rect.left; 
    renderState.height = rect.bottom - rect.top;

    uint buffSize = renderState.width * renderState.height * sizeof(uint);

    //memory
    if (renderState.buff) {
      VirtualFree(renderState.buff, 0, MEM_RELEASE);
      renderState.buff = NULL;
    }
    //rendering status
    renderState.buff = VirtualAlloc(0, buffSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    renderState.buffBitMapInfo.bmiHeader.biSize = sizeof(renderState.buffBitMapInfo.bmiHeader);
    renderState.buffBitMapInfo.bmiHeader.biWidth = renderState.width;
    renderState.buffBitMapInfo.bmiHeader.biHeight = renderState.height;
    renderState.buffBitMapInfo.bmiHeader.biPlanes = 1;
    renderState.buffBitMapInfo.bmiHeader.biBitCount = 32; //32 bits
    renderState.buffBitMapInfo.bmiHeader.biCompression = BI_RGB;

  }
  else {
    result = DefWindowProc(hwnd, uMsg, wParam, lParam);
  }

  return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

  //class Window
  WNDCLASS WindowClass = {};
  WindowClass.style = CS_HREDRAW | CS_VREDRAW;
  WindowClass.lpszClassName = "Window Class"; //name to identify class
  WindowClass.lpfnWndProc = WindowCallBack; //pointer to messages

  //register class
  RegisterClass(&WindowClass);

  //create window
  HWND window = CreateWindowA(WindowClass.lpszClassName, "Arkanoid", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
  HDC hdc = GetDC(window); //get device context

  while (RUN) {
    //input
    MSG message;

    Input input;

    float dt = 0.166667f, freq;
    LARGE_INTEGER frame_begin_time, perfFreq;
    QueryPerformanceCounter(&frame_begin_time);
    QueryPerformanceFrequency(&perfFreq);
    freq = (float)perfFreq.QuadPart;

    for (int i = 0; i < BUTTON_COUNT; i++) {
      input.buttons[i].changed = false;
    }

    //getting messages while playing
    while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

      switch (message.message) {
        case WM_KEYUP:
        case WM_KEYDOWN: {
          uint vkCode = (uint)message.wParam; //virtual key code
          bool is_down = ((message.lParam & (1<<31))==0);

#define ProcessButton(b,code)\
case code: {\
          input.buttons[b].changed = (is_down != input.buttons[b].is_down) ;\
          input.buttons[b].is_down = is_down;\
          }break;

          switch (vkCode) {
            ProcessButton(BUTTON_LEFT, VK_LEFT);
            ProcessButton(BUTTON_RIGHT, VK_RIGHT);
          }

        }break;
        default: {
          TranslateMessage(&message);
          DispatchMessage(&message);
        }
      }

    }

    //simulate (pixels)
    Simulate(&input, dt);

    //render
    StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.buff,&renderState.buffBitMapInfo, DIB_RGB_COLORS,SRCCOPY);
 
    LARGE_INTEGER frame_end_time;
    QueryPerformanceCounter(&frame_end_time);
    dt = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart)/freq;
    frame_begin_time = frame_end_time; //for next loop
  }
}