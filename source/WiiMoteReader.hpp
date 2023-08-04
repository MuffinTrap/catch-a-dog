#pragma once

#include "glm/glm.hpp"

class DebugPrinter;

class WiiMoteReader {

public:
  void Init(DebugPrinter *printer);
  void StartFrame();
  void PrintWiiMoteStatus();
  void DrawDebugCursor();

  bool ButtonPress(int buttonEnum);
  bool ButtonRelease(int buttonEnum);
  bool ButtonHeld(int buttonEnum);

  glm::vec2 GetCursorPosition();

  char ir_message[60];
  char position_message[60];
  char correction_message[60];

  float ir_x;
  float ir_y;

  int cursor_x;
  int cursor_y;

  float correction_x;
  float correction_y;

  DebugPrinter *printerPtr;
};

