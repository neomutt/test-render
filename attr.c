#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "attr.h"
#include "mapping.h"

// clang-format off
static const struct Mapping attr_list[] = {
  { "none",          ATTR_NONE      },
  { "normal",        ATTR_NONE      },
  { "bold",          ATTR_BOLD      },
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

void print_attr(unsigned int attr)
{
  attr &= ATTR_MASK;
  for (size_t i = 0; i < array_size(attr_list); i++)
  {
    if (attr & attr_list[i].value)
    {
      printf(attr_list[i].name);
      attr &= ~attr_list[i].value;
      if (attr != 0)
        printf(",");
    }
  }
  printf("\n");
}

bool parse_attr(const char *str, size_t len, unsigned short *attr)
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
