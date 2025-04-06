#include <LPC21xx.H>
#include "header.h"
#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)
u32 temp2,vout,temperature,speed;
extern u32 flag; //CAN Flag
CAN2 v1;
extern unsigned int timer1;
extern unsigned int timer2;
u32 sflag1=0,sflag2=0; //indi. flags
u32 lower=0;
int main()
{
	can2_init();
	uart0_init(9600);
	lcd_init();
	lcd_cgram();

//	lcd_cmd(0xc6);
//	lcd_data(3);
	lcd_cmd(0x80);
	delay_ms(100);
	lcd_data(0);
	lcd_cmd(0x8F);
	lcd_data(1);

	lcd_cmd(0x0C);

	IODIR0=LED1|LED2|LED3;
	IOSET0=LED1|LED2|LED3;


	config_vic_for_timer1();
	timer1_config();
	config_vic_for_CAN2();


	while(1)
	{
		if(flag==1)
		{
			flag=0;

			//temp2=((v1.byteA>>8)&(0xFF)); //pre...
		//	temperature=((v1.byteA)&(0x000000ff));
//			vout=(3.3*temp2)/1023;
//			temperature=(vout-0.5)/0.01;


//			lcd_cmd(0xc1); 
//			lcd_data(((((temperature/10)%10))+48));
//			lcd_data((((temperature%10))+48));
//
//			lcd_cmd(0xc3);
//			lcd_data(7); //Deg.celcius


/////////////////////////////////////////////////////////////////////
			//for battery
//			if(((v1.byteA>>8)&(0x0000FFFF))==0)
//			{
//				lcd_cmd(0xc6);
//				lcd_data(3);
//			} 
//			else if((((v1.byteA>>8)&(0x0000FFFF))>0) &&  (((v1.byteA>>8)&(0x0000FFFF))<=341)) 
//			{
//				lcd_cmd(0xc6);
//				lcd_data(4);
//			}
//			else if((((v1.byteA>>8)&(0x0000FFFF))>341) && (((v1.byteA>>8)&(0x0000FFFF))<=682))
//			{
//				lcd_cmd(0xc6);
//				lcd_data(5);
//			}
//			else    
//			{
//				lcd_cmd(0xc6);
//				lcd_data(6);
//			}

//------------------------------------------------------------
	   temp2=((v1.byteA)&(0xFFFF)); //pre...
			//temperature=((v1.byteA)&(0x000000ff));
			vout=(280*temp2)/1023;
			lcd_cmd(0xc0);
			  lcd_string("speed:");
			lcd_cmd(0xc7);
			lcd_data((((vout/100))+48));
			lcd_data(((((vout/10)%10))+48));
			//lcd_data((((vout%10))+48));












			
            	lcd_data((((temperature%10))+48));
			 //lcd_cmd(0xc);
			  lcd_string(" kmph");



	 //-----------------------------------------------------------------



//////////////////////////////////////////////////////////////////////////////////////
				if((v1.byteA&0xFF)==0x05)
				{
					lcd_cmd(0x87);
					lcd_data(2);
					lcd_data('D');
					IOCLR0=LED1;
				}
				if((v1.byteA&0xFF)==0x06)
				{
					lcd_cmd(0x87);
					lcd_data(' ');
					lcd_data(' ');
					IOSET0=LED1;
				}
//////////////////////////////////////////////////
				if((v1.byteA&0xFF)==0x07) //L ON
				{
					sflag1=1;
				}
				if((v1.byteA&0xFF)==0x09)  //R ON
				{
					sflag2=1;
				}
////////////////////////////////////////
				if(sflag1==1) //for L indi.
				{
					if(timer1==1)
					{
						lcd_cmd(0x80);
						lcd_data(0);
						IOCLR0=LED2;
					}
					else
					{
						lcd_cmd(0x80);
						lcd_data(' ');
						IOSET0=LED2;
					}
				}
				if(((v1.byteA&0xFF)==0x08) || ((v1.byteA&0xFF)==0x09))
				{
					sflag1=0;
					lcd_cmd(0x80);
					lcd_data(0);
					IOSET0=LED2;
				}
////////////////////////////////////////////////

				if(sflag2==1)
				{
					if(timer2==1)
					{
						lcd_cmd(0x8F);
						lcd_data(1);
						IOCLR0=LED3;
					}
					else
					{
						lcd_cmd(0x8F);
						lcd_data(' ');
						IOSET0=LED3;
					}
				}

				if(((v1.byteA&0xFF)==0x07) || ((v1.byteA&0xFF)==0x10))
				{
					sflag2=0;
					lcd_cmd(0x8F);
					lcd_data(1);
					IOSET0=LED3;
				}
			}
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////



			//      uart0_atoi(temperature);




			//                      if(((v1.byteA>>8)&(0x0000FF))>=100) // for temperature
			//                          {^M
			//
			//                              lcd_cmd(0xc1);
			//                              lcd_data(((v1.byteA>>16)&(0xFFFF)/100)+48);
			//                              lcd_data((((v1.byteA>>16)&(0xFFFF)/10)%10)+48);
			//                              lcd_data(((v1.byteA>>16)&(0xFFFF)%10)+48);
			//                              lcd_data('C');
			//                      }
			//                  else
			//                         {
			//                         lcd_cmd(0xc2);^M
			//                         lcd_data(((v1.byteA>>16)&(0xFFFF)/10)+48);^M
			//                         lcd_data(((v1.byteA>>16)&(0xFFFF)%10)+48);^M
			//                         lcd_data('C');^M
			//                         }^M





/*#include <LPC21xx.H>
#include "header.h"
#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)
u32 sflag1,sflag2;;
CAN2 v1;
extern int timer1;
extern int timer2;

int main()
{
 		lcd_init();
	can2_init();
    uart0_init(9600);
	IODIR0=LED1|LED2|LED3;
	IOSET0=LED1|LED2|LED3;	
	config_vic_for_timer1();
	timer1_config();

	config_vic_for_CAN2();
	uart0_tx_string("NodeB\r\n");
    lcd_cgram1();
	lcd_cgram2();
	lcd_cgram3();
	lcd_cmd(0x80);	
	lcd_data(0);
	lcd_cmd(0x83);
	lcd_data(1);
	lcd_cmd(0x86);
	lcd_data(2);
	   
	
while(1)
	{
		switch(v1.byteA&0xFF)
		{
			case 0x05:IOCLR0=LED1;
					 lcd_data(2);
				      break;
			case 0x06:IOSET0=LED1;
					lcd_cmd(0x86);
					lcd_data(' ');
				    break;
			case 0x07:sflag1=1;
					if(sflag1==1){
						if(timer1==1){
						IOCLR0=LED2;
						lcd_cmd(0x80); //left indi
						lcd_data(0);
						}
						else
						{
						IOSET0=LED2;
						lcd_cmd(0x80);
						lcd_data(' ');
						}
				      }				
		   case 0x09:sflag2=1;
		   			if(sflag2==1){
						if(timer2==1){
						IOCLR0=LED3;
						lcd_cmd(0x83);
						lcd_data(1);
						}
						else
						{
						IOSET0=LED3;
						lcd_cmd(0x83);
						lcd_data(' ');
						 }
				    	}
					}*/
//
// if(((v1.byteA>>16)&0xFF)>=0)|| (((v1.byteA>>16)&0xFF ))

// lcd_data(((v1.byteA>>16)&0xFF))


	
/*	if(timer1==1)
				      timer1=0;
					  {
					 if(sflag1)
					  IOCLR0=LED1;
					  else
					  {
					  IOSET0=LED1;
					  }
					 }


					 if((v1.byteA&0xFF)==0x07)
{
sflag1=1;
}
		   	
			if((v1.byteA&0xFF)==0x09)
	   			     	{
	                      sflag2=1;
	                    }  */
