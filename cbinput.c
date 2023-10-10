#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    remove("cbfiodata.dmp");
    fp=fopen("cbfiodata.dmp","r");
    if(fp!=NULL){
        return 1;
    }
    fclose(fp);
    atexit(exitfunc);
    int matchid=0;
    fp=fopen("cbfiodata.dmp","w");
    char inputcur[1024];
    char inputlast[1024];
    cbc_setcolor(Cyan|Bright);
    printc(Cyan|Bright,msg->global_input);
    cbc_setcolor(Default);
    while(1){
        matchid++;
        matchid=matchid%10000;
        printf(">>");
        cbc_setcolor(Yellow);
        fflush(stdout);
        memset(inputcur,0,1024);
        fgets(inputcur,1024,stdin);
        fflush(stdin);
        if(inputcur[strlen(inputcur)-1]==L'\n'){
            inputcur[strlen(inputcur)-1]=0;
        }
        cbc_setcolor(Default);
        if(!strlen(inputcur)){
            int slen=strlen(inputlast);
            fprintf(fp,"%d.%d.%s",matchid,slen,inputlast);
        }else{
            fclose(fp);
            fp=fopen("cbfiodata.dmp","w");
            int slen=strlen(inputcur);
            fprintf(fp,"%d.%d.%s",matchid,slen,inputcur);
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
    fp=NULL;
    return 0;
}
void exitfunc(){
    if(fp!=NULL){
        fclose(fp);
    }
    remove("cbfiodata.dmp");
}
