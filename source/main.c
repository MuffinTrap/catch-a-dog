/*===========================================
        GRRLIB (GX Version)
        - Template Code -

        Minimum Code To Use GRRLIB
============================================*/
#include <grrlib.h>

#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "test_dog_png.h"

#define GRRLIB_BLACK   0x000000FF
#define GRRLIB_WHITE   0xFFFFFFFF

int main(int argc, char **argv) {
  // Initialise the Graphics & Video subsystem
  GRRLIB_Init();

  // Initialise the Wiimotes
  WPAD_Init();

  GRRLIB_texImg *test_dog_tex = GRRLIB_LoadTexture(test_dog_png);

  int dog_x = 480;

  // Loop forever
  while(1) {

    WPAD_ScanPads();  // Scan the Wiimotes

    // If [HOME] was pressed on the first Wiimote, break out of the loop
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;

    dog_x -= 1;
    if (dog_x < 0){
      dog_x = 480;
    }

    // ---------------------------------------------------------------------
    // Place your drawing code here
    // ---------------------------------------------------------------------
    GRRLIB_FillScreen(GRRLIB_BLACK);    // Clear the screen
    GRRLIB_DrawImg(dog_x, 50, test_dog_tex, 0, 1, 1, GRRLIB_WHITE);  // Draw doggo

    GRRLIB_Render();  // Render the frame buffer to the TV
  }

  GRRLIB_FreeTexture(test_dog_tex);
  GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

  exit(0);  // Use exit() to exit a program, do not use 'return' from main()

}
