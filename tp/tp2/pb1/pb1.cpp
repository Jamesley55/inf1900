#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t D2 = 0x04;
const uint8_t debounce = 10;
const uint8_t rouge = (1 << 0);
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
void alumerDel();
int main()
{
    PORTA |= (1 << DDA0) | (1 << DDA1);
    DDRD = 0x0;
    Etats etat = Etats::INIT;
    for (;;)
    {

        switch (etat)
        {
        case Etats::INIT:
            if (estPresser())
                etat = Etats::EA;
            break;
        case Etats::EA:
            if (estPresser())
                etat = Etats::EB;
            break;

        case Etats::EB:
            if (estPresser())
                etat = Etats::EC;
            break;

        case Etats::EC:
            if (estPresser())
                etat = Etats::ED;
            break;
        case Etats::ED:
            if (estPresser())
                etat = Etats::EE;
            break;
        case Etats::EE:
            if (estPresser())
            {
                alumerDel();
                etat = Etats::INIT;
            }
            break;
        }
    }
    return 0;
}

bool estPresser()
{
    if (PIND & D2)
    {
        _delay_ms(debounce);
        if (PIND & D2)
        {
            return true;
        }
    }
    return false;
}
void alumerDel()
{
    PORTA = rouge;
    _delay_ms(1000);
}