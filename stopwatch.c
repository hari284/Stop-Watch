#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#define lcd PORTD
#define t 1
void lcd_init()
{
  lcd_command(0x02);//home position
  lcd_command(0x28);//4-bit mode,,,(0x38) for 8-bit mode
  lcd_command(0x0c);//cursor off
  lcd_command(0x06);//auto increament in address's
}
void lcd_string(unsigned char *str)
{
  char i=0;
  while(str[i]!='\0')
  {
    lcd_data(str[i]);
	i++;
  }
}
void lcd_command(unsigned char cmd)
{
  lcd=(cmd&0xf0);
  lcd|=0x04;
  _delay_ms(t);
  lcd&=0xf0;
 _delay_ms(t);
  
  lcd=(cmd<<4)&0xf0;//to assure that there will not be any garbage value in lcd
  lcd|=0x04;
  _delay_ms(t);
  lcd&=0xf0;
  _delay_ms(t);
}

void lcd_data(unsigned char data)
{
  lcd=(data&0xf0);
  lcd|=0x05;
 _delay_ms(t);
  lcd&=0xf1;
  _delay_ms(t);
  
  lcd=(data<<4)&0xf0;//to assure that there will not be any garbage value in lcd
  lcd|=0x05;
  _delay_ms(t);
  lcd&=0xf1;
  //_delay_ms(t);
}

void main()
{
  DDRD=0xff;
  lcd_init();
  
  while(1)
  { 
     lcd_command(0x82);
	 lcd_string("STOP WATCH");
	 //_delay_ms(1);
     lcd_command(0xc4);
	 lcd_string("00:00:00");
	 //_delay_ms(1);
	 /////////FOR 99:59:99 PATTERN///////////
	 for(char n=0;n<=9;n++)
	 {
	   for(char p=0;p<=9;p++)
	   {
		for(char m=0;m<6;m++)
		{
			for(char k=0;k<=9;k++)
			{
				for(char j=0;j<=9;j++)
				{
				     for(char i=0;i<=9;i++)
					 { lcd_command(0xcb);
					   lcd_data(i+48);
					   //_delay_ms(1);
	  
					 }
				    lcd_command(0xca);
					lcd_data(49+j);
				}
				 lcd_command(0xca);
				 lcd_string("00"); 
  
			    lcd_command(0xc8);
				lcd_data(49+k);

			}
			lcd_command(0xc7);
			lcd_data(49+m);
			lcd_command(0xc8);
			lcd_data(48);
			
		}
		lcd_command(0xca);
		lcd_string("00"); 
		lcd_command(0xc7);
        lcd_string("00");
		lcd_command(0xc5);
		lcd_data(49+p);
		if((n==2)&&(p==2))
	     goto hell;
   }

      lcd_command(0xc4);
	  lcd_data(49+n);
	  lcd_command(0xc5);
	  lcd_data(48);
	  
	 
 }    
      hell:
     lcd_command(0xc4);
     lcd_string("00:00:00");  
	 _delay_ms(1000); 
  }
}
