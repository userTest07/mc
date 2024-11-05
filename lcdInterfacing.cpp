#include <p18f4550.h>
#pragma config FOSC = HS
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF



#define LCD_DATA    PORTD
#define ctrl        PORTE
#define en          PORTEbits.RE2
#define rw          PORTEbits.RE1
#define rs          PORTEbits.RE0

void myMsDelay(unsigned int time);
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_write_string(const char *str);

void main()
{
    char msg1[] = "ICOER E&TC";
    char msg2[] = "Welcome-JSPM ";

    TRISD = 0x00; 
    TRISE = 0x00; 
    ADCON1 = 0x0E; 

    init_LCD();          
    
    LCD_write_string(msg1);
    LCD_cmd(0xC0);         
    LCD_write_string(msg2);
    
    while(1) {
        
    }
}

void myMsDelay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 275; j++);
}


void init_LCD(void)
{
    LCD_cmd(0x38);
    myMsDelay(15);

    LCD_cmd(0x01);
    myMsDelay(15);

    LCD_cmd(0x0C);
    myMsDelay(15);

    LCD_cmd(0x80);
    myMsDelay(15);
}


void LCD_cmd(unsigned char cmd)
{
    LCD_DATA = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    myMsDelay(15);
    en = 0;
    myMsDelay(15);
}


void LCD_write(unsigned char data)
{
    LCD_DATA = data;
    rs = 1;
    rw = 0;
    en = 1;
    myMsDelay(15);
    en = 0;
    myMsDelay(15);
}


void LCD_write_string(const char *str)
{
    while (*str)        
    {
        LCD_write(*str);
        myMsDelay(15);
        str++;
    }
}
