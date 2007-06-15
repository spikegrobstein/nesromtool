/*
 *  types.h
 *  nesromtool
 *
 *  Created by spike on Fri May 21 2004.
 *  Copyright (c) 2004 Sadistech. All rights reserved.
 *
 */

#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned long u32;
typedef unsigned short u16;

typedef unsigned char uchar;

//check if bool is defined or not...
#ifndef bool
#define bool int

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#endif

#endif /* _TYPES_H_ */

