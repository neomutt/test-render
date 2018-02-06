#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attr.h"
#include "colour.h"
#include "highlight.h"
#include "regex2.h"

void test_attr(char *str)
{
  printf("%s\n", str);
  unsigned short attr = 0;
  if (parse_attr_list(str, strlen(str), &attr))
  {
    print_attr(attr);
    printf("\n");
  }
  else
  {
    printf("failed\n");
  }
}

void test_colour(char *str)
{
  printf("%s\n", str);

  struct RgbColour col = { 0 };

  if (parse_colour(str, strlen(str), &col))
  {
    print_colour(&col);
    printf("\n");
  }
  else
  {
    printf("failed\n");
  }
}

void test_highlight(char *str)
{
  struct Highlight *hi = calloc(1, sizeof(*hi));

  if (parse_highlight(str, strlen(str), hi))
  {
    print_highlight(hi);
  }
  else
  {
    printf("failed\n");
  }

  free_highlight(hi);
}

void test_regex(char *str)
{
  struct Regex *r = regex_new(str);

  regex_free(r);
}

int main(int argc, char *argv[])
{
  for (; argc > 1; argc--, argv++)
  {
    // test_attr(argv[1]);
    // test_colour(argv[1]);
    test_highlight(argv[1]);
    // test_regex(argv[1]);
  }

  return 0;
}
