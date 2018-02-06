#include <ctype.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include "colour.h"
#include "mapping.h"

// clang-format off
#define ANSI_BLACK   0
#define ANSI_RED     1
#define ANSI_GREEN   2
#define ANSI_YELLOW  3
#define ANSI_BLUE    4
#define ANSI_MAGENTA 5
#define ANSI_CYAN    6
#define ANSI_WHITE   7

struct Mapping colour_list[] =
{
  { "black",     ANSI_BLACK   },
  { "red",       ANSI_RED     },
  { "green",     ANSI_GREEN   },
  { "yellow",    ANSI_YELLOW  },
  { "brown",     ANSI_YELLOW  },
  { "blue",      ANSI_BLUE    },
  { "magenta",   ANSI_MAGENTA },
  { "cyan",      ANSI_CYAN    },
  { "white",     ANSI_WHITE   },
  { "lightgray", ANSI_WHITE   },
  { "grey",      ANSI_WHITE   },
};
// clang-format on

void colour_print(struct RgbColour *col)
{
  if (!col)
    return;

  bool tty = (isatty(1) == 1);

  if (tty)
  {
    int mean = (col->red + col->green + col->blue) / 3;
    if (mean < 128)
      printf("\033[38;2;255;255;255m");
    else
      printf("\033[38;2;0;0;0m");
    printf("\033[48;2;%d;%d;%dm", col->red, col->green, col->blue);
  }

  printf("#%02x%02x%02x", col->red, col->green, col->blue);

  if (tty)
    printf("\033[0m");
}

bool parse_hex3(const char *str, size_t len, struct RgbColour *col)
{
  if (!str || (len != 4) || !col)
    return false;

  unsigned int red = 0;
  unsigned int green = 0;
  unsigned int blue = 0;

  int rc = sscanf(str, "#%1x%1x%1x", &red, &green, &blue);
  if (rc != 3)
    return false;

  col->red = (red << 4) + red;
  col->green = (green << 4) + green;
  col->blue = (blue << 4) + blue;

  return true;
}

bool parse_hex6(const char *str, size_t len, struct RgbColour *col)
{
  if (!str || (len != 7) || !col)
    return false;

  unsigned int red = 0;
  unsigned int green = 0;
  unsigned int blue = 0;

  int rc = sscanf(str, "#%02x%02x%02x", &red, &green, &blue);
  if (rc != 3)
    return false;

  col->red = red;
  col->green = green;
  col->blue = blue;

  return true;
}

bool palette_base_to_rgb(int n, struct RgbColour *col)
{
  if ((n < 0) || (n > 15) || !col)
    return false;

  int r = 0;
  int g = 0;
  int b = 0;

  if (n & 1)
    r = 0x80;
  if (n & 2)
    g = 0x80;
  if (n & 4)
    b = 0x80;

  if (n & 8)
  {
    if (n & 1)
      r += 0x7f;
    if (n & 2)
      g += 0x7f;
    if (n & 4)
      b += 0x7f;

    if (n == 8)
    {
      r = 0x80;
      g = 0x80;
      b = 0x80;
    }
  }

  if (n == 7)
  {
    r += 0x40;
    g += 0x40;
    b += 0x40;
  }

  col->red = r;
  col->green = g;
  col->blue = b;

  return true;
}

bool palette_cube_to_rgb(int n, struct RgbColour *col)
{
  if ((n < 16) || (n > 231) || !col)
    return false;

  int ids[] = { 0x00, 0x5F, 0x87, 0xAF, 0xD7, 0xFF };

  n -= 16;
  int r = ids[n / 36];
  int g = ids[(n / 6) % 6];
  int b = ids[n % 6];

  col->red = r;
  col->green = g;
  col->blue = b;

  return true;
}

bool palette_greys_to_rgb(int n, struct RgbColour *col)
{
  if ((n < 232) || (n > 255) || !col)
    return false;

  n -= 232;
  col->red = (n * 10) + 8;
  col->green = col->red;
  col->blue = col->red;

  return true;
}

bool palette_to_rgb(int n, struct RgbColour *col)
{
  if (palette_base_to_rgb(n, col))
    return true;
  if (palette_cube_to_rgb(n, col))
    return true;

  return palette_greys_to_rgb(n, col);
}

bool parse_colorn(const char *str, size_t len, struct RgbColour *col)
{
  if (!str || !col)
    return false;

  if ((len < 6) || (len > 8))
    return false;

  if (strncasecmp(str, "color", 5) != 0)
    return false;

  if (isdigit(str[5]) == 0)
    return false;
  if ((len > 6) && isdigit(str[6]) == 0)
    return false;
  if ((len > 7) && isdigit(str[7]) == 0)
    return false;

  int num = 0;
  int rc = sscanf(str, "color%d", &num);
  if (rc != 1)
    return false;

  return palette_to_rgb(num, col);
}

bool parse_colour_name(const char *str, size_t len, struct RgbColour *col)
{
  if (!str || (len == 0) || !col)
    return false;

  bool bright = false;

  if (strncasecmp(str, "bright", 6) == 0)
  {
    bright = true;
    str += 6;
  }

  for (size_t i = 0; i < array_size(colour_list); i++)
  {
    if (strcasecmp(str, colour_list[i].name) == 0)
    {
      int n = colour_list[i].value;
      if (bright)
        n += 8;

      return palette_base_to_rgb(n, col);
    }
  }

  return false;
}

bool colour_parse(const char *str, size_t len, struct RgbColour *col)
{
  if (!str || (len == 0) || !col)
    return false;

  if (parse_hex6(str, len, col))
    return true;

  if (parse_hex3(str, len, col))
    return true;

  if (parse_colorn(str, len, col))
    return true;

  if (parse_colour_name(str, len, col))
    return true;

  return false;
}
