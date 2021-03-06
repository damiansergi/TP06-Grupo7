#ifndef MILAGROS_LCD_H__
#define MILAGROS_LCD_H__

#include "basicLCD.h"
#include "allegro5/allegro.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

#define HOME_C	0	
#define HOME_R	0	

#define C_SIZE	45	//Tama?o de las letras

#define COLUMNS	16
#define ROWS	2

#define NEGRO		al_map_rgb(0, 0, 0)
#define ROSA		al_map_rgb(227, 13, 107)
#define BLANCO		al_map_rgb(255, 255, 255)
#define AMARILLO	al_map_rgb(248, 241, 8)
#define AZUL		al_map_rgb(8, 59, 248)
#define VERDE		al_map_rgb(8, 248, 12)
#define NARANJA		al_map_rgb(248, 153, 8)
#define VIOLETA		al_map_rgb(169, 35, 219)
#define CELESTE		al_map_rgb(35, 172, 219)

using namespace std;

class milagrosLCD : public basicLCD {
public:
	milagrosLCD();
	~milagrosLCD();

	virtual bool lcdInitOk();
	virtual lcdError& lcdGetError();
	virtual bool lcdClear();
	virtual bool lcdClearToEOL();
	virtual basicLCD& operator<<(const unsigned char c);
	virtual basicLCD& operator<<(const char* c);
	virtual bool lcdMoveCursorUp();
	virtual bool lcdMoveCursorDown();
	virtual bool lcdMoveCursorRight();
	virtual bool lcdMoveCursorLeft();
	virtual bool lcdSetCursorPosition(const cursorPosition pos);
	virtual cursorPosition lcdGetCursorPosition();

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	lcdError LCDError;
	cursorPosition	position;
	bool initOK;
	string data;


	void init_display();
	void init_fonts();

	void clear_display();
	void write_display();

	int getCoords(int num);
};

#endif	//MILAGROS_LCD_H__