#define Corburt_Debug
#define Corburt_Explicit_Pointer_Trace
#include <stdio.h>
#include <locale.h>
#include "include/cbbase.h"
#include "include/cbplayer.h"
#include "include/cbio.h"
int main(){
    checkendianess();
    buffer=mallocpointer(1024*sizeof(wchar_t));
    wmemset(buffer,0,1024);
    initrng();
    //setlocale(LC_ALL,"");
    setlocale(LC_ALL,"en_GB");
    printc(Green|Bright,msg_global_welcome);
    printc(Default,msg_global_splash);
    printc(Yellow,msg_global_splash2);
    printc(Default,L"        %40ls\n\n",msg_global_corburtversion);
    readsaves();
    wchar_t *input_line;
    input_line=mallocpointer(1024*sizeof(wchar_t));
    wmemset(input_line,0,1024);
    while(1){
        scanline(input_line,1024);
        wcslower(&input_line);
        if(wcscmp(input_line,L"quit")==0){
            break;
        }else if(wcscmp(input_line,L"stats")==0||wcscmp(input_line,L"st")==0){
            showstatus();
        }
    }
    freepointer(buffer);
    freepointer(input_line);
    savesaves();
    //getwc(stdin);
    return 0;
}
