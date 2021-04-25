#include "milagrosLCD.h"

milagrosLCD::milagrosLCD() {
	position.column = HOME_C;
	position.row = HOME_R;
	initOK = true;
	//tengo que inicializar todo tipo el display, allegro etc
	if (!al_init() && initOK) { //Primera funcion a llamar antes de empezar a usar allegro.
		cout << "failed to initialize allegro!" << endl;
		initOK = false;
	}
	//No se si es necesario tener esto
	/*if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitives!\n");
		initOK = false;
	}*/

	//Inicializo las fuentes y letras.
	init_fonts();

	//Inicializo el display
	init_display();
}

milagrosLCD::~milagrosLCD() {
	al_destroy_display(display);
}

void milagrosLCD::init_display(){
	display = al_create_display(DISP_W, DISP_H); // Intenta crear display de 640x480 de fallar devuelve NULL
	if (!display && initOK) {
		cout << "failed to create display!" << endl;
		initOK = false;
	}

	clear_display();
}

void milagrosLCD::init_fonts() {
	if (!al_init_font_addon() && initOK) {
		cout << "failed to initialize font addon!" << endl;
		initOK = false;
	}
	if (!al_init_ttf_addon() && initOK) {
		cout << "failed to initialize ttf addon!" << endl;
	}
	if (!(font = al_load_font("04B_30__.TTF", 16, 0))) {	//el 16 es el size, lo puedo cambiar si me parece muy grande o muy chico.
		cout << "failed to initialize the font!\n" << endl;
		initOK = false;
	}
	
}

void milagrosLCD::clear_display() {
	al_clear_to_color(AMARILLO); //Hace clear del backbuffer del diplay al color amarillo

	al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla

	al_rest(1.5);
}

/*=====================================================
* Name: lcdInitOk
* Entra: -
* Resulta: No genera ning�n cambio en el display.
* Devuelve en su nombre �true� si el display se inicializ�
* correctamente (el constructor no tuvo errores) o �false
* en caso contrario.
*=====================================================*/
bool milagrosLCD::lcdInitOk() {
	return initOK;
}

/*=====================================================
* Name: lcdGetError
* Entra: -
* Resulta: No genera ning�n cambio en el display.
* Devuelve en su nombre un lcdError&
*=====================================================*/
lcdError& milagrosLCD::lcdGetError() {
	return LCDError;
}


/*=====================================================
* Name: lcdClear
* Entra: -
* Resulta: Borra el display y el cursor va a HOME
*
* Devuelve en su nombre �true� si fue satisfactoria �false�
* en caso contrario.
*=====================================================*/
bool milagrosLCD::lcdClear() {
	bool clearOK = true; //Vale true si todo bien y false en caso contrario.
	position.column = HOME_C;
	position.row = HOME_R;
	
	clear_display();

	return clearOK;
}


/*=====================================================
* Name: lcdClearToEOL
* Entra: -
* Resulta: Borra el display desde la posici�n actual
* del cursor hasta el final de la l�nea.
*
* Devuelve en su nombre �true� si fue satisfactoria �false�
* en caso contrario.
*=====================================================*/
bool milagrosLCD::lcdClearToEOL() {
	bool clearOK = true; //Vale true si todo bien y false en caso contrario.
	//Averiguar como borrar algunas letras.
	return clearOK;
}


/*=====================================================
* Name: operator<<()
* Entra: Un car�cter
* Resulta: Pone el car�cter en la posici�n actual
* del cursor del display y avanza el cursor a la pr�xima
* posici�n respetando el gap (si el car�cter no es imprimible
* lo ignora)
*
* Devuelve en su nombre una referencia a un basicLCD que permite
* encascar la funci�n:
* basicLCD lcd;
* lcd << �a� << �b� << �c�;
*=====================================================*/
basicLCD& milagrosLCD::operator<<(const unsigned char c) {
	//al_draw_textf(font, NEGRO, position.column, position.row, 0, c);
	if (position.column == 15) {
		position.column = 0;
		if (position.row == 1) {
			//no se q pasa
		}
		else {
			position.row = 1;
		}
	}
	else {
		++position.column;
	}
	return *this;
}

/*=====================================================
* Name: operator<<()
* Entra: Una cadena de caracteres NULL terminated
* Resulta: imprime la cadena de caracteres en la posici�n actual
* del cursor y avanza el cursor al final de la cadena respetando
* el gap (si alg�n car�cter no es imprimible lo ignora). Si recibe una
* cadena de m�s de 32 caracteres, muestra los �ltimos 32 en el display.
*
* Devuelve en su nombre una referencia a un basicLCD que permite
* encascar la funci�n:
* basicLCD lcd;
* lcd << �Hola� << � � << �Mundo�;
*=====================================================*/
basicLCD& milagrosLCD::operator<<(const char* c) {
	//Ver como hacer que si me llegan +32 caracteres se quede con los ultimos 32 nomas
	/*if (sizeof(c) > 32) {
		const char* new_c;
		for (int i = sizeof(c), int f = 32; i > 32, f > 0; i--, --f){
			new_c[f] = c[i];
		}
	}*/
	al_draw_textf(font, NEGRO, position.column, position.row, 0, c);
	al_flip_display();
	al_rest(6.0);

	//update de la posicion del cursor
	position.column += 4*16;
	return *this;
}

/*=====================================================
* Name: lcdMoveCursorUp
*
* Entra: -
* Resulta: Pasa el cursor a la primera l�nea del display sin
* alterar la columna en la que estaba.
*
* Devuelve en su nombre �true� si fue satisfactoria �false�
* en caso contrario.
*=====================================================*/
bool milagrosLCD::lcdMoveCursorUp() {
	bool moveOK = true; //Vale true si todo bien, false en lo contrario.
	switch (position.row) {
	case 0:
		break;
	case 1:
		position.row = 0;
		break;
	}
	return moveOK;
}

/*=====================================================
* Name: lcdMoveCursorDown
*
* Entra: -
* Resulta: Pasa el cursor a la segunda l�nea del display sin
* alterar la columna en la que estaba.
*
* Devuelve en su nombre �true� si fue satisfactoria �false�
* en caso contrario.
*=====================================================*/
bool milagrosLCD::lcdMoveCursorDown() {
	bool moveOK = true; //Vale true si todo bien y false en caso contrario.
	switch (position.row) {
	case 0:
		position.row = 1;
		break;
	case 1:
		break;
	}
	return moveOK;
}

/*=====================================================
* Name: lcdMoveCursorRight
*
* Entra: -
* Resulta: Avanza el cursor una posici�n
*
* Devuelve en su nombre �true� si fue satisfactoria �false�
* en caso contrario.
*=====================================================*/
bool milagrosLCD::lcdMoveCursorRight() {
	bool moveOK = true; //Vale true si todo bien y false en caso contrario.
	switch (position.column) {
	case 15:
		break;
	default:
		++position.column;
		break;
	}
	return moveOK;
}

/*=====================================================
* Name: lcdMoveCursorLeft
*
* Entra: -
* Resulta: Retrocede el cursor una posici�n
*
* Devuelve en su nombre �true� si fue satisfactoria �false�
* en caso contrario.
*=====================================================*/
bool milagrosLCD::lcdMoveCursorLeft() {
	bool moveOK = true; //Vale true si todo bien y false en caso contrario.
	switch (position.column) {
	case 0:
		break;
	default:
		--position.column;
		break;
	}

	return moveOK;
}

/*=====================================================
* Name: lcdSetCursorPosition
* Entra: Recibe una estructura tipo cursorPosition
* Resulta: Posiciona el cursor en la posici�n dada
* por row y column. row[0-1] col[0-19]. Ante un valor inv�lido
* de row y/o column ignora la instrucci�n (no hace nada).
*
* Devuelve en su nombre �true� si fue satisfactoria �false�
* en caso contrario.
*=====================================================*/
bool milagrosLCD::lcdSetCursorPosition(const cursorPosition pos) {
	bool setOK = true; //Vale true si todo bien y false en caso contrario.
	//Me fijo que los valores que me piden son correctos.
	if (pos.column >= 2 || pos.column < 0 || pos.row >= 16 || pos.row <= 0) {
		setOK = false;
		cout << "Invalid cursor position!" << endl;
	}
	this->position.column = pos.column;
	this->position.row = pos.row;
	return setOK;
}

/*=====================================================
* Name: lcdGetCursorPosition
* Entra: -
* Resulta: Devuelve la posici�n actual del cursor.
*
*
* Devuelve una estructura tipo cursorPosition
*=====================================================*/
cursorPosition milagrosLCD::lcdGetCursorPosition() {
	return position;
}