#ifndef _ATTR_H
#define _ATTR_H

#include <stdbool.h>
#include <stdio.h>

#define ATTR_NONE      0
#define ATTR_BOLD      (1 << 0)
#define ATTR_CONCEAL   (1 << 1)
#define ATTR_FAINT     (1 << 2)
#define ATTR_ITALIC    (1 << 3)
#define ATTR_REVERSE   (1 << 4)
#define ATTR_STRIKE    (1 << 5)
#define ATTR_UNDERLINE (1 << 6)
#define ATTR_URI       (1 << 7)

#define ATTR_MASK     ((1 << 8) - 1)

void attr_print(unsigned int attr);
bool attr_parse(const char *str, size_t len, unsigned short *attr);
bool attr_parse_list(char *str, size_t len, unsigned short *attr);

#endif /* _ATTR_H */
