#ifndef _COLOUR_H
#define _COLOUR_H

#include <stdbool.h>

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

union Colour
{
  struct AnsiColour ansi;
  struct PaletteColour pal;
  struct RgbColour rgb;
};

void print_colour(struct RgbColour *col);
bool parse_colour(const char *str, size_t len, struct RgbColour *col);

#endif /* _COLOUR_H */

