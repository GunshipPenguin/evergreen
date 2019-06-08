#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga_terminal.h"
#include "libk/string.h"

static const size_t VGA_TERMINAL_WIDTH = 80;
static const size_t VGA_TERMINAL_HEIGHT = 25;
static uint16_t *VGA_TERMINAL_BUF_START = (uint16_t *) 0xB8000;

size_t vga_terminal_row;
size_t vga_terminal_column;
uint8_t vga_terminal_color;
uint16_t* vga_terminal_buffer;

static inline uint16_t vga_terminal_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

static inline uint16_t vga_terminal_address(size_t row, size_t col) {
  return row * VGA_TERMINAL_WIDTH + col;
}

static void vga_terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_TERMINAL_WIDTH + x;
  vga_terminal_buffer[index] = vga_terminal_entry(c, color);
}

static void vga_terminal_scroll() {
  for (size_t row=0;row<VGA_TERMINAL_HEIGHT;row++) {
    for (size_t col=0;col<VGA_TERMINAL_WIDTH;col++) {
      vga_terminal_buffer[vga_terminal_address(row, col)] =
          vga_terminal_buffer[vga_terminal_address(row+1, col)];
    }
  }
}

static void vga_terminal_newline() {
  if (vga_terminal_row == VGA_TERMINAL_HEIGHT) {
    vga_terminal_scroll();
  } else {
    vga_terminal_row++;
    vga_terminal_column = 0;
  }
}

static void vga_terminal_write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    vga_terminal_putchar(data[i]);
  }
}

uint8_t vga_terminal_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

void vga_terminal_putchar(char c) {
  if (c == '\n') {
    vga_terminal_newline();
    return;
  }

  vga_terminal_putentryat(c, vga_terminal_color, vga_terminal_column,
      vga_terminal_row);
  if (++vga_terminal_column == VGA_TERMINAL_WIDTH) {
    vga_terminal_column = 0;
    if (++vga_terminal_row == VGA_TERMINAL_HEIGHT) {
      vga_terminal_row = 0;
    }
  }
}

void vga_terminal_setcolor(uint8_t color) {
  vga_terminal_color = color;
}

void vga_terminal_writestring(const char* data) {
  vga_terminal_write(data, strlen(data));
}

void vga_terminal_initialize(void) {
  vga_terminal_row = 0;
  vga_terminal_column = 0;
  vga_terminal_color = vga_terminal_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  vga_terminal_buffer = VGA_TERMINAL_BUF_START;

  for (size_t y = 0; y < VGA_TERMINAL_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_TERMINAL_WIDTH; x++) {
      const size_t index = y * VGA_TERMINAL_WIDTH + x;
      vga_terminal_buffer[index] = vga_terminal_entry(' ', vga_terminal_color);
    }
  }
}

