#ifndef _UMOD_H_
#define _UMOD_H_

#include "umul.h"
#include "udiv.h"

unsigned _umod(unsigned a, unsigned b) { return a - (a / b) * b; }

#endif /* _UMOD_H_ */
