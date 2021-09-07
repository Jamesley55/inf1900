#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

void Couleur()
{
    DDRB = 0xff; // PORT B est en mode sortie

    for (;;)
    {
        PORTB = (1 << 0); // rouge

        _delay_ms(1000); //1 sec

        PORTB = (1 << 1); // vert

        _delay_ms(1000); // 1 sec

        double compteur = 0;
        while (compteur <= 100)
        { // Ambre
            PORTB = 0x02;

            _delay_ms(10);

            PORTB = 0x01;

            _delay_ms(2);
            compteur++;
        }
    }
}

void InterupteurAmbre()
{
    DDRB = 0xff; // PORT B est en mode sortie
    DDRB = 0x0;  // PORT A est en mode entree
    for (;;)
    {
        if (PIND & 0x04)
        {
            _delay_ms(10);
            while (PIND & 0x04)
            {

                PORTB = 0x01;
                _delay_ms(2);
            }
        }
    }
    PORTB = 0x00;
}

int main()
{
    Couleur();
    InterupteurAmbre();
    return 0;
}
