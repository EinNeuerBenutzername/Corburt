#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "include/cbcurses.h"
#include "include/cbbase.h"
#include "include/msg.h"
FILE *fp;
void exitfunc(){
    if(fp!=NULL){
        fclose(fp);
    }
    remove("data.dmp");
}
int main(){
    cbc_setwindowtitle("cbinput");
    remove("data.dmp");
    atexit(exitfunc);
    long matchid=0;
    fp=fopen("data.dmp","w");
    wchar_t input[1024];
    wchar_t inputlast[1024];
    cbc_setcolor(Cyan|Bright);
    printc(Cyan|Bright,msg->global_input);
    cbc_setcolor(Default);
    while(1){
        matchid++;
        matchid=matchid%10000000;
        printf(">>");
        cbc_setcolor(Yellow);
        fflush(stdout);
        wmemset(input,0,1024);
        fgetws(input,1024,stdin);
        fflush(stdin);
        if(input[wcslen(input)-1]==L'\n'){
            input[wcslen(input)-1]=0;
        }
        cbc_setcolor(Default);
        if(!wcslen(input)){
            fprintf(fp,"%d.%d.%ls",matchid,wcslen(inputlast),inputlast);
        }else{
            fclose(fp);
            fp=fopen("data.dmp","w");
            fprintf(fp,"%d.%d.%ls",matchid,wcslen(input),input);
            wmemset(inputlast,0,1024);
            wcscpy(inputlast,input);
        }
        rewind(fp);
        fflush(fp);
        if(wcsncmp(input,L"quit",4)==0){
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

