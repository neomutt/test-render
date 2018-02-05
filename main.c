#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "attr.h"
#include "mapping.h"
#include "colour.h"

struct Highlight
{
  union Colour fg;
  union Colour bg;
  unsigned short attr;
};

void test_attr(char *str)
{
  printf("%s\n", str);

  char *marker = NULL;
  unsigned short attr = 0;

  while ((str = strtok(str, ",")) != NULL)
  {
    parse_attr(marker, str - marker, &attr);
    marker = str;
    str = NULL;
  }

  parse_attr(marker, strlen(marker), &attr);

  print_attr(attr);
}

void test_colour(char *str)
{
  printf("%s\n", str);

  struct RgbColour col = { 0 };

  if (parse_colour(str, strlen(str), &col))
    print_colour(&col);
  else
    printf("failed\n");
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    return 1;

  for (; argc > 1; argc--, argv++)
  {
    // test_attr(argv[1]);
    test_colour(argv[1]);
  }

  return 0;
}
