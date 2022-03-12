/*Corburt Curses
  This is a C99 curses library with no external dependencies (hopefully).
    Some of the code are from github.
    It provides following functions:
        window manipulation (weak)
            setwindowtitle(title), getwindowsize(*rows,*cols)
        cursor manipulation
            hidecursor(), showcursor(), setcursor(row,col), getcursor(*row,*col)
        i/o manipulation
            setcolor(color), getch(), clearscreen()
        buffer manipulation
            rawmode(), cookedmode(), setbufferalternate()
  Platform support: Windows (tested) and *nixes (POSIX, not tested)*/
#ifndef Corburt_Curses_h_Include_Guard
#define Corburt_Curses_h_Include_Guard
//#define CBCurses_Strict  // todo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#if defined(CBCurses_Disable)
    //do nothing
#elif defined(_WIN32)||defined(_WIN64)||defined(WINVER)
    #define CBCurses_Windows
    #include <windows.h>
    #include <conio.h>
    HANDLE hIn,hOut,hOutOld;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD mode;
#else
    #define CBCurses_Unix
    #include <sys/ioctl.h> // window size
    #include <termios.h>
    #include <unistd.h>
    #include <signal.h>
    struct termios orig_termios;
#endif
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	Default=0x00,
	Black=0x01,
	Red=0x02,
	Green=0x03,
	Yellow=0x04,
	Blue=0x05,
	Magenta=0x06,
	Cyan=0x07,
	White=0x08,
	Bright=0x80,
	FG_Mask=0x7F
} cbc_enum_color;
void cbc_init();
void cbc_setwindowtitle(const char *title);
void cbc_getwindowsize(size_t *rows,size_t *cols);
void cbc_setcolor(cbc_enum_color color);
void cbc_clearscreen();
void cbc_hidecursor();
void cbc_showcursor();
void cbc_setcursor(size_t row,size_t col);
void cbc_getcursor(size_t *row,size_t *col);
void cbc_rawmode();
void cbc_cookedmode();
void cbc_setbufferalternate();
int cbc_getch();
#ifndef CBCurses_Disable
static void fail(const char *failmsg){
    if(failmsg==NULL)return;
    FILE *fp=fopen("curseserr.log","w");
    fprintf(fp,"%s\n",failmsg);
    fclose(fp);
}
#endif
#ifdef CBCurses_Windows
static void cbcint_updatebufferinfo();
#endif

/*
void cbc_functiontemplate(){
#ifdef CBCurses_Windows
#elif defined(CBCurses_Unix)
#else
#endif
}
*/
void cbc_init(){
#ifdef CBCurses_Windows
	hIn=GetStdHandle(STD_INPUT_HANDLE);
	hOut=hOutOld=GetStdHandle(STD_OUTPUT_HANDLE);
	if(hOutOld==INVALID_HANDLE_VALUE||hIn==INVALID_HANDLE_VALUE)
		fail("Failure in function init()");
#elif defined(CBCurses_Unix)
#else
#endif
	setlocale(LC_ALL, "");
}
void cbc_setwindowtitle(const char *title){
#ifdef CBCurses_Windows
	TCHAR new_title[64]={0};
	for(size_t i=0;i<63&&i<strlen(title);i++)new_title[i]=title[i];
	if(!SetConsoleTitle(new_title)){
		fail("Failure in function setwindowtitle()");
	}
#elif defined(CBCurses_Unix)
	char buff[64]="\0";
	if(sprintf(buff,"\x1b]0;%s\x7",title)<0||write(STDOUT_FILENO,buff,sizeof(buff))==-1){
		fail("Failure in function setwindowtitle()");
	}
#else
#endif
}
void cbc_getwindowsize(size_t *rows,size_t *cols){
#ifdef CBCurses_Windows
    if(!GetConsoleScreenBufferInfo(hOut,&csbi)){
		fail("Failure in calling GetConsoleScreenBufferInfo() in function getwindowsize()");
	}
	if(rows!=NULL){
		*rows=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
	}
	if(cols!=NULL)
	{
		*cols=csbi.srWindow.Right-csbi.srWindow.Left+1;
	}
#elif defined(CBCurses_Unix)
	struct winsize ws;
	if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws)==-1||ws.ws_col==0){
		if(write(STDOUT_FILENO,"\x1b[999C\x1b[999B",12)!=12){
			fail("Failure in function getwindowsize()");
		}
		get_cursor_position(rows,cols);
		if(rows!=NULL)++(*rows);
		if(cols!=NULL)++(*cols);
	}else{
		if(rows!=NULL)*rows=ws.ws_row;
		if(cols!=NULL)*cols=ws.ws_col;
    }
#else
#endif
}
void cbc_setcolor(cbc_enum_color color){
#ifdef CBCurses_Windows
    CONSOLE_SCREEN_BUFFER_INFO info;
	static WORD dft_wAttributes=0;
	WORD wAttributes=0;
	if(!dft_wAttributes){
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
		dft_wAttributes=info.wAttributes;
	}
	if(Default==(color&FG_Mask)){
		wAttributes|=dft_wAttributes&(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	}else{
		wAttributes|=(color&Bright)?FOREGROUND_INTENSITY:0;
		switch(color&FG_Mask){
			case Red:wAttributes|=FOREGROUND_RED;break;
			case Green:wAttributes|=FOREGROUND_GREEN;break;
			case Blue:wAttributes|=FOREGROUND_BLUE;break;
			case Yellow:wAttributes|=FOREGROUND_RED|FOREGROUND_GREEN;break;
			case Magenta:wAttributes|=FOREGROUND_RED|FOREGROUND_BLUE;break;
			case Cyan:wAttributes|=FOREGROUND_GREEN|FOREGROUND_BLUE;break;
			case White:wAttributes|=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;break;
			default:break;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wAttributes);
#elif defined(CBCurses_Unix)
    printf("\033[m");
	if (Default!=(color&FG_Mask)){
        printf("\033[%dm",29+(color&Mask)+((color&Bright)?60:0));
    }
#else
#endif
}
void cbc_clearscreen(){
#ifdef CBCurses_Windows
	COORD coord={0,0};
	DWORD cCharsWritten,dwConSize;
	cbcint_updatebufferinfo();
	dwConSize=csbi.dwSize.X*csbi.dwSize.Y;
	if(!FillConsoleOutputCharacter(
        hOut,
        (TCHAR)' ',
        dwConSize,
        coord,
        &cCharsWritten)
    ||!FillConsoleOutputAttribute(
        hOut,
        csbi.wAttributes,
        dwConSize,
        coord,
        &cCharsWritten)
    ||!SetConsoleCursorPosition(
        hOut,
        coord))
	{
		fail("Failure in function clearscreen()");
	}
#elif defined(CBCurses_Unix)
    if(write(STDOUT_FILENO,"\x1b[2J",4)!=4||write(STDOUT_FILENO,"\x1b[H",3)!=3){
		fail("Failed to clear the screen");
	}
#else
#endif
}
void cbc_hidecursor(){
#ifdef CBCurses_Windows
	CONSOLE_CURSOR_INFO cursorInfo;
	if(!GetConsoleCursorInfo(hOut,&cursorInfo))
		fail("Failure in calling GetConsoleCursorInfo() in function hidecursor()");
	cursorInfo.bVisible = 0;
	if(!SetConsoleCursorInfo(hOut,&cursorInfo))
		fail("Failure in calling SetConsoleCursorInfo() in function hidecursor()");
#elif defined(CBCurses_Unix)
	if(write(STDOUT_FILENO,"\x1b[?25l",6)!=6){
		fail("Failure in function hidecursor()");
	}
#else
#endif
}
void cbc_showcursor(){
#ifdef CBCurses_Windows
	CONSOLE_CURSOR_INFO cursorInfo;
	if(!GetConsoleCursorInfo(hOut,&cursorInfo))
		fail("Failure in calling GetConsoleCursorInfo() in function hidecursor()");
	cursorInfo.bVisible=1;
	if(!SetConsoleCursorInfo(hOut,&cursorInfo))
		fail("Failure in calling SetConsoleCursorInfo() in function hidecursor()");
#elif defined(CBCurses_Unix)
	if(write(STDOUT_FILENO,"\x1b[?25h",6)!=6){
		fail("Failure in function hidecursor()");
	}
#else
#endif
}
void cbc_setcursor(size_t row,size_t col){
#ifdef CBCurses_Windows
//	COORD coord;
//	coord.X=(SHORT)col;
//	coord.Y=(SHORT)row;
//	if(!SetConsoleCursorPosition(hOut,coord)){
//		fail("Failure in calling SetConsoleCursorPosition() in function setcursor()");
//	}
	GetConsoleScreenBufferInfo(hOut,&csbi);
	csbi.dwCursorPosition.Y=(SHORT)row+csbi.srWindow.Top;
	csbi.dwCursorPosition.X=(SHORT)col+csbi.srWindow.Left;
	SetConsoleCursorPosition(hOut, csbi.dwCursorPosition);
    if(!SetConsoleCursorPosition(hOut,csbi.dwCursorPosition)){
		fail("Failure in calling SetConsoleCursorPosition() in function setcursor()");
	}
#elif defined(CBCurses_Unix)
	char buff[32]="\0";
	if(sprintf(buff,"\x1b[%zu;%zuH",row+1,col+1)<0||write(STDOUT_FILENO,buff,sizeof(buff))==-1){
		fail("Failure in function setcursor()");
	}
#else
#endif
}
void cbc_getcursor(size_t *row,size_t *col){
#ifdef CBCurses_Windows
    CONSOLE_SCREEN_BUFFER_INFO inf;
	if(!GetConsoleScreenBufferInfo(hOut,&inf)){
        fail("Failure in calling GetConsoleScreenBufferInfo() in function getcursor()");
	}
	*row=inf.dwCursorPosition.Y-inf.srWindow.Top;
	*col=inf.dwCursorPosition.X-inf.srWindow.Left;
#elif defined(CBCurses_Unix)
	int i;
	char buf[32];
	printf("\e[6n");
	for(i=0;i<(char)sizeof(buf)-1;++i){
		buf[i]=(char)cbc_getch();
		if('R'== buf[i]){break;}
	}
	buf[i]='\0';
	if(2!=sscanf(buf,"\e[%d;%dR",row,col)){
        fail("Failure in function getcursor()");
        return;
    }
	if(*row>0)(*row)--;
	if(*col>0)(*col)--;
#else
#endif
}
void cbc_rawmode(){
#ifdef CBCurses_Windows
	if(!GetConsoleMode(hIn, &mode)||!SetConsoleMode(hIn,
        mode&~(ENABLE_LINE_INPUT
        |ENABLE_ECHO_INPUT
        |ENABLE_PROCESSED_INPUT
        |ENABLE_PROCESSED_OUTPUT
        |ENABLE_WRAP_AT_EOL_OUTPUT))
    ){
		fail("Failure in function rawmode()");
	}
#elif defined(CBCurses_Unix)
    struct termios raw=orig_termios;
	if(tcgetattr(STDIN_FILENO,&orig_termios)==-1){
		fail("Failure in calling tcgetattr() in function rawmode()");
	}
	raw.c_iflag&=~(BRKINT|ICRNL|INPCK|ISTRIP|IXON);
	raw.c_oflag&=~(OPOST);
	raw.c_cflag|=(CS8);
	raw.c_lflag&=~(ECHO|ICANON|IEXTEN|ISIG);
	raw.c_cc[VMIN]=0;
	raw.c_cc[VTIME]=1;
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw)==-1){
		fail("Failure in calling tcgetattr() in function rawmode()");
	}
#else
#endif
}
void cbc_cookedmode(){
#ifdef CBCurses_Windows
	if(!SetConsoleMode(hIn,mode)){
		fail("Failure in calling SetConsoleMode() in function cookedmode()");
	}
#elif defined(CBCurses_Unix)
#else
#endif
}
void cbc_setbufferalternate(){
#ifdef CBCurses_Windows
	hOutOld = GetStdHandle(STD_OUTPUT_HANDLE);
	hOut = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	if (hOutOld== INVALID_HANDLE_VALUE ||
		hOut==INVALID_HANDLE_VALUE)
		fail("Failure in calling CreateConsoleScreenBuffer() in function setbufferalternate()");
	if (!SetConsoleActiveScreenBuffer(hOut))
		fail("Failure in calling SetConsoleActiveScreenBuffer() in function setbufferalternate()");
#elif defined(CBCurses_Unix)
	if(write(STDOUT_FILENO,"\x1b[?1049h\x1b[H",11)!=11)fail("Failure in function setbufferalternate()");
#else
#endif
}
int cbc_getch(){
#ifdef CBCurses_Windows
	fflush(stdout);
	#ifdef _MSC_VER
	return _getch();
	#else
	return getch();
	#endif
#elif defined(CBCurses_Unix)
	char ch=0;
	struct termios old_term,cur_term;
	fflush(stdout);
	if(tcgetattr(STDIN_FILENO,&old_term)<0){perror("tcsetattr");}
	cur_term=old_term;
	cur_term.c_lflag&=~(ICANON|ECHO|ISIG); // echoing off, canonical off, no signal chars
	cur_term.c_cc[VMIN]=1;
	cur_term.c_cc[VTIME]=0;
	if(tcsetattr(STDIN_FILENO,TCSANOW,&cur_term)<0){perror("tcsetattr");}
	if(read(STDIN_FILENO, &ch,1)<0){ /* perror("read()"); */ } // signal will interrupt
	if(tcsetattr(STDIN_FILENO,TCSADRAIN,&old_term)<0){perror("tcsetattr");}
	return ch;
#else
#endif
    return 0;
}
#ifdef CBCurses_Windows
static void cbcint_updatebufferinfo(){
#ifdef CBCurses_Windows
	if(!GetConsoleScreenBufferInfo(hOut,&csbi))
		fail("Failure in function updatebufferinfo()");
#endif
}
#endif

#ifdef __cplusplus
}
#endif
#endif
