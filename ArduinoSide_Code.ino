
#include <EEPROM.h>
#include<string.h>
#define Baud 2400
int addr = 0;
void setup()
{
  //Configure UART 
  UBRR0  = 47;                 //2400 baud at frequency = 1.8432MHz   
  UCSR0B = (1<<3) | (1<<4);    //Enable TX and RX  
  UCSR0C = (1<<1) |(1<<2);    // 8 bit frame
  UCSR0C = ~(1<<3);            //1 Stop bit
}

void loop()
{
  //Recieve Data from PC to Arduino
  char receivedchar;
   while (1) {
   while(!(UCSR0A & (1<<7)));
  	receivedchar = UDR0;
     if(receivedchar == '\0')
     {
       break;
     }
     
     EEPROM.write((uint8_t*)addr,receivedchar);
     addr++;
   }
     
  
  //Transmit Data from Arduino to PC
    addr = 0;
  	while(1)
	 { 
		while(!(UCSR0A & (1<<5)));
  			UDR0 = EEPROM.read(addr);
      		addr++;
 		if (EEPROM.read(addr) == '\0')
   		{
    		break;
  		}
    }
  delay(1000);	
}



