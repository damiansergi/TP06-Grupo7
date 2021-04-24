
#include "damianLCD.h"
#include <iostream> 

using namespace std;

#define DISPLAYWIDTH 720
#define DISPLAYHEIGHT 240

#define ALLEGRODISPLAYWIDTH 1280
#define ALLEGRODISPLAYHEIGHT 720

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
    if (!(font = al_load_font("LiberationSerif-Regular.ttf", 50, 0))) {

        cout << "failed to initialize the font!\n" << endl;
        error = true;
    }

    display = al_create_display(ALLEGRODISPLAYWIDTH, ALLEGRODISPLAYHEIGHT);
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



    al_clear_to_color(al_map_rgb(255,255,255));

    al_draw_filled_rectangle((ALLEGRODISPLAYWIDTH -DISPLAYWIDTH) / 2,
                            (ALLEGRODISPLAYHEIGHT-DISPLAYHEIGHT)/2 ,
        ((ALLEGRODISPLAYWIDTH - DISPLAYWIDTH) / 2) + (ALLEGRODISPLAYWIDTH - DISPLAYWIDTH),
        ((ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT) / 2) + (ALLEGRODISPLAYHEIGHT - DISPLAYHEIGHT),
        al_map_rgb(50, 150, 200));


    al_flip_display();

    return true;
}

bool damianLCD::lcdClearToEOL() {

    return true;
}
basicLCD& damianLCD::operator<<(const unsigned char c) {

    return *this;
}
basicLCD& damianLCD::operator<<(const char* c) {

    return *this;
}
bool damianLCD::lcdMoveCursorUp() {

    return true;
}
bool damianLCD::lcdMoveCursorDown() {

    return true;
}
bool damianLCD::lcdMoveCursorRight() {

    return true;
}
bool damianLCD::lcdMoveCursorLeft() {

    return true;
}
bool damianLCD::lcdSetCursorPosition(const cursorPosition pos) {

    return true;
}
cursorPosition damianLCD::lcdGetCursorPosition() {

    cursorPosition salida = { 0,0 };

    return salida;
}
