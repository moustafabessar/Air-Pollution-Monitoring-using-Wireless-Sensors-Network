
#include "Registers.h"
#include "util/delay.h"
#include "comman.h"
#include "DIO_lcd.h"

char DIO_WritePinVal(char PIN_NUM , char Val){
	char PIN_Index=PIN_NUM%8;
	char PIN_location=PIN_NUM/8;
	   
	   if (Val==1)
	   {
	   
	   switch(PIN_location){
		   case 0: Set_bit(E_DDRA,PIN_Index);
		           Set_bit(E_portA,PIN_Index);
		    break;
			case 1: 
			  Set_bit(E_DDRB,PIN_Index);
			  Set_bit(E_portB,PIN_Index);
			break;
			case 2: 
			  Set_bit(E_DDRC,PIN_Index);
			  Set_bit(E_portC,PIN_Index);
			break;
			case 3: 
			  Set_bit(E_DDRD,PIN_Index);
			  Set_bit(E_portD,PIN_Index);
			break;
			default:
			break;
	   }
	}else if (Val==0){
		 
		 switch(PIN_location){
			 case 0: 
			    Set_bit(E_DDRA,PIN_Index);
			    clr_bit(E_portA,PIN_Index);
			 break;
			 case 1:
			       Set_bit(E_DDRB,PIN_Index);
			       clr_bit(E_portB,PIN_Index);
			 break;
			 case 2: 
			      Set_bit(E_DDRC,PIN_Index);
			      clr_bit(E_portC,PIN_Index);
			 break;
			 case 3:
			      Set_bit(E_DDRD,PIN_Index);
			      clr_bit(E_portD,PIN_Index);
			 break;
			 default:
			 break;
		 }
	}
	
}
char DIO_TogglePinVal(char PIN_NUM){
	char PIN_Index=PIN_NUM%8;
	char PIN_location=PIN_NUM/8;
	switch(PIN_location){
		case 0: 
		Set_bit(E_DDRA,PIN_Index);
		Toggle_bit(E_portA,PIN_Index);
		break;
		case 1:
		Set_bit(E_DDRB,PIN_Index);
		Toggle_bit(E_portB,PIN_Index);
		break;
		case 2:
		Set_bit(E_DDRC,PIN_Index);
		Toggle_bit(E_portC,PIN_Index);
		break;
		case 3:
		Set_bit(E_DDRD,PIN_Index);
		Toggle_bit(E_portD,PIN_Index);
		break;
		default:
		break;
	}
	
}
char DIO_WritePinDir(char PIN_NUM , char Val){
	char PIN_Index=PIN_NUM%8;
	char PIN_location=PIN_NUM/8;
	
	if (Val==1)
	{
		
		switch(PIN_location){
			case 0: Set_bit(E_DDRA,PIN_Index);
			
			break;
			case 1:
			Set_bit(E_DDRB,PIN_Index);
			
			break;
			case 2:
			Set_bit(E_DDRC,PIN_Index);
			
			break;
			case 3:
			Set_bit(E_DDRD,PIN_Index);
			
			break;
			default:
			break;
		}
	}
	else if (Val==0){
		
		switch(PIN_location){
			case 0:
			clr_bit(E_DDRA,PIN_Index);
			
			break;
			case 1:
			clr_bit(E_DDRB,PIN_Index);
			
			break;
			case 2:
			clr_bit(E_DDRC,PIN_Index);
			
			break;
			case 3:
			clr_bit(E_DDRD,PIN_Index);
			
			break;
			default:
			break;
		}
	}
}
char DIO_ReadPinVal(char PIN_NUM , char *Val){
	char PIN_Index=PIN_NUM%8;
	char PIN_location=PIN_NUM/8;
	
	 switch(PIN_location){
		 case 0: 
		    clr_bit(E_DDRA,PIN_Index);
		   *Val=Get_bit(E_PINA,PIN_Index);
		 break;
		 
		 case 1:
		 clr_bit(E_DDRB,PIN_Index);
		 *Val=Get_bit(E_PINB,PIN_Index);
		 break;
		 case 2:
		 clr_bit(E_DDRC,PIN_Index);
		 *Val=Get_bit(E_PINC,PIN_Index);
		 break;
		 
		 case 3:
		 clr_bit(E_DDRD,PIN_Index);
		 *Val=Get_bit(E_PIND,PIN_Index);
		 break;
		 
		 default:
		 break;
	 }
	
	
}
char DIO_WritePortVal(char PORT_NUM , char Val){
	switch(PORT_NUM)
	{
		case 0:
		E_portA=Val;
		break;
		
		case 1:
		E_portB=Val;
		break;
		
		case 2:
		E_portC=Val;
		break;
		
		case 3:
		E_portD=Val;
		break;
		
		default:
		break;
	}
}
char DIO_ReadPortVal(char PORT_NUM,char *Val){
	switch(PORT_NUM)
	{
		case 0:
		*Val=E_PINA;
		
		break;
		
		case 1:
		*Val=E_PINB;
		
		break;
		case 2:
		*Val=E_PINC;
		
		break;
		
		case 3:
		*Val=E_PIND;
		
		break;
		
		default:
		break;
	}
}
char DIO_WritePortDir(char PORT_NUM , char Val){
	switch(PORT_NUM)
	{
		case 0:
		E_DDRA=Val;
		
		break;
		
		case 1:
		E_DDRB=Val;
		
		break;
		case 2:
		E_DDRC=Val;
		
		break;
		
		case 3:
		E_DDRD=Val;
		
		break;
		
		default:
		break;
	}
}
void DIO_Init(void)
{
	PORTA=PORTA_init ;
	PORTB=PORTB_init ;
	PORTC=PORTC_init ;
	PORTD=PORTD_init ;
	
	DDRA=DDRA_init ;
	DDRB=DDRB_init ;
	DDRC=DDRC_init ;
	DDRD=DDRD_init ;
	
}


