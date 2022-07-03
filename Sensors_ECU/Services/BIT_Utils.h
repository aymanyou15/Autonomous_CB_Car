/* 
 * File:   STD_Types.h
 * Author: Ayman Elgammal
 *
 * Created on January 3, 2022, 2:39 PM
*/
 
#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define REG_BITS    8


#define SET_BIT(Reg, Bit)	    (Reg |= (1<<Bit))
#define ASSIGN_BIT(Reg, Bit, Value)      (Value == 1? (Reg |= 1<<Bit):(Reg &= ~(1<<Bit)))
#define CLR_BIT(Reg, Bit)	    (Reg &= ~(1<<Bit))
#define GET_BIT(Reg, Bit)	    ((Reg>>Bit) & 1)
#define RSHFT_REG(Reg, No)	    (Reg = Reg>>No)
#define LSHFT_REG(Reg, No)	    (Reg = Reg << No)
#define CRSHFT_REG(Reg, No)     (Reg = (Reg >> No) | (Reg << (REG_BITS - No)))
#define CLSHFT_REG(Reg, No)     (Reg = (Reg << No) | (Reg >> (REG_BITS - No)))
#define ASSIGN_REG(Reg, Value)  (Reg = Value)
#define SET_REG(Reg)            (Reg = ~(Reg & 0))
#define CLR_REG(Reg)            (Reg = 0)
#define TGL_BIT(Reg, Bit)       (Reg ^= (1 << Bit))
#define TGL_REG(Reg)            (Reg = ~Reg)
#if REG_BITS == 32
    #define SET_H_NIP(Reg)          (Reg |= 0b11111111111111110000000000000000)
#elif REG_BITS == 16
    #define SET_H_NIP(Reg)          (Reg |= 0b1111111100000000)
#else /* size = 8 by default */
    #define SET_H_NIP(Reg)          (Reg |= 0b11110000)
#endif
#if REG_BITS == 32
    #define SET_L_NIP(Reg)          (Reg |= 0b00000000000000001111111111111111)
#elif REG_BITS == 16
    #define SET_L_NIP(Reg)          (Reg |= 0b0000000011111111)
#else
    #define SET_L_NIP(Reg)          (Reg |= 0b00001111)
#endif
#if REG_BITS == 32
    #define CLR_H_NIP(Reg)          (Reg &= 0b00000000000000001111111111111111)
#elif REG_BITS == 16
    #define CLR_H_NIP(Reg)          (Reg &= 0b0000000011111111)
#else
    #define CLR_H_NIP(Reg)          (Reg &= 0b00001111)
#endif
#if REG_BITS == 32
    #define CLR_L_NIP(Reg)          (Reg &= 0b11111111111111110000000000000000)
#elif REG_BITS == 16
    #define CLR_L_NIP(Reg)          (Reg &= 0b1111111100000000)
#else
    #define CLR_L_NIP(Reg)          (Reg &= 0b11110000)
#endif
#if REG_BITS == 32
    #define GET_H_NIP(Reg)          ((Reg & 0b11111111111111110000000000000000)>>16)
#elif REG_BITS == 16
    #define GET_H_NIP(Reg)          ((Reg & 0b1111111100000000)>>8)
#else
    #define GET_H_NIP(Reg)          ((Reg & 0b11110000)>>4)
#endif
#if REG_BITS == 32
    #define GET_L_NIP(Reg)          (Reg & 0b00000000000000001111111111111111)
#elif REG_BITS == 16
    #define GET_L_NIP(Reg)          (Reg & 0b0000000011111111)
#else
    #define GET_L_NIP(Reg)          (Reg & 0b00001111)
#endif
#if REG_BITS == 32
    #define ASSIGN_H_NIP(Reg, Value)    (Reg = (Reg & 0b00000000000000001111111111111111) | (Value << 16))
#elif REG_BITS == 16
    #define ASSIGN_H_NIP(Reg, Value)    (Reg = (Reg & 0b0000000011111111) | (Value << 8))
#else
    #define ASSIGN_H_NIP(Reg, Value)    (Reg = (Reg & 0b00001111) | (Value << 4))
#endif
#if REG_BITS == 32
    #define ASSIGN_L_NIP(Reg, Value)    (Reg = (Reg & 0b11111111111111110000000000000000) | Value)
#elif REG_BITS == 16
    #define ASSIGN_L_NIP(Reg, Value)    (Reg = (Reg & 0b1111111100000000) | Value)
#else
    #define ASSIGN_L_NIP(Reg, Value)    (Reg = (Reg & 0b11110000) | Value)
#endif
#if REG_BITS == 32
    #define TGL_H_NIP(Reg)    (Reg = (Reg ^ 0b11111111111111110000000000000000))
#elif REG_BITS == 16
    #define TGL_H_NIP(Reg)    (Reg = (Reg ^ 0b1111111100000000))
#else
    #define TGL_H_NIP(Reg)    (Reg = (Reg ^ 0b11110000))
#endif
#if REG_BITS == 32
    #define TGL_L_NIP(Reg)    (Reg = (Reg ^ 0b00000000000000001111111111111111))
#elif REG_BITS == 16
    #define TGL_L_NIP(Reg)    (Reg = (Reg ^ 0b0000000011111111))
#else
    #define TGL_L_NIP(Reg)    (Reg = (Reg ^ 0b00001111))
#endif
#define SWAP_NIB(Reg)    (Reg = (Reg >> (REG_BITS/2)) | (Reg << (REG_BITS/2)))
#define CONC_PRE(B7,B6,B5,B4,B3,B2,B1,B0)	0b##B7##B6##B5##B4##B3##B2##B1##B0
#define CONC(B7,B6,B5,B4,B3,B2,B1,B0)	CONC_PRE(B7,B6,B5,B4,B3,B2,B1,B0)


/* uncomment this section to check the macros */
/*
char* toBinary(int num, int length);

int main()
{
    int Reg = 0b00001111;
    //SET_H_NIP(Reg);
    char* binary = toBinary(Reg, 8);
    printf("the binary representation is:   %s\n", binary);

    free(binary);

    return 0;
}

char* toBinary(int num, int length)
{
    
    char* binary = (char*) malloc(length * sizeof(char));
    int j = 0;
    
    for(unsigned i = (1 << length-1); i > 0; i /= 2)
    {
        binary[j++] = (num & i)? '1' : '0';
    }
    binary[j] = '\0';
    return binary;
}
*/

 
#endif		/* STD_UTILS_H */
