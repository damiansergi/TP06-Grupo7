#include "salvaLCD.h"

//Funion auxiliar para inicializar allegro
bool must_init(bool test, const char* description)
{
    if (test)
        return true;
    else
    {
        printf("couldn't initialize %s\n", description);
        return false;
    }
}

salvaLCD::salvaLCD() {
    Error = true; 
    Cursor.column = 0;
    Cursor.row = 0; 

    if (!(must_init(al_init(), "allegro")))
        Error = false; 

    if (!(must_init(al_install_keyboard(), "keyboard")))
        Error = false;

    if (!(must_init(al_init_primitives_addon(), "primitives")))
        Error = false; 

    display = al_create_display(W, H);
    if (!(must_init(display, "display")))
        Error = false;

    font = al_create_builtin_font();
    if (!(must_init(font, "font")))
        Error = false;

    cout << "Constructor true" << endl; 
}

salvaLCD:: ~salvaLCD() {
    al_destroy_display(display);//Destruimos lo creado 
    al_destroy_font(font);
}

bool salvaLCD::lcdInitOk() {
    return Error; //El constructor ya se encargo de ver si hubo error
}

lcdError& salvaLCD::lcdGetError() {
    return (this->LcdError);//Devolvemos el LcdError
}

bool salvaLCD::lcdClear() {

    information_r1.replace(0, 16, "                "); //Limpiamos el string de info
    information_r2.replace(0,16, "                ");

    al_clear_to_color(al_map_rgb_f(0, 1, 0));//Verde
    al_flip_display(); 
  
    //al_rest(1.0);

    //Cursor a HOME - HOME es el primer elemento de la pantalla
    Cursor.column = 0;
    Cursor.row = 0;

    return true; 

}


bool salvaLCD:: lcdClearToEOL() {


    if (Cursor.row == 0)
    {
        al_draw_filled_rectangle(0, 0, W, H / 2, al_map_rgb_f(0, 1, 0));//Limpiamos la fila
        information_r1.replace(Cursor.column, 16-Cursor.column, "                ");//Sacamos lo que esta despues del cursor

        al_draw_text(font, al_map_rgb(255, 255, 255), W / 4, H / 4, 0, information_r1.c_str());//Escribimos lo que tenemos
    }
    else if (Cursor.row == 1) {//Lo mismo para la segunda fila

        al_draw_filled_rectangle(0, H / 2, W, H, al_map_rgb_f(0, 1, 0));
        information_r2.replace(Cursor.column, 16 - Cursor.column, "                ");

        al_draw_text(font, al_map_rgb(255, 255, 255), W /4, H * (0.75) , 0, information_r2.c_str());
    }
    else
        return false; 

    al_flip_display(); //Imprimimos todo lo escrito

    return true; 
}

basicLCD& salvaLCD::operator<<(const unsigned char c) {

    if (isprint(c)) {
        if (Cursor.row == 0)
            information_r1.replace(Cursor.column, 1, 1, c);//TODO
        else if (Cursor.row == 1)
            information_r2.replace(Cursor.column, 1, 1, c);

        lcdMoveCursorRight();

        //Imprimiemos la pantalla de nuevo
        al_clear_to_color( al_map_rgb_f(0, 1, 0));//Limpiamos todo

        al_draw_text(font, al_map_rgb(255, 255, 255), W / 4, H / 4, 0, information_r1.c_str());     //Imprimimos primera fila
        al_draw_text(font, al_map_rgb(255, 255, 255), W / 4, H * (0.75), 0, information_r2.c_str());//Imprimirmos segunda fila

        al_flip_display();//Imprimimos todo lo escrito
    }

    return *this;
}


basicLCD& salvaLCD::operator<<(const char* c) {

    string aux = string(c);
    
    //Ver bien el tema de los nuemros de columna
    if (Cursor.row == 0)//Si estamos en la primera fila
    {
        if (aux.length() > (16 - Cursor.column) )//Y el string se va de linea, osea mueve al cursor mas alla de 16
        {
            information_r1.replace(Cursor.column, 15, aux.substr(0, (16 - Cursor.column)));//Escribo lo que puedo en la linea 1

            if ((aux.length() - (16 - Cursor.column)) < 16)//Si lo que me queda por escribir es mas chico que 16, lo escribo
            {
                information_r2.replace(0, (aux.length() - (16 - Cursor.column + 1 )), aux.substr((16 - Cursor.column), aux.length()));

                for (int i = 0; i < aux.length(); i++) {
                    lcdMoveCursorRight();
                }
            }
            else//Si el arreglo no entra en toda la linea dos lo corto 
            {
                information_r2.replace(0, 15, aux.substr(16, 16));
                Cursor.column = 15;
            }  
        }
        else
        {
            information_r1.replace(Cursor.column, 15, aux);
            for (int i = 0; i < aux.length(); i++) {
                lcdMoveCursorRight();
            }
        }

    }
    else if (Cursor.row == 1)
    {
        information_r2.replace(Cursor.column, 15, aux);
        for (int i = 0; i < aux.length(); i++) {
            lcdMoveCursorRight();
        }
        if (Cursor.column > 15)
        {
            Cursor.column = 15;
        }
    }

    //Imprimiemos la pantalla de nuevo
    al_clear_to_color(al_map_rgb_f(0, 1, 0));//Limpiamos todo

    al_draw_text(font, al_map_rgb(255, 255, 255), W / 4, H / 4, 0, information_r1.c_str());     //Imprimimos primera fila
    al_draw_text(font, al_map_rgb(255, 255, 255), W / 4, H * (0.75), 0, information_r2.c_str());//Imprimirmos segunda fila

    al_flip_display();//Imprimimos todo lo escrito

    return *this; 
    
}

//MOVIMIENTO DEL CURSOR

bool salvaLCD::lcdMoveCursorUp() {
    if (Cursor.row == 0) {
        return true;
    }
    else if (Cursor.row == 1) {
        Cursor.row = 0; 
        return true;
    }
    return false; //Column.row esta fuera de margen
}

bool salvaLCD:: lcdMoveCursorDown(){
    if (Cursor.row == 1) {
        return true;
    }
    else if (Cursor.row == 0) {
        Cursor.row = 1;
        return true;
    }
    return false; //Column.row esta fuera de margen
}

bool salvaLCD:: lcdMoveCursorRight() {
    if (Cursor.column == 15) {   //Si estamos en el ultimo elemento de una fila
        if (Cursor.row == 1)     //Y es la segunda fila
            return true;         // Nos quedamos donde estamos
        else if (Cursor.row == 0)//Si es la fila es la primera
        {
            Cursor.row = 1;      //Nos ponemos en el primer elemento de la segunda
            Cursor.column = 0;
            return true;
        }
        return false; //Si no paso nada de lo anterior debe haber un error
    }
    else if ((Cursor.column < 15) && (Cursor.column > 0)) {// Si no estamos en el ultimo elemento y es mayor a 0(por si acaso hay un error)
        Cursor.column++;//Pasamos al siguiente elemento
        return true;
    }
    return false; //Column.row esta fuera de margen
}

bool salvaLCD:: lcdMoveCursorLeft() {
    if (Cursor.column == 0) {   //Si estamos en el primer elemento de una fila
        if (Cursor.row == 0)     //Y es la primera fila
            return true;         // Nos quedamos donde estamos
        else if (Cursor.row == 1)//Si es la fila es la segunda
        {
            Cursor.row = 0;      //Nos ponemos en el ultimo elemento de la primera
            Cursor.column = 15;
            return true;
        }
        return false; //Si no paso nada de lo anterior debe haber un error
    }
    else if (Cursor.column > 0) {// Si no estamos en el primer elemento
        Cursor.column--;//Pasamos al elemento anetrior
        return true;
    }
    return false; //Column.row esta fuera de margen
}

bool salvaLCD::lcdSetCursorPosition(const cursorPosition pos) {
    
    if( (pos.row == 0) || (pos.row ==1))
        Cursor.row = pos.row;
    if((pos.column > 0) && (pos.column < 16))//Porque la consigna dice 19
        Cursor.column = pos.column; 

    return true; 
}

cursorPosition salvaLCD:: lcdGetCursorPosition() {
    return Cursor; 
}











