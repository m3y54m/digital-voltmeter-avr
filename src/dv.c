/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.4a Advanced
Automatic Program Generator
© Copyright 1998-2009 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Digital Voltmeter
Version : 
Date    : 12/5/2013
Author  : Meysam Parvizi
Company : University of Zanjan Robotics Association
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega8.h>

#include <delay.h>

#define ADC_VREF_TYPE 0x00

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

void digit(unsigned char mnum)
{
    switch (mnum)
    {
        case 0:
            PORTD = 0b00111111;
            break;
        case 1:
            PORTD = 0b00000110;
            break;    
        case 2:
            PORTD = 0b01011011;
            break;     
        case 3:
            PORTD = 0b01001111;
            break;
        case 4:
            PORTD = 0b01100110;
            break;    
        case 5:
            PORTD = 0b01101101;
            break;    
        case 6:
            PORTD = 0b01111101;
            break;    
        case 7:
            PORTD = 0b00000111;
            break;
        case 8:
            PORTD = 0b01111111;
            break;
        case 9:
            PORTD = 0b01101111;
            break;
        case 10:
            PORTD = 0b00000000;
    }
}

void dot(unsigned char ch)
{
    if (ch == 1)
        PORTD.7 = 1;
    else
        if (ch == 0)
            PORTD.7 = 0;
}

void print_number(float input_num, unsigned int delay_t)
{
    unsigned char n1;
    unsigned char n2;
    unsigned char n3;
    unsigned char n4;
    unsigned int temp;

    if (input_num <= -100 || input_num >= 100)
    {
        PORTB.0 = 1;
        PORTB.1 = 1;
        PORTB.2 = 1;
        PORTB.3 = 1;
    }
    else
    {
        if (input_num >= 0)
        {   
            if (input_num == 0)
            {
                n4 = 0;
                n3 = 0;
                n2 = 0;
                n1 = 0;
            }
            else
            {
                temp = input_num * 100;
                n4 = temp / 1000;
                temp = temp - n4 * 1000;
                n3 = temp / 100;
                temp = temp - n3 * 100;
                n2 = temp / 10;
                n1 = temp - n2 * 10;
            }
            
            PORTB.0 = 0;
            digit(n1);
            delay_ms(delay_t);
            PORTB.0 = 1;
            PORTB.1 = 0;
            digit(n2);
            delay_ms(delay_t);
            PORTB.1 = 1;
            PORTB.2 = 0;
            digit(n3);
            dot(1);
            delay_ms(delay_t);
            PORTB.2 = 1;
            PORTB.3 = 0;
            digit(n4);
            delay_ms(delay_t);
            PORTB.3 = 1;
        }
        else
        {
            input_num = -input_num;
            if (input_num == 0)
            {
                n4 = 0;
                n3 = 0;
                n2 = 0;
                n1 = 0;
            }
            else
            {
                temp = input_num * 100;
                n4 = temp / 1000;
                temp = temp - n4 * 1000;
                n3 = temp / 100;
                temp = temp - n3 * 100;
                n2 = temp / 10;
                n1 = temp - n2 * 10;
            }
            
            PORTB.0 = 0;
            digit(n1);
            dot(1);
            delay_ms(delay_t);
            PORTB.0 = 1;
            PORTB.1 = 0;
            digit(n2);
            delay_ms(delay_t);
            PORTB.1 = 1;
            PORTB.2 = 0;
            digit(n3);
            dot(1);
            delay_ms(delay_t);
            PORTB.2 = 1;
            PORTB.3 = 0;
            digit(n4);
            delay_ms(delay_t);
            PORTB.3 = 1;
            
        }
    }
}

void print_error(unsigned int delay_t)
{
    PORTB.0 = 0;
    PORTD = 0b01010000;
    delay_ms(delay_t);
    PORTB.0 = 1;
    PORTB.1 = 0;
    PORTD = 0b01010000;
    delay_ms(delay_t);
    PORTB.1 = 1;
    PORTB.2 = 0;
    PORTD = 0b01111001;
    delay_ms(delay_t);
    PORTB.2 = 1;
    PORTB.3 = 1;
    delay_ms(delay_t);
}
            
// Declare your global variables here

void main(void)
{
// Declare your local variables here
float x = 0;
unsigned int dt = 1;

// Input/Output Ports initialization
// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=T State6=T State5=T State4=T State3=1 State2=1 State1=1 State0=1 
PORTB=0x0F;
DDRB=0x0F;

// Port C initialization
// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTD=0x00;
DDRD=0xFF;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
TCCR0=0x00;
TCNT0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 125.000 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x86;

while (1)
      {
      dt = 1;
      x = ((float)read_adc(5) * 4.88) / 1024;
      x = (x - 2.40185) * 10.43478;
      if (x > 25 || x < -25)
        print_error(dt);
      else       
        print_number(x,dt);
      };
}
