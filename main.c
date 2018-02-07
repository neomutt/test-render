#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attr.h"
#include "colour.h"
#include "highlight.h"
#include "regex2.h"

int main(int argc, char *argv[])
{
  for (; argc > 1; argc--, argv++)
  {
    attr_test(argv[1]);
    colour_test(argv[1]);
    regex_test(argv[1]);
    highlight_test(argv[1]);
  }

  return 0;
}
