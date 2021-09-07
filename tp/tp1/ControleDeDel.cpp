/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */

#define F_CPU 8000000UL // 1 MHz
#include <util/delay_basic.h>
#include <avr/io.h>


void DELRouge(double second);
void DELVert(double second);
void lectureButtonPoussoir();
void DELAmbree();

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie

  for (;;) // boucle sans fin
  {
    // DELRouge(100);
    // DELVert(100);
    // DELAmbree();
    lectureButtonPoussoir();
  }
  return 0;
}

void wait(double second)
{

  for (int i = 0; i < second / 0.26; i++)
  {
    _delay_loop_2(0);
  }
}

void DELVert(double second)
{
  PORTA = (1 << 0); // 0x01
  wait(second);
}

void DELRouge(double second)
{

  PORTA = (1 << 1); // 0x02
  wait(second);
}

void DELAmbree()
{
  for (int i = 0; i < 10; i++)
  {
    DELVert(0.26);
    DELRouge(0.26);
  }
}
void lectureButtonPoussoir(){
  
  DDRD = 0x0;

  if (PIND & 0x04)
  {
    // wait 10ms
    wait(0.26);
    while(PIND & 0x04){
      if(PIND & 0x04)
        DELRouge(1);
      else
      {
        PORTA = 0x0; 
      }
      
    }
    PORTA = 0x0; // 0x02

  }
  // PORTA = (1 << 1); // 0x02
} 