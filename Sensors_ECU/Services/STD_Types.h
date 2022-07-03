/* 
 * File:   STD_Types.h
 * Author: Ayman Elgammal
 *
 * Created on January 29, 2022, 2:39 PM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H


typedef unsigned char      u8;
typedef unsigned short int u16;
typedef unsigned long  int u32;
typedef signed   char      s8;
typedef signed   short int s16;
typedef signed   long  int s32;
typedef float              f32;
typedef double             f64;
typedef long double        f128;

typedef unsigned char *      	pu8;
typedef unsigned short int *	 pu16;
typedef unsigned long  int *	 pu32;
typedef signed   char *     	 ps8;
typedef signed   short int * 	ps16;
typedef signed   long  int * 	ps32;
typedef float*             	 pf32;
typedef double*             	pf64;
typedef long double*        	pf128;

/* function to pointer data type */
typedef void (*ptr_func)(void);





#endif	/* STD_TYPES_H */

