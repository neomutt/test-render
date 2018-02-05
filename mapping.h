#ifndef _MAPPING_H
#define _MAPPING_H

#define array_size(x) (sizeof(x) / sizeof((x)[0]))

struct Mapping
{
  const char *name;
  int value;
};

#endif /* _MAPPING_H */
