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
        switch (etat)
        {
        case Etats::INIT:
            couleurAmbre();
            break;
        case Etats::EA:
            break;
        case Etats::EB:
            break;
        case Etats::EC:
            break;
        case Etats::ED:
            break;
        case Etats::EE:
            break;
        }
    }
    return 0;
}
void couleurAmbre()
{
    uint8_t counteur = 0;
    while (counteur < 100)
    {
        PORTA = vert;

        _delay_ms(10);

        PORTA = rouge;

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