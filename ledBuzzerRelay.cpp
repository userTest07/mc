#include <p18f4520.h>
#pragma config FOSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF
#define lrbit PORTBbits.RB4 //SW0 interfaced to RB4
#define rlbit PORTBbits.RB5 //SW1
#define buzzer PORTCbits.RC2
#define relay PORTCbits.RC1
void MsDelay (unsigned int time)
{
 unsigned int i, j;
 for (i = 0; i < time; i++)
 for (j = 0; j < 275; j++);
}
void main()
{
 unsigned char val=0;
 INTCON2bits.RBPU=0; 
 ADCON1 = 0x0F; 
 TRISBbits.TRISB4=1;
 TRISBbits.TRISB5=1;
 TRISCbits.TRISC1=0;
 TRISCbits.TRISC2=0;
 TRISD = 0x00;
 PORTD = 0x00;
 buzzer = 0; 
 relay = 0;
while (1)
{
 if (!(lrbit))
 val = 1;
 if (!(rlbit))
 val = 2;
 if (val == 1)
 {
 buzzer = 1;
 relay = 1;
 PORTD = PORTD >>1;
 if (PORTD == 0x00)
 PORTD = 0x80;
 MsDelay(250);
 }
 if (val == 2)
 {
buzzer = 0;
 relay = 0;
 PORTD = PORTD<<1;
 if (PORTD == 0x00)
 PORTD = 0x01;
 MsDelay(250);
 }
 }
}
