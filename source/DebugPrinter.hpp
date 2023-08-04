#pragma once
/* Debug printer

   This singleton class lets to print text on the screen.
   It handles automatically where to draw the text

*/

struct GRRLIB_texImg;

class DebugPrinter {

private:
  static DebugPrinter* singleton;
  GRRLIB_texImg *debug_font_tex;
  void SInit();
  void SDeInit();
  void SPrint(const char* text);
  int font_width = 0;
  int font_height = 0;
  int line_number = 0;
  float message_scale = 0.5f;


public:

  static void Init();
  static void Print(const char* text);
  static void StartFrame();
  static void DeInit();
};


