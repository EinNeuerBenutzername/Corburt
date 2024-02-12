#include <stdio.h>
#include <stdlib.h>
#include "include/cbio.h"
#include "include/cbcurses.h"

FILE *fp=NULL;
void exitfunc(void);

int main(void){
    remove("_cbfiodata.dmp");
    fp=fopen("_cbfiodata.dmp","r");
    if(fp!=NULL){
        return -1;
    }
    fclose(fp);
    fp=fopen("_cbfiodata.dmp","w");
    atexit(exitfunc);

    Curses.init();
    Curses.setTitle("cbinput");
    Curses.hideCursor();

    char inputcur[1024];
    char inputlast[1024];
    i32 matchid=0;

    while(1){
        matchid++;
        matchid=matchid%10000;
        printf(">>");
        Curses.setColor(Yellow);
        memset(inputcur,0,1024);
        fgets(inputcur,1024,stdin);
        fflush(stdin);
        while(inputcur[strlen(inputcur)-1]=='\n' || inputcur[strlen(inputcur)-1]=='\r'){
            inputcur[strlen(inputcur)-1]=0;
        }
        Curses.setColor(Default);
        if(!strlen(inputcur)){
            i32 slen=strlen(inputlast);
            fprintf(fp,"%" SPECi32 ".%" SPECi32 ".%s",matchid,slen,inputlast);
        }else{
            fclose(fp);
            fp=fopen("_cbfiodata.dmp","w");
            i32 slen=strlen(inputcur);
            fprintf(fp,"%" SPECi32 ".%" SPECi32 ".%s",matchid,slen,inputcur);
            memset(inputlast,0,1024);
            strcpy(inputlast,inputcur);
        }
        rewind(fp);
        fflush(fp);
        if(strncmp(inputcur,"quit",4)==0){
            fflush(fp);
            fclose(fp);
            fp=NULL;
            return 0;
        }
    }

    fclose(fp);

    return 0;
}

void exitfunc(void){
    if(fp!=NULL){
        fclose(fp);
    }
    remove("cbfiodata.dmp");
}
