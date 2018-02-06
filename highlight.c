#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "highlight.h"
#include "attr.h"
#include "colour.h"
#include "mapping.h"

// clang-format off
#define OBJECT_APPLE  1 
#define OBJECT_BANANA 2
#define OBJECT_CHERRY 3

struct Mapping object_list[] =
{
  { "apple",  OBJECT_APPLE  },
  { "banana", OBJECT_BANANA },
  { "cherry", OBJECT_CHERRY },
};
// clang-format on

const char *get_object_name(int id)
{
  for (size_t i = 0; i < array_size(object_list); i++)
  {
    if (object_list[i].value == id)
      return object_list[i].name;
  }

  return NULL;
}

void print_highlight(struct Highlight *hi)
{
  if (!hi)
    return;

  const char *name = get_object_name(hi->id);
  if (!name)
    return;

  printf("highlight %s ", name);
  printf("fg=");
  print_colour(&hi->fg);
  printf(" bg=");
  print_colour(&hi->bg);
  printf(" attr=");
  print_attr(hi->attr);
  printf("\n");
}

bool parse_highlight(char *str, size_t len, struct Highlight *hi)
{
  if (!str)
    return false;

  str = strtok(str, " ");
  if (!str)
    return false;

  if (strcasecmp(str, "highlight") != 0)
    return false;

  str = strtok(NULL, " ");
  if (!str)
    return false;

  int object = 0;
  for (size_t i = 0; i < array_size(object_list); i++)
  {
    if (strcasecmp(str, object_list[i].name) == 0)
    {
      object = object_list[i].value;
      break;
    }
  }

  if (object == 0)
    return false;

  hi->id = object;

  while ((str = strtok(NULL, " ")) != NULL)
  {
    if (strncmp(str, "fg=", 3) == 0)
    {
      str += 3;
      if (!parse_colour(str, strlen(str), &hi->fg))
        return false;
    }
    else if (strncmp(str, "bg=", 3) == 0)
    {
      str += 3;
      if (!parse_colour(str, strlen(str), &hi->bg))
        return false;
    }
    else if (strncmp(str, "attr=", 5) == 0)
    {
      str += 5;
      if (!parse_attr_list(str, strlen(str), &hi->attr))
        return false;
    }
    else
    {
      return false;
    }
  }

  return true;
}
