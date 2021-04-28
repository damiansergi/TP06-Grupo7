// TP06-Grupo07.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "damianLCD.h"
#include "milagrosLCD.h"
#include "salvaLCD.h"

#define DELAY 3 //seconds

void testLCD(basicLCD* p2LCD) {

    if (p2LCD->lcdInitOk()) {

        cout << "Test Start" << endl;

        *p2LCD << "There are no wrong notes on piano";

        al_rest(DELAY);
        cout << "test 1 finished" << endl; 

        p2LCD->lcdClearToEOL();

        al_rest(DELAY);
        cout << "test 2 finished" << endl;

        *p2LCD << 'J';

        al_rest(DELAY);
        cout << "test 3 finished" << endl;

        p2LCD->lcdClear();

        al_rest(DELAY);
        cout << "test 4 finished" << endl;

        cursorPosition testPos = { 0, 10 };
        p2LCD->lcdSetCursorPosition(testPos);
        *p2LCD << 'I';

        al_rest(DELAY);
        cout << "test 5 finished" << endl;

        p2LCD->lcdMoveCursorRight();
        *p2LCD << 'U';

        al_rest(DELAY);
        cout << "test 6 finished" << endl;

        p2LCD->lcdMoveCursorDown();
        p2LCD->lcdMoveCursorLeft();
        *p2LCD << 'P';

        al_rest(DELAY);
        cout << "test 7 finished" << endl;

        p2LCD->lcdMoveCursorRight();
        *p2LCD << 'I';

        al_rest(DELAY);
        cout << "test 8 finished" << endl;

        p2LCD->lcdMoveCursorUp();
        *p2LCD << "TEST123";

        al_rest(DELAY);
        cout << "test 9 finished" << endl;

        testPos.row = 1;
        testPos.column = 14;
        p2LCD->lcdClear();
        p2LCD->lcdSetCursorPosition(testPos);
        *p2LCD << "hola";

        al_rest(5 * DELAY);
        cout << "test 10 finished" << endl;

        p2LCD->lcdClear();
        *p2LCD << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

        al_rest(5 * DELAY);
        cout << "test 11 finished" << endl;
    }

}


int main()
{

    basicLCD* p2LCD = nullptr;

    for (int i = 3; i <= 3; i++) { 

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
