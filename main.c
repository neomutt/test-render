#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attr.h"
#include "colour.h"
#include "highlight.h"
#include "regex2.h"

struct Segment
{
  int i;
};

void seg_test(const char *str)
{
  if (!str)
    return;

  char buf[1024];
  FILE *fp = NULL;

  fp = fopen(str, "r");
  if (!fp)
    return;

  while (fgets(buf, sizeof(buf), fp))
  {
    printf(">>>%s", buf);
  }

  fclose(fp);
}

int main(int argc, char *argv[])
{
  for (; argc > 1; argc--, argv++)
  {
    seg_test(argv[1]);
  }

  return 0;
}
