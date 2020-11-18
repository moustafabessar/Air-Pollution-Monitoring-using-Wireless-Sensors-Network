/*
 * comman.h
 *
 * Created: 9/3/2016 3:14:30 PM
 *  Author: Ahmed Hossam
 */ 


#ifndef COMMAN_H_
#define COMMAN_H_
#define clr_bit(reg,bitno) reg=reg&(~(1<<bitno))
#define Set_bit(reg,bitno) reg=reg|(1<<bitno)
#define Get_bit(reg,bitno) (reg&(1<<bitno))>>bitno
#define Toggle_bit(reg,bitno) reg=(reg^(1<<bitno))
#define SEI() __asm__("SEI")
#define CLI() __asm__("CLI")



#endif /* COMMAN_H_ */