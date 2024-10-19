#include <buffalo/print.h>

extern "C" void __kernel_main__() {
  print_clear();
  print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
  print_str("Welcome to our 64-bit kernel!");
}
