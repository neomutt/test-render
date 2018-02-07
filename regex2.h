#ifndef _REGEX2_H
#define _REGEX2_H

#include <regex.h>
#include <stdbool.h>

struct Regex
{
  const char *pattern;
  regex_t *rx;
  bool not;
};

void regex_free(struct Regex *r);
struct Regex *regex_new(const char *pat);
void regex_test(char *str);

#endif /* _REGEX2_H */
