#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t D2 = 0x04;
const uint8_t debounce = 10;
const uint8_t rouge = (1 << 0);
const uint8_t eteint = (0 << 0);
enum class Etats
{
    INIT,
    EA,
    EB,
    EC,
    ED,
    EE
};

void alumerDel();
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
                    etat = Etats::EA;
                break;
            case Etats::EA:
                if (PIND & D2)
                    etat = Etats::EB;

                break;

            case Etats::EB:
                if (PIND & D2)
                    etat = Etats::EC;

                break;

            case Etats::EC:
                if (PIND & D2)
                    etat = Etats::ED;

                break;
            case Etats::ED:
                if (PIND & D2)
                    etat = Etats::EE;

                break;
            case Etats::EE:
                if (PIND & D2)
                {
                    alumerDel();
                    PORTA = eteint;
                    etat = Etats::INIT;
                }

                break;
            }
        }
        _delay_ms(125);
    }
    return 0;
}

void alumerDel()
{
    PORTA = rouge;
    _delay_ms(1000);
}