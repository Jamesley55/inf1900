#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t D2 = 0x04;
const uint8_t debounce = 10;
const uint8_t rouge = 0x1;
const uint8_t vert = 0x2;
const uint8_t eteint = 0x0;

enum class Etats
{
    INIT,
    EA,
    EB,
    EC,
    ED,
    EE
};
bool estPresser();
void couleurAmbre();
int main()
{
    DDRA |= (1 << DDA0) | (1 << DDA1);
    DDRD = 0x0;
    Etats etat = Etats::INIT;
    for (;;)
    {
        if (PIND & D2)
        {
            _delay_ms(debounce);
            switch (etat)
            {
            case Etats::INIT:
                
                if (PIND & D2)
                {   
                    etat = Etats::EA;
                }
                break;
            case Etats::EA:
                etat = Etats::EB;
                break;

            case Etats::EB:
                PORTA = vert;
                if (PIND & D2)
                {
                    if (PIND & D2)
                        etat = Etats::EC;
                }
                break;

            case Etats::EC:
                PORTA = rouge;
                if (!(PIND & D2))
                {

                    if (!(PIND & D2))
                        etat = Etats::ED;
                }
                break;
            case Etats::ED:
                PORTA = vert;
            }
        }
        else{
            switch (etat)
            {
            case Etats::INIT:

                PORTA = rouge;
            
                break;
            case Etats::EA:
                couleurAmbre();
                break;
            case Etats::EB:
                PORTA = vert;
                if (PIND & D2)
                {
                    if (PIND & D2)
                        etat = Etats::EC;
                }
                break;

            case Etats::EC:
                PORTA = rouge;
                if (!(PIND & D2))
                {

                    if (!(PIND & D2))
                        etat = Etats::ED;
                }
                break;
            case Etats::ED:
                PORTA = eteint;
                if (PIND & D2)
                {

                    if (PIND & D2)
                        etat = Etats::EE;
                }
                break;
            case Etats::EE:
                PORTA = vert;
                if ((!PIND & D2))
                {
                    if (PIND & D2)
                        Etats::INIT;
                }
            }
        }
        
    }
    return 0;
}
void couleurAmbre()
{
    uint8_t counteur = 0;
    while (counteur < 100)
    {
        PORTB = vert;

        _delay_ms(10);

        PORTB = rouge;

        _delay_ms(2);
        counteur++;
    }
}

bool estPresser()
{
    if (PIND & D2)
    {
        _delay_ms(debounce);
        if (PIND & D2)
            return true;
    }
    return false;
}