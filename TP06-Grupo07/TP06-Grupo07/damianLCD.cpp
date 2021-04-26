
#include "damianLCD.h"
#include <iostream> 

using namespace std;

#define DISPLAYWIDTH 720
#define DISPLAYHEIGHT 120

#define ALLEGRODISPLAYWIDTH 1280
#define ALLEGRODISPLAYHEIGHT 720

static int CursorPosToNumber(cursorPosition pos);  //Translate from the cursor position to the index in the string

damianLCD::damianLCD() {

    error = false;

    if (!al_init()){

        cout << "failed to initialize allegro!\n" << endl;
        error = true;
    }

    if (!al_init_primitives_addon()) {

        cout << "failed to initialize allegro primitives!\n" << endl;
        error = true;
    }
    if (!al_init_font_addon()) {

        cout << "failed to initialize allegro fonts!\n" << endl;
        error = true;
    }
    if (!al_init_ttf_addon()) {

        cout << "failed to initialize allegro ttf!\n" << endl;
        error = true;
    }
    if (!(font = al_load_ttf_font("LiberationSerif-Regular.ttf", 50, 0))) {

        cout << "failed to initialize the font!\n" << endl;
        error = true;
    }

    display = al_create_display(ALLEGRODISPLAYWIDTH, ALLEGRODISPLAYHEIGHT);

    pos.column = 1;
    pos.row = 1;
    message = string("                                ");
}

damianLCD::~damianLCD() {

    al_destroy_display(display);
}

bool damianLCD::lcdInitOk() {

    if (error == true){
    
        return false;
    }

    if (display == nullptr) {

        return false;
    }

    return true;

}


lcdError& damianLCD::lcdGetError() {

    return damianLCDError;
}


bool damianLCD::lcdClear() {

    message.clear();
    message = string("                                ");
    pos.row = 1;
    pos.column = 1;

    printMessage();

    return true;
}

bool damianLCD::lcdClearToEOL(){  

    if (pos.row == 1) {

        message.replace(0, 16, "                ");
    }
    else if (pos.row == 2) {

        message.replace(16, 16, "                ");
    }

    printMessage();

    return true;
}

basicLCD& damianLCD::operator<<(const unsigned char c) { 

    if (isprint(c)) {
        message.replace(CursorPosToNumber(pos), 1, 1, c);

        printMessage();
    }
    return *this;
}

basicLCD& damianLCD::operator<<(const char* c) {

    string auxString = string(c);
    int index = CursorPosToNumber(pos);
    int copyIndex = 0;

     while (auxString.size() > 32) {

         auxString.erase(0, 1);
     }

     while (index < 32 && copyIndex < auxString.size() ) {

         message.replace(index, 1, 1, auxString[copyIndex] );
         index++;
         copyIndex++;
     }

    printMessage();

    return *this;
}

bool damianLCD::lcdMoveCursorLeft() {

    if (pos.column == 1 && pos.row == 2) {

        pos.column = 16;
        pos.row = 1;
    }
    else if (pos.column > 1) {
        pos.column--;
    }


    return true;
}

bool damianLCD::lcdMoveCursorRight() {

    if (pos.column == 16 && pos.row == 1) {

        pos.column = 1;
        pos.row = 2;
    }
    else if (pos.column < 16) {
        pos.column++;
    }

    return true;
}

bool damianLCD::lcdMoveCursorDown() {

    if (pos.row == 1) {
        pos.row++;
    }

    return true;
}

bool damianLCD::lcdMoveCursorUp() {

    if (pos.row == 2) {
        pos.row--;
    }

    return true;
}

bool damianLCD::lcdSetCursorPosition(const cursorPosition pos) {

    if (pos.column <= 16 && pos.row <= 2 && pos.column >= 1 && pos.row >= 1) {
            
        this->pos = pos;
    }
    else {

        return false;
    }

    return true;
}

cursorPosition damianLCD::lcdGetCursorPosition() {

    return pos;
}

bool damianLCD::printMessage() {

    char buffer[2] = {1, '\0'};

    al_clear_to_color(al_map_rgb(255, 255, 255));

    al_draw_filled_rectangle(((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) - 50,
        ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2) - 50,
        (((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + DISPLAYWIDTH) + 50,
        (((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2) + DISPLAYHEIGHT) + 50,
        al_map_rgb(146, 42, 141));

    al_draw_filled_rectangle((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2,
        (ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2,
        ((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + DISPLAYWIDTH,
        ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2) + DISPLAYHEIGHT,
        al_map_rgb(50, 150, 200));

    al_draw_rectangle((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2,
        (ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2,
        ((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + DISPLAYWIDTH,
        ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2) + DISPLAYHEIGHT,
        al_map_rgb(0, 0, 0), 5);

    al_draw_line((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2, ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2) + DISPLAYHEIGHT / 2,
        ((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + DISPLAYWIDTH,
        ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2) + DISPLAYHEIGHT - DISPLAYHEIGHT / 2, al_map_rgb(0, 0, 0), 5);

    for (int i = 0; i < 16; i++) {

        al_draw_line(((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + 45 * i, ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2),
            ((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + 45 * i, ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2) + DISPLAYHEIGHT,
            al_map_rgb(0, 0, 0), 5);
    }

    for (int i = 0; i < message.size(); i++) {
        buffer[0] = message[i];

        if (i < 16) {
            al_draw_text(font, al_map_rgb(0, 0, 0), ((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + 10 + 45 * i,
                ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2),
                0, buffer);
        }
        else if (i<32) {
            al_draw_text(font, al_map_rgb(0, 0, 0), ((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + 10 + 45 * (i - 16),
                ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2 + 60),
                0, buffer);
        }
    }
    al_flip_display();

    return true;
}

static int CursorPosToNumber(cursorPosition pos) {  //Translate from the cursor position to the index in the string

    return (pos.row - 1) * 16 + (pos.column - 1);
}