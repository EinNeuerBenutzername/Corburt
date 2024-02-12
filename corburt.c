#define __CB_DEBUG
#include "include/corburt.h"

void initCorburt(void);

int main(int argc, const char *argv[]){
    FIO.cd(argc?argv[0]:"");
    initCorburt();

//    IO.printf("Lorem    ipsum         dorem  is a latin (?) phrase widely used in font displays.");

    while(1){
        // Loop
        Utils.showFPS();
        Time.wait(30);
        Time.endLoop();
    }
    Mem.freeAll();
    return 0;
}

void initCorburt(void){
    Curses.init();
    Curses.setTitle("Corburt");
    Utils.setupRand();
    IO.init();
    Curses.hideCursor();
}
