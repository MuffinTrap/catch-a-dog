#include "DebugPrinter.hpp"

#include <grrlib.h>
#include "grrlib_colors.hpp"

// Fonts
#include "debug_font_20_14_png.h"

// Singleton functions

DebugPrinter* DebugPrinter::singleton;

void DebugPrinter::SInit() {
  font_height = 20;
  font_width = 14;
  debug_font_tex = GRRLIB_LoadTexture(debug_font_20_14_png);
  GRRLIB_InitTileSet(debug_font_tex, font_width, font_height, 32);
  line_number = 1;
}

void DebugPrinter::SDeInit() {
  GRRLIB_FreeTexture(debug_font_tex);
}

void DebugPrinter::SPrint(const char* text)
{
  GRRLIB_Printf(20, line_number * font_height * message_scale, debug_font_tex, GRRLIB_WHITE, message_scale, text);
  line_number += 1;
}


// Public functions

void DebugPrinter::Init() {
  if (singleton == NULL) {
    singleton = new DebugPrinter();
    singleton->SInit();
  }
}

void DebugPrinter::StartFrame() {
  singleton->line_number = 1;
}

void DebugPrinter::Print(const char* text) {
  singleton->SPrint(text);
}

void DebugPrinter::DeInit() {
  if (singleton != NULL) {
    singleton->DeInit();
    delete(singleton);
  }
}

