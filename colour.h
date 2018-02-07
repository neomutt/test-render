#ifndef _COLOUR_H
#define _COLOUR_H

#include <stdbool.h>
#include <stdio.h>

struct AnsiColour
{
  unsigned char index;
  bool bright;
};

struct PaletteColour
{
  unsigned char index;
};

struct RgbColour
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

union Colour {
  struct AnsiColour ansi;
  struct PaletteColour pal;
  struct RgbColour rgb;
};

void colour_print(struct RgbColour *col);
bool colour_parse(const char *str, size_t len, struct RgbColour *col);
void colour_test(char *str);

#endif /* _COLOUR_H */
