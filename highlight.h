#ifndef _HIGHLIGHT_H
#define _HIGHLIGHT_H

#include <stdbool.h>
#include <stdio.h>
#include "colour.h"

struct Highlight
{
  // union Colour fg;
  // union Colour bg;
  int id;
  struct RgbColour fg;
  struct RgbColour bg;
  unsigned short attr;
};

bool parse_highlight(char *str, size_t len, struct Highlight *hi);
void print_highlight(struct Highlight *hi);

#endif /* _HIGHLIGHT_H */
