// TP06-Grupo07.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "damianLCD.h"
#include "milagrosLCD.h"
#include "salvaLCD.h"
#include <windows.h>

#define DELAY 1000


int main()
{
    milagrosLCD LCDMili;
    damianLCD LCDDami;
    salvaLCD LCDSalva; 
    basicLCD* p2LCD = nullptr;

    for (int i = 1; i <= 2; i++) {  //CAMBIAR A I<=3 PARA PONER LAS OTRAS IMPLEMENTACIONES

        if (i == 1) {

            p2LCD = &LCDDami;
        }
        else if (i == 2) {

            p2LCD = &LCDMili;
        }
        else if (i == 3) {

            p2LCD = &LCDSalva; 
        }

        if (p2LCD->lcdInitOk()) {

            *p2LCD << "There are no wrong notes on piano";

            Sleep(DELAY);

            p2LCD->lcdClearToEOL();

            Sleep(DELAY);

            *p2LCD << 'J';

            Sleep(DELAY);

            p2LCD->lcdClear();

            Sleep(DELAY);

            cursorPosition testPos = { 1,10 };
            p2LCD->lcdSetCursorPosition(testPos);
            *p2LCD << 'I';

            Sleep(DELAY);

            p2LCD->lcdMoveCursorRight();
            *p2LCD << 'U';

            Sleep(DELAY);

            p2LCD->lcdMoveCursorDown();
            p2LCD->lcdMoveCursorLeft();
            *p2LCD << 'P';

            Sleep(DELAY);

            p2LCD->lcdMoveCursorRight();
            *p2LCD << 'I';

            Sleep(DELAY);

            p2LCD->lcdMoveCursorUp();
            *p2LCD << "TEST123";

            Sleep(DELAY);
        }
    }

    return 0;
}
