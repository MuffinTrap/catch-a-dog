#include "DebugPrinter.hpp"

#include <grrlib.h>
#undef R
#include "grrlib_colors.hpp"

// Fonts
#include "debug_font_20_14_png.h"


void DebugPrinter::Init() {
  font_height = 20;
  font_width = 14;
  debug_font_tex = GRRLIB_LoadTexture(debug_font_20_14_png);
  GRRLIB_InitTileSet(debug_font_tex, font_width, font_height, 32);
  line_number = 1;
}

void DebugPrinter::StartFrame() {
  line_number = 1;
}

void DebugPrinter::Print(const char* text)
{
  GRRLIB_Printf(20, line_number * font_height * message_scale, debug_font_tex, GRRLIB_WHITE, message_scale, text);
  line_number += 1;
}

void DebugPrinter::DeInit() {
  GRRLIB_FreeTexture(debug_font_tex);
}
