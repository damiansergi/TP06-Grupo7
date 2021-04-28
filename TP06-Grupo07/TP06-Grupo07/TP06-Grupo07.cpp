// TP06-Grupo07.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "damianLCD.h"
#include "milagrosLCD.h"
#include "salvaLCD.h"

#define DELAY 1 //seconds

void testLCD(basicLCD* p2LCD) {

    if (p2LCD->lcdInitOk()) {

        *p2LCD << "There are no wrong notes on piano";

        al_rest(DELAY);

        p2LCD->lcdClearToEOL();

        al_rest(DELAY);

        *p2LCD << 'J';

        al_rest(DELAY);

        p2LCD->lcdClear();

        al_rest(DELAY);

        cursorPosition testPos = { 0, 10 };
        p2LCD->lcdSetCursorPosition(testPos);
        *p2LCD << 'I';

        al_rest(DELAY);

        p2LCD->lcdMoveCursorRight();
        *p2LCD << 'U';

        al_rest(DELAY);

        p2LCD->lcdMoveCursorDown();
        p2LCD->lcdMoveCursorLeft();
        *p2LCD << 'P';

        al_rest(DELAY);

        p2LCD->lcdMoveCursorRight();
        *p2LCD << 'I';

        al_rest(DELAY);

        p2LCD->lcdMoveCursorUp();
        *p2LCD << "TEST123";

        al_rest(DELAY);

        testPos.row = 1;
        testPos.column = 14;
        p2LCD->lcdClear();
        p2LCD->lcdSetCursorPosition(testPos);
        *p2LCD << "hola";

        al_rest(5 * DELAY);

        p2LCD->lcdClear();
        *p2LCD << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

        al_rest(5 * DELAY);
    }

}


int main()
{

    basicLCD* p2LCD = nullptr;

    for (int i = 1; i <= 3; i++) { 

        if (i == 1) {

            damianLCD LCDDami;
            p2LCD = &LCDDami;
            testLCD(p2LCD);
        }
        else if (i == 2) {
            
            milagrosLCD LCDMili;
            p2LCD = &LCDMili;
            testLCD(p2LCD);
            
        }
        else if (i == 3) {

            salvaLCD LCDSalva;
            p2LCD = &LCDSalva;
            testLCD(p2LCD);
        }
    }

    return 0;
}
