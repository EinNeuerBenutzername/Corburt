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
i32 __CBFIO_RecvCBInput(char *line, i32 scans);

i32 __CBFIO_ReadI32(FILE *fp, i32 *data);
i32 __CBFIO_ReadI64(FILE *fp, i64 *data);
i32 __CBFIO_ReadU32(FILE *fp, u32 *data);
i32 __CBFIO_ReadU64(FILE *fp, u64 *data);
i32 __CBFIO_ReadStr(FILE *fp, char *data);
void __CBFIO_WriteI32(FILE *fp, i32 data);
void __CBFIO_WriteI64(FILE *fp, i64 data);
void __CBFIO_WriteU32(FILE *fp, u32 data);
void __CBFIO_WriteU64(FILE *fp, u64 data);
void __CBFIO_WriteStr(FILE *fp, char *data);

struct {
    struct {
        FILE *fp;
        i32 line_id;
    } cbinput; // recvCBInput
    i32 endian_diff;
    const char *cb_path;
    char *working_dir;
    size_t working_dir_len;
} __CBFIO_data = {
    .cbinput={NULL, 0},
    .endian_diff=ENDIAN_UNKNOWN
};

const struct {
    void (*cd)(const char *path);
    FILE *(*openRelative)(const char *relative_path, const char *restrict_mode);
    i32 (*recvCBInput)(char *line, i32 scans);
//    i32 (*readI32)(FILE *fp, i32 *data);
//    i32 (*readI64)(FILE *fp, i64 *data);
//    i32 (*readU32)(FILE *fp, u32 *data);
//    i32 (*readU64)(FILE *fp, u64 *data);
//    i32 (*readStr)(FILE *fp, char *data);
//    void (*writeI32)(FILE *fp, i32 data);
//    void (*writeI64)(FILE *fp, i64 data);
//    void (*writeU32)(FILE *fp, u32 data);
//    void (*writeU64)(FILE *fp, u64 data);
//    void (*writeStr)(FILE *fp, char *data);
} FIO = {
    .cd=__CBFIO_CD,
    .openRelative=__CBFIO_FOpenRelative,
    .recvCBInput=__CBFIO_RecvCBInput,
//    .readI32=__CBFIO_ReadI32,
//    .readI64=__CBFIO_ReadI64,
//    .readU32=__CBFIO_ReadU32,
//    .readU64=__CBFIO_ReadU64,
//    .readStr=__CBFIO_ReadStr,
//    .writeI32=__CBFIO_WriteI32,
//    .writeI64=__CBFIO_WriteI64,
//    .writeU32=__CBFIO_WriteU32,
//    .writeU64=__CBFIO_WriteU64,
//    .writeStr=__CBFIO_WriteStr,
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
    char *dir=Mem.calloc((path_len+1), sizeof(char));
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
    char *tmppath=Mem.calloc(rpath_len+__CBFIO_data.working_dir_len, sizeof(char));
    memset(tmppath, 0, rpath_len+__CBFIO_data.working_dir_len);
    strcpy(tmppath, __CBFIO_data.working_dir);
    strcat(tmppath, relative_path);
    FILE *fp=fopen(tmppath, restrict_mode);
    Mem.free(tmppath);
    return fp;
}
i32 __CBFIO_RecvCBInput(char *line, i32 scans){
    memset(line, 0, scans);
    FILE *fp=__CBFIO_data.cbinput.fp;
    if(!fp){
        fp=fopen("_cbfiodata.dmp", "r");
        if(!fp){
            return 0;
        }
        __CBFIO_data.cbinput.fp=fp;
    }
    i32 id, len;
    if(fscanf(fp, "%" SPECi32 ".%" SPECi32 ".", &id, &len)!=2){
        return 0;
    }
    if(id==__CBFIO_data.cbinput.line_id){
        rewind(fp);
        fflush(fp);
        return 0;
    }else{
        __CBFIO_data.cbinput.line_id=id;
        if(len>=scans){
            len=scans-2;
        }
        fgets(line, len+1, fp);
        rewind(fp);
        fflush(fp);
    }
    return 1;
}

//===========================================
//  Read & Write
//===========================================

//i32 __CBFIO_ReadI32(FILE *fp, i32 *data){return 1;}
//i32 __CBFIO_ReadI64(FILE *fp, i64 *data){return 1;}
//i32 __CBFIO_ReadU32(FILE *fp, u32 *data){return 1;}
//i32 __CBFIO_ReadU64(FILE *fp, u64 *data){return 1;}
//i32 __CBFIO_ReadStr(FILE *fp, char *data){return 1;}
//void __CBFIO_WriteI32(FILE *fp, i32 data){fprintf(fp, , data)}
//void __CBFIO_WriteI64(FILE *fp, i64 data){}
//void __CBFIO_WriteU32(FILE *fp, u32 data){}
//void __CBFIO_WriteU64(FILE *fp, u64 data){}
//void __CBFIO_WriteStr(FILE *fp, char *data){}

#endif
