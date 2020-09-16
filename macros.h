/*
 * macros.h
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#ifndef MACROS_H_
#define MACROS_H_

#include <DOS.H>
#include "SCHEDULE.H"


#define lock {asm{pushf; cli;}}
#define unlock {asm popf;}

static unsigned infinity = 100000;
static unsigned long maxStackSize = 65536;
typedef unsigned char IVTNo, old;

typedef void interrupt (*pInterrupt)(...);


#endif /* MACROS_H_ */
