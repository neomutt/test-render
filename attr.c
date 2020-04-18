#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "attr.h"
#include "mapping.h"

// clang-format off
static const struct Mapping attr_list[] = {
  { "none",          ATTR_NONE      },
  { "normal",        ATTR_NONE      },
  { "bold",          ATTR_BOLD      },
  { "blink",         ATTR_BLINK     },
  { "standout",      ATTR_BOLD      },
  { "conceal",       ATTR_CONCEAL   },
  { "faint",         ATTR_FAINT     },
  { "italic",        ATTR_ITALIC    },
  { "reverse",       ATTR_REVERSE   },
  { "strike",        ATTR_STRIKE    },
  { "strikethrough", ATTR_STRIKE    },
  { "underline",     ATTR_UNDERLINE },
  { "uri",           ATTR_URI       },
};
// clang-format on

void print_ansi(const char *str, int attr)
{
  if (!str)
    return;

  int code = 0;
  if (attr == ATTR_BLINK)
    code = 5;
  else if (attr == ATTR_BOLD)
    code = 1;
  else if (attr == ATTR_CONCEAL)
    code = 8;
  else if (attr == ATTR_FAINT)
    code = 2;
  else if (attr == ATTR_ITALIC)
    code = 3;
  else if (attr == ATTR_REVERSE)
    code = 7;
  else if (attr == ATTR_STRIKE)
    code = 9;
  else if (attr == ATTR_UNDERLINE)
    code = 4;
  else if (attr == ATTR_URI)
    code = 10;

  if ((code == 0) || (isatty(1) == 0))
  {
    printf("%s", str);
  }
  else if (code == 10)
  {
    printf("\033]8;;%s\007%s\033]8;;\007", "https://www.example.com", str);
  }
  else
  {
    printf("\033[%dm%s\033[0m", code, str);
  }
}

void attr_print(unsigned int attr)
{
  attr &= ATTR_MASK;
  for (size_t i = 0; i < array_size(attr_list); i++)
  {
    if (attr & attr_list[i].value)
    {
      print_ansi(attr_list[i].name, attr_list[i].value);
      attr &= ~attr_list[i].value;
      if (attr != 0)
        printf(",");
    }
  }
}

bool attr_parse(const char *str, size_t len, unsigned short *attr)
{
  if (!str || (len == 0) || !attr)
    return false;

  for (size_t i = 0; i < array_size(attr_list); i++)
  {
    if (strncmp(attr_list[i].name, str, len) == 0)
    {
      *attr |= attr_list[i].value;
      return true;
    }
  }

  return false;
}

bool attr_parse_list(char *str, size_t len, unsigned short *attr)
{
  if (!str || (len == 0) || !attr)
    return false;

  str = strtok(str, ",");
  if (!str)
    return false;

  if (!attr_parse(str, strlen(str), attr))
    return false;

  while ((str = strtok(NULL, ",")) != NULL)
  {
    if (!attr_parse(str, strlen(str), attr))
      return false;
  }

  return true;
}

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
