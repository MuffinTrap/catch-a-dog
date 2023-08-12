/* Reading Wiimote cursor */
#include "WiiMoteReader.hpp"

#include <grrlib.h>
#undef R
#include <stdlib.h>
#include <cstdio>
#include <wiiuse/wpad.h>

#include "grrlib_colors.hpp"
#include "DebugPrinter.hpp"

static const int screen_width = 640;
static const int screen_height = 480;

bool WiiMoteReader::ButtonPress(int buttonEnum) {
  return (WPAD_ButtonsDown(0) & buttonEnum);
}

bool WiiMoteReader::ButtonRelease(int buttonEnum) {
  return (WPAD_ButtonsUp(0) & buttonEnum);
}

bool WiiMoteReader::ButtonHeld(int buttonEnum) {
  return (WPAD_ButtonsHeld(0) & buttonEnum);
}

void WiiMoteReader::Init(DebugPrinter *printer) {
  WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

  cursor_x = screen_width / 2;
  cursor_y = screen_height / 2;

  // Tested and found these values to be good
  correction_x = -125.0f;
  correction_y = -10.0f;

  printerPtr = printer;
}

glm::vec2 WiiMoteReader::GetCursorPosition() {
  return glm::vec2(cursor_x, cursor_y);
}

void WiiMoteReader::StartFrame() {
  WPAD_ScanPads();  // Scan the Wiimotes
  ir_t ir;
  WPAD_IR(WPAD_CHAN_0, &ir);

  /* Found these values by testing:

     IR X goes from 0 to 1200, so 0.5 gives correct result
     IR Y does not cover the whole screen, so multiply with 1.3 before halving


     IR also has:
     ax ay for raw position
     sx sy are for smoothed position
     x  y  are bounded coordinates

     int offset[2] IR XY correction offset
   */
  const double sensitivity_x = 0.5;
  const double sensitivity_y = 1.3 * 0.5;
  ir_x = ir.sx;
  ir_y = ir.sy;

  cursor_x = (ir.sx - correction_x) * sensitivity_x;
  cursor_y = (ir.sy - correction_y) * sensitivity_y;

  int mult = 1;

  if (ButtonHeld(WPAD_BUTTON_A)) {
    mult = 10;
  }


  // Adjust with - and +
  if (ButtonPress(WPAD_BUTTON_PLUS)) {
    if (ButtonHeld(WPAD_BUTTON_B)) {
      correction_y += 1 * mult;
    }
    else {
      correction_x += 1 * mult;
    }
  }
  if (ButtonPress(WPAD_BUTTON_MINUS)) {
    if (ButtonHeld(WPAD_BUTTON_B)) {
      correction_y -= 1 * mult;
    }
    else {
      correction_x -= 1 * mult;
    }
  }
}

void WiiMoteReader::PrintWiiMoteStatus() {
  sprintf(ir_message, "Wiimote IR: X: %2.0f Y: %2.0f", ir_x, ir_y);
  printerPtr->Print(ir_message);
  sprintf(position_message, "Wiimote: X: %d Y: %d", cursor_x, cursor_y);
  printerPtr->Print(position_message);
  sprintf(correction_message, "Correction X: %d Y: %d", (int)correction_x, (int)correction_y);
  printerPtr->Print(correction_message);
}

void WiiMoteReader::DrawDebugCursor() {


  GRRLIB_Line(cursor_x, 0, cursor_x, screen_height, GRRLIB_WHITE);
  GRRLIB_Line(0, cursor_y, screen_width, cursor_y, GRRLIB_WHITE);

    // Read WiiMote position

    // Draw a circle on the cursor

    // If cursor is outside the screen: draw indicator?
}


