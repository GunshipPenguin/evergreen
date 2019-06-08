#include "vga_terminal.h"

#if defined(__linux__)
#error "You are not using a cross-compiler"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) {
  vga_terminal_initialize();
  vga_terminal_setcolor(
      vga_terminal_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
  vga_terminal_writestring("=========\n");
  vga_terminal_writestring("Evergreen\n");
  vga_terminal_writestring("=========\n");
  vga_terminal_setcolor(
      vga_terminal_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));

  vga_terminal_writestring("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n123456789\n");
}
