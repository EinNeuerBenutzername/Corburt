#ifndef CBFIO_BASE_INCLUDED
#define CBFIO_BASE_INCLUDED
#include <limits.h>
#if CHAR_BIT!=8
    #error Macro CHAR_BIT is not 8.
#endif
#include <stdio.h>
#include <inttypes.h>

static int fio_isle();
static int fio_isle(){
    int i=1;
    return (int)(*(char *)&i);
}

struct fio{
    size_t filesize;
    size_t fileptr;
    int_fast8_t int_fast32_t_size;
    int_fast8_t int_fast64_t_size;
    int_fast8_t wchar_t_size;
    int_fast8_t fail;
} fio={0,0,4,8,2,0};

void fio_getfilesize(char *filename);
void fio_fail(const char *errmsg);
void fio_getfilesize(char *filename){
    FILE *fp=fopen(filename,"rb");
    fio.filesize=0;
    fio.fileptr=0;
    fio.fail=0;
    if(fp==NULL){
        fio.fail=1;
        return;
    }
    fseek(fp,0,SEEK_END);
    fio.filesize=ftell(fp);
    fclose(fp);
}
void fio_fail(const char *errmsg){
    if(!fio.fail){
        fio.fail=1;
        printf("FIO Fail: failure at position %" PRIdFAST32 ": %s\n",fio.fileptr,errmsg);
        FILE *errorlog=fopen("err.log","a");
        fprintf(errorlog,"FIO Fail: failure at position %" PRIdFAST32 ": %s\n",fio.fileptr,errmsg);
        fclose(errorlog);
    }
}

static int_fast32_t int_fast32_t_makele (int_fast32_t n);
static int_fast32_t int_fast32_t_makebe (int_fast32_t n);
void                int_fast32_t_read   (int_fast32_t *n,FILE *fp);
void                int_fast32_t_write  (int_fast32_t n,FILE *fp);
static int_fast32_t int_fast64_t_makele (int_fast64_t b);
static int_fast32_t int_fast64_t_makebe (int_fast64_t b);
void                int_fast64_t_read   (int_fast64_t *b,FILE *fp);
void                int_fast64_t_write  (int_fast64_t b,FILE *fp);

static int_fast32_t int_fast32_t_makele (int_fast32_t n){
    unsigned char c[sizeof(int_fast32_t)];
    if(fio_isle())return n;
    int_fast32_t result;
    for(size_t i=0;i<sizeof(int_fast32_t);i++){
        c[i]=(n>>CHAR_BIT*i)&UCHAR_MAX;
        result+=(int_fast32_t)c[i]<<((sizeof(int_fast32_t)-i-1)*CHAR_BIT);
    }
    return result;
}
static int_fast32_t int_fast32_t_makebe (int_fast32_t n){
    unsigned char c[sizeof(int_fast32_t)];
    if(fio_isle())return n;
    int_fast32_t result;
    for(size_t i=0;i<sizeof(int_fast32_t);i++){
        c[i]=(n>>CHAR_BIT*i)&UCHAR_MAX;
        result+=(int_fast32_t)c[i]<<((sizeof(int_fast32_t)-i-1)*CHAR_BIT);
    }
    return result;
}
void                int_fast32_t_read   (int_fast32_t *n,FILE *fp){
    *n=0;
    if(fio.fail)return;
    if(fio.fileptr+fio.int_fast32_t_size>fio.filesize){
        fio_fail("exceeded file length.");
        return;
    }
    int_fast32_t r;
    if(fread(&r,fio.int_fast32_t_size,1,fp)!=1){
        fio_fail("fread() fail.");
        return;
    }
    fio.fileptr+=fio.int_fast32_t_size;
    if(!fio_isle())r=int_fast32_t_makebe(r);
    *n=r;
}
void                int_fast32_t_write  (int_fast32_t n,FILE *fp){
    n=int_fast32_t_makele(n);
    fwrite(&n,fio.int_fast32_t_size,1,fp);
}
static int_fast32_t int_fast64_t_makele (int_fast64_t b){
    unsigned char c[sizeof(int_fast64_t)];
    if(fio_isle())return b;
    int_fast64_t result;
    for(size_t i=0;i<sizeof(int_fast64_t);i++){
        c[i]=(b>>CHAR_BIT*i)&UCHAR_MAX;
        result+=(int_fast64_t)c[i]<<((sizeof(int_fast64_t)-i-1)*CHAR_BIT);
    }
    return result;
}
static int_fast32_t int_fast64_t_makebe (int_fast64_t b){
    unsigned char c[sizeof(int_fast64_t)];
    if(fio_isle())return b;
    int_fast64_t result;
    for(size_t i=0;i<sizeof(int_fast64_t);i++){
        c[i]=(b>>CHAR_BIT*i)&UCHAR_MAX;
        result+=(int_fast64_t)c[i]<<((sizeof(int_fast64_t)-i-1)*CHAR_BIT);
    }
    return result;
}
void                int_fast64_t_read   (int_fast64_t *b,FILE *fp){
    *b=0;
    if(fio.fail)return;
    if(fio.fileptr+fio.int_fast64_t_size>fio.filesize){
        fio_fail("exceeded file length.");
        return;
    }
    int_fast64_t r;
    if(fread(&r,fio.int_fast64_t_size,1,fp)!=1){
        fio_fail("fread() fail.");
        return;
    }
    fio.fileptr+=fio.int_fast64_t_size;
    if(!fio_isle())r=int_fast64_t_makebe(r);
    *b=r;
}
void                int_fast64_t_write  (int_fast64_t b,FILE *fp){
    b=int_fast64_t_makele(b);
    fwrite(&b,fio.int_fast64_t_size,1,fp);
}

static void         wcs_makele          (wchar_t *wcs);
static void         wcs_makebe          (wchar_t *wcs);
void                wcs_read            (wchar_t *wcs,size_t len,FILE *fp);
void                wcs_write           (wchar_t *wcs,size_t len,FILE *fp);

static void         wcs_makele          (wchar_t *wcs){
    if(fio_isle())return;
    for(size_t i=0;i<wcslen(wcs);i++){
        unsigned char c[sizeof(wchar_t)];
        wchar_t result;
        for(size_t j=0;j<sizeof(wchar_t);j++){
            c[j]=(wcs[i]>>(CHAR_BIT*i))&UCHAR_MAX;
            result+=(wchar_t)c[i]<<((sizeof(wchar_t)-i-1)*CHAR_BIT);
        }
        wcs[i]=result;
    }
}
static void         wcs_makebe          (wchar_t *wcs){
    if(fio_isle())return;
    for(size_t i=0;i<wcslen(wcs);i++){
        unsigned char c[sizeof(wchar_t)];
        wchar_t result;
        for(size_t j=0;j<sizeof(wchar_t);j++){
            c[j]=(wcs[i]>>(CHAR_BIT*i))&UCHAR_MAX;
            result+=(wchar_t)c[i]<<((sizeof(wchar_t)-i-1)*CHAR_BIT);
        }
        wcs[i]=result;
    }
}
void                wcs_read            (wchar_t *wcs,size_t len,FILE *fp){
    if(fio.fail)return;
    if(fio.fileptr+fio.wchar_t_size*len>fio.filesize){
        fio_fail("exceeded file length.");
        return;
    }
    for(size_t i=0;i<len;i++){
        uint_fast32_t tmpint=0;
        if(fread(&tmpint,fio.wchar_t_size,1,fp)!=1){
            fio_fail("fread() fail.");
            return;
        }
        wcs[i]=tmpint;
        fio.fileptr+=fio.wchar_t_size;
    }
    if(!fio_isle())wcs_makebe(wcs);
}
void                wcs_write           (wchar_t *wcs,size_t len,FILE *fp){
    wcs_makele(wcs);
//    fwrite(wcs,len*sizeof(wchar_t),1,fp);
    for(size_t i=0;i<len;i++){
        int_fast32_t mask=(UCHAR_MAX+1)*(UCHAR_MAX+1)-1;
        int_fast16_t tmpint16=wcs[i]%mask;
        fwrite(&tmpint16,fio.wchar_t_size,1,fp);
    }
    wcs_makebe(wcs);
}

#endif
