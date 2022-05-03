#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "include/cbcurses.h"
#include "include/cbbase.h"
#include "include/msg.h"
FILE *fp;
void exitfunc();
int main(){
    cbc_init();
    cbc_setwindowtitle("cbinput");
    cbc_setcolor(Default);
    cbc_clearscreen();
    remove("data.dmp");
    atexit(exitfunc);
    int matchid=0;
    fp=fopen("data.dmp","w");
    wchar_t inputcur[1024];
    wchar_t inputlast[1024];
    cbc_setcolor(Cyan|Bright);
    printc(Cyan|Bright,msg->global_input);
    cbc_setcolor(Default);
    while(1){
        matchid++;
        matchid=matchid%10000;
        printf(">>");
        cbc_setcolor(Yellow);
        fflush(stdout);
        wmemset(inputcur,0,1024);
        fgetws(inputcur,1024,stdin);
        fflush(stdin);
        if(inputcur[wcslen(inputcur)-1]==L'\n'){
            inputcur[wcslen(inputcur)-1]=0;
        }
        cbc_setcolor(Default);
        if(!wcslen(inputcur)){
            fprintf(fp,"%d.%d.%ls",matchid,wcslen(inputlast),inputlast);
        }else{
            fclose(fp);
            fp=fopen("data.dmp","w");
            fprintf(fp,"%d.%d.%ls",matchid,wcslen(inputcur),inputcur);
            wmemset(inputlast,0,1024);
            wcscpy(inputlast,inputcur);
        }
        rewind(fp);
        fflush(fp);
        if(wcsncmp(inputcur,L"quit",4)==0){
            fflush(fp);
            fclose(fp);
            fp=NULL;
            return 0;
        }
    }
    fclose(fp);
    fp=NULL;
    return 0;
}
void exitfunc(){
    if(fp!=NULL){
        fclose(fp);
    }
    remove("data.dmp");
}
