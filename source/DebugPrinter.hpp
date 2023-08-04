#pragma once
/* Debug printer

   This singleton class lets to print text on the screen.
   It handles automatically where to draw the text

*/

struct GRRLIB_texImg;

class DebugPrinter {
public:
  GRRLIB_texImg *debug_font_tex;
  int font_width = 0;
  int font_height = 0;
  int line_number = 0;
  float message_scale = 0.5f;
  void Init();
  void StartFrame();
  void Print(const char* text);
  void DeInit();
};


