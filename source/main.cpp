/*===========================================
        GRRLIB (GX Version)
        - Template Code -

        Minimum Code To Use GRRLIB
============================================*/

// GLM MUST BE INCLUDED BEFORE grrlib.h because GRRLIB pollutes
// global scope with junk macros that break GLM's templates :E
#include "glm/glm.hpp"

#include <grrlib.h>
#include <ogc/lwp_watchdog.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "resource_manager.hpp"
#include "creature_system.hpp"
#include "transform_system.hpp"

#define GRRLIB_BLACK   0x000000FF
#define GRRLIB_WHITE   0xFFFFFFFF

int main(int argc, char **argv) {
  // Initialise the Graphics & Video subsystem
  GRRLIB_Init();

  // Initialise the Wiimotes
  WPAD_Init();

  double deltaTime;
  settime((uint64_t)0); //So we don't have to start with a huge number.
  uint64_t deltaTimeStart = gettime();

  ResourceManager resource_manager;
  TransformSystem transform_system;
  CreatureSystem creature_system;

  GRRLIB_texImg *test_dog_tex = resource_manager.tex(TextureName::test_dog);

  int dog_x = 480;

  glm::vec2 crazy_dog_pos = glm::vec2(340, 120);



  // Loop forever
  while(1) {
    deltaTime = (double)(gettime() - deltaTimeStart) / (double)(TB_TIMER_CLOCK * 1000); // division is to convert from ticks to seconds
    deltaTimeStart = gettime();
    double time = (double)(deltaTimeStart) / (double)(TB_TIMER_CLOCK * 1000);

    WPAD_ScanPads();  // Scan the Wiimotes

    // If [HOME] was pressed on the first Wiimote, break out of the loop
    if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;

    dog_x -= 1;
    if (dog_x < 0){
      dog_x = 480;
    }

    crazy_dog_pos = glm::vec2(
      340.f + glm::sin(time * 6.f) * 40.f,
      120.f + glm::cos(time * 8.f) * 80.f
    );

    // ---------------------------------------------------------------------
    // Place your drawing code here
    // ---------------------------------------------------------------------
    GRRLIB_FillScreen(GRRLIB_BLACK);    // Clear the screen
    GRRLIB_DrawImg(dog_x, 50, test_dog_tex, 0, 1, 1, GRRLIB_WHITE);  // Draw doggo
    GRRLIB_DrawImg((int)crazy_dog_pos.x, (int)crazy_dog_pos.y, test_dog_tex, 0, 1, 1, GRRLIB_WHITE);

    GRRLIB_Render();  // Render the frame buffer to the TV
  }

  GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

  exit(0);  // Use exit() to exit a program, do not use 'return' from main()

}
