#ifndef API_H
#define API_H

#include <mcu/types.h>

typedef struct {
  const char *name;
  u32 version;
  const char *git_hash;
} api_t;

#endif // API_H
