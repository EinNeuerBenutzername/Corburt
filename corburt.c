#define __CB_DEBUG
#include "include/corburt.h"

void exitFunc(void);
void initCorburt(void);

int main(int argc, const char *argv[]){
    FIO.cd(argc?argv[0]:"");
    initCorburt();

    IO.printf("{$+}Welcome to Corburt.\n");
    IO.printf( "{$CBlogoU}   @@@@                @@                      \n"
                         "  @@  @@               @@                  @@  \n"
                         "  ##      ####  # ###  ####  ##  ## # ###  ####\n"
                         "  ##     ##  ## ##  ## ## ## ##  ## ##  ## ##  \n"
               "{$CBlogoL}  $$  $$ $$  $$ $$     $$ $$ $$  $$ $$     $$  \n"
                         "   $$$$   $$$$  $$     $$$    $$$$  $$      $$${$d}\n\n");
    IO.printf("%47s\n\n", "v0.4.1");

    char *line=Mem.calloc(1024, sizeof(char));

    while(1){
        // Loop
        if(FIO.recvCBInput(line, 1024)){
            IO.printf("{$NHint}Player says: {$d}");
            IO.setColorMode(0);
            IO.printf("%s\n", line);
            IO.setColorMode(1);
        }
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
    atexit(exitFunc);
    Utils.setupRand();
    IO.init();
    Curses.hideCursor();

}

void exitFunc(void){
    fclose(__CBFIO_data.cbinput.fp);
    remove("_cbfiodata.dmp");
}
