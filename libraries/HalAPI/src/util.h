/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc


#ifndef UTILI_H_
#define UTILI_H_

#include <stdbool.h>
#include <mcu/types.h>
//#include "periph.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NO_PORT_NUMBER 0xAAEE5566

int phylib_util_open(const char * name, u8 port, int * fd, int total, bool * init);
int phylib_util_close(u8 port, int * fd);

#ifdef __cplusplus
}
#endif

#endif /* UTILI_H_ */
