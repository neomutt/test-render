#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attr.h"
#include "colour.h"
#include "highlight.h"
#include "regex2.h"

void attr_test(char *str)
{
  printf("%s\n", str);
  unsigned short attr = 0;
  if (attr_parse_list(str, strlen(str), &attr))
  {
    attr_print(attr);
    printf("\n");
  }
  else
  {
    printf("failed\n");
  }
}

void colour_test(char *str)
{
  printf("%s\n", str);

  struct RgbColour col = { 0 };

  if (colour_parse(str, strlen(str), &col))
  {
    colour_print(&col);
    printf("\n");
  }
  else
  {
    printf("failed\n");
  }
}

void highlight_test(char *str)
{
  struct Highlight *hi = calloc(1, sizeof(*hi));

  if (highlight_parse(str, strlen(str), hi))
  {
    highlight_print(hi);
  }
  else
  {
    printf("failed\n");
  }

  highlight_free(hi);
}

void regex_test(char *str)
{
  struct Regex *r = regex_new(str);

  regex_free(r);
}

int main(int argc, char *argv[])
{
  for (; argc > 1; argc--, argv++)
  {
    // attr_test(argv[1]);
    // colour_test(argv[1]);
    highlight_test(argv[1]);
    // regex_test(argv[1]);
  }

  return 0;
}
