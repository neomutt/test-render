#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "regex2.h"

void regex_free(struct Regex *r)
{
  if (!r)
    return;

  free((void *) r->pattern);
  if (r->rx)
    regfree(r->rx);
  free(r->rx);
  free(r);
}

struct Regex *regex_new(const char *pat)
{
  if (!pat)
    return NULL;

  regex_t *rx = calloc(1, sizeof(*rx));
  if (!rx)
    return NULL;

  int rc = regcomp(rx, pat, 0);
  if (rc != 0)
  {
    free(rx);
    return NULL;
  }

  struct Regex *r = calloc(1, sizeof(*r));
  if (!r)
    return NULL;

  r->pattern = strdup(pat);
  r->rx = rx;
  r->not = false;
  return r;
}
