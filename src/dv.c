/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.4a Advanced
Automatic Program Generator
© Copyright 1998-2009 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Digital Voltmeter
Version : 2.0
Date    : 1393 Esfand 21
Author  : Meysam Parvizi
Company : 
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

// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))

unsigned char digits[10] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
float x = 0;
unsigned char i=0;

void shiftPORTB(unsigned char i)
{
   switch (i)
   {
      case 0:
         PORTB = 0b00001110;
         break;
      case 1:
         PORTB = 0b00001101;
         break;
      case 2:
         PORTB = 0b00001011;
         break;
      case 3:
         PORTB = 0b00000111;
         break;   
   }
}

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here



/*******************************************************************/

    unsigned char n[4];
    unsigned int temp;
    unsigned char signFlag=0;
    float tempx;
        
    tempx = x;
    
    if (tempx <= -100 || tempx >= 100)
    {
        PORTB.0 = 1;
        PORTB.1 = 1;
        PORTB.2 = 1;
        PORTB.3 = 1;
    }
    else
    {
        if (tempx < 0)
        {   
            tempx = -tempx;
            signFlag=1;
        }
        else
        {
            signFlag=0;
        }
        
         if (tempx == 0)
         {
             n[3] = 0;
             n[2] = 0;
             n[1] = 0;
             n[0] = 0;
         }
         else
         {
             temp = tempx * 100;
             n[3] = temp / 1000;
             temp = temp - n[3] * 1000;
             n[2] = temp / 100;
             temp = temp - n[2] * 100;
             n[1] = temp / 10;
             n[0] = temp - n[1] * 10;
         }

         PORTD = digits[n[i]];
         
         if (i==0)
         {
            if (signFlag) PORTD.7=1; else  PORTD.7=0;
         }
         
         if (i==2) PORTD.7=1;
          
         shiftPORTB(i);
         i++;
         if (i==4) i=0;
    }

/******************************************************************/

}          

void main(void)
{

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
// Clock value: 125.000 kHz
TCCR0=(0<<CS02) | (1<<CS01) | (1<<CS00);
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
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<TOIE0);


// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 125.000 kHz
// ADC Voltage Reference: AVCC pin
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ACME);

// Global enable interrupts
#asm("sei")

PORTB=0b00001110;

while (1)
      {

      x = ((float)read_adc(5) * 4.93) / 1023;
      x = (x - 2.428) * 10.43478;
      delay_ms(200);

      
      
      };
}
