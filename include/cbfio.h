#ifndef __CBFIO
#define __CBFIO

// BOTTOM LAYER

#include <stdio.h>
#include <string.h>

// On default, we assume that we play on little-endian platforms.

// enum enum_endianness {ENDIAN_BIG, ENDIAN_LITTLE};
enum enum_endianness {
    ENDIAN_SAME=0,
    ENDIAN_BYTE=1,
    ENDIAN_BIT=2,
    ENDIAN_UNKNOWN=4
};

i32 __CBFIO_GetCurrentEndianness(void); // Usable, but discarded
void __CBFIO_EndiannessDiff(void);

void __CBFIO_CD(const char *path);
FILE *__CBFIO_FOpenRelative(const char *relative_path, const char *restrict_mode);

struct {
    i32 endian_diff;
    const char *cb_path;
    char *working_dir;
    size_t working_dir_len;
} __CBFIO_data = {
    .endian_diff=ENDIAN_UNKNOWN
};

const struct {
    void (*cd)(const char *path);
    FILE *(*openRelative)(const char *relative_path, const char *restrict_mode);
} FIO = {
    .cd=__CBFIO_CD,
    .openRelative=__CBFIO_FOpenRelative
};

i32 __CBFIO_GetCurrentEndianness(void){ // obsolete
    unsigned char buffer[4];
    buffer[0]=0x00;
    buffer[0]=0x01;
    buffer[0]=0x02;
    buffer[0]=0x03;
    switch((*(u32*)buffer)){
    case 0x00010203UL: return 0; // ENDIAN_BIG;
    case 0x03020100UL: return 1; // ENDIAN_LITTLE;
    case 0x02030001UL: break; // ENDIAN_BIG_WORD
    case 0x01000302UL: break; // ENDIAN_LITTLE_WORD
    default: break; // UNKNOWN
    }
    return -1; // Not gonna deal with it anyway
}
void __CBFIO_EndiannessDiff(void){
    // We read a 32-bit integer 0x00010203 from file.
    u32 indicator;
    FILE *fp=fopen("", "r");
    if(!fp){
        __CBFIO_data.endian_diff=ENDIAN_SAME;
        return;
    }
    fscanf(fp, "%" SPECu32, &indicator);
    switch(indicator){
    case 0x00010203UL: __CBFIO_data.endian_diff=ENDIAN_SAME; break;
    case 0x03020100UL: __CBFIO_data.endian_diff=ENDIAN_BYTE; break;
    case 0x008040C0UL: __CBFIO_data.endian_diff=ENDIAN_BIT; break;
    case 0xC0408000UL: __CBFIO_data.endian_diff=ENDIAN_BYTE|ENDIAN_BIT; break;
    }
}

void __CBFIO_CD(const char *path){
    __CBFIO_data.cb_path=path;
    size_t path_len=strlen(path);
    char *dir=Mem.malloc((path_len+1)*sizeof(char));
    memset(dir, 0, path_len+1);
    strcpy(dir, path);
    while(path_len>0){
        path_len--;
        if(dir[path_len]=='\\' || dir[path_len]=='/'){
            break;
        }else{
            dir[path_len]=0;
        }
    }
    __CBFIO_data.working_dir=dir;
    __CBFIO_data.working_dir_len=path_len;
}
FILE *__CBFIO_FOpenRelative(const char *relative_path, const char *restrict_mode){
    size_t rpath_len=strlen(relative_path);
    char *tmppath=Mem.malloc(rpath_len+__CBFIO_data.working_dir_len);
    memset(tmppath, 0, rpath_len+__CBFIO_data.working_dir_len);
    strcpy(tmppath, __CBFIO_data.working_dir);
    strcat(tmppath, relative_path);
    FILE *fp=fopen(tmppath, restrict_mode);
    Mem.free(tmppath);
    return fp;
}



#endif
