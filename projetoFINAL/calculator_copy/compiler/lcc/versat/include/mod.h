#ifndef _MOD_H_
#define _MOD_H_

#include "mul.h"
#include "div.h"

int _mod(int a, int b) { return a - (a / b) * b; }

#endif /* _MOD_H_ */
