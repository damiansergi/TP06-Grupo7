#ifndef salvaLCD_H

#define salvaLCD_H

#include "basicLCD.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define W 256*2
#define H 64*2

class salvaLCD : public basicLCD {
	public: 
		salvaLCD(); 
		~salvaLCD();

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
		lcdError LcdError;
		cursorPosition	Cursor;
		string information_r1; 
		string information_r2;
		bool Error; 

};



#endif // salvaLCD_H







