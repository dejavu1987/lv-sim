#include "lvgl.h"
#include "app_hal.h"
#include "mainScreen.c"

int main(void)
{
  lv_init();

  hal_setup();

  hakunamatata();

  hal_loop();
}
