#ifndef __CBCURSES
#define __CBCURSES
// Acknowledgements to JCWang's repo Crossline
// at https://github.com/jcwangxp/Crossline

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __CBSYS // Platform detection
    #if !defined(__CB_WINDOWS) && !defined(__CB_POSIX)
        #if defined(_WIN32)
            #define __CB_WINDOWS
        #elif defined(__POSIX__) || defined(__APPLE__) || defined(__linux__)  ||  defined(__FreeBSD__)  ||  defined(__EMSCRIPTEN__)
            #define __CB_POSIX
        #else
            #error Compile Error: Unsupported platform.
        #endif
    #endif
#endif

#if defined(__CB_WINDOWS)
    #include <windows.h>
    #include <conio.h>
    static HANDLE hOut;
    static CONSOLE_SCREEN_BUFFER_INFO csbi;
//    static DWORD mode;
#elif defined(__CB_POSIX)
    #include <sys/ioctl.h> // window size
    #include <termios.h>
    #include <unistd.h>
    #include <signal.h>
    static struct termios orig_termios;
#else
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
} _color16;

int __cbcurses_current_color=Default;

void __CBCurses_Fail(const char *msg);
void __CBCurses_Init(void);
void __CBCurses_SetWindowTitle(const char *title);
void __CBCurses_GetWindowSize(size_t *rows, size_t *cols);
void __CBCurses_SetColor(int color);
int __CBCurses_GetColor(void);
void __CBCurses_Cls(void);
void __CBCurses_HideCursor(void);
void __CBCurses_ShowCursor(void);
void __CBCurses_SetCursor(size_t row, size_t col);
void __CBCurses_GetCursor(size_t *row, size_t *col);
int __CBCurses_Getch(void);

const struct {
    void (*init)(void);
    void (*setTitle)(const char *title);
    void (*getWindowSize)(size_t *rows, size_t *cols);
    void (*setColor)(int color);
    int (*getColor)(void);
    void (*cls)(void);
    void (*hideCursor)(void);
    void (*showCursor)(void);
    void (*setCursor)(size_t row, size_t col);
    void (*getCursor)(size_t *row, size_t *col);
} Curses = {
    .init=__CBCurses_Init,
    .setTitle=__CBCurses_SetWindowTitle,
    .getWindowSize=__CBCurses_GetWindowSize,
    .setColor=__CBCurses_SetColor,
    .getColor=__CBCurses_GetColor,
    .cls=__CBCurses_Cls,
    .hideCursor=__CBCurses_HideCursor,
    .showCursor=__CBCurses_ShowCursor,
    .setCursor=__CBCurses_SetCursor,
    .getCursor=__CBCurses_GetCursor
};

void __CBCurses_Fail(const char *msg){
    int color=Curses.getColor();
    Curses.setColor(Red|Bright);
    printf("[ERROR] %s\n", msg);
    Curses.setColor(color);
}

void __CBCurses_Init(void){
#if defined(__CB_WINDOWS)
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	if(hOut==INVALID_HANDLE_VALUE)
		__CBCurses_Fail("Failed to initialize curses.");
#elif defined(__CB_POSIX)
#else
#endif
}
void __CBCurses_SetWindowTitle(const char *title){
#if defined(__CB_WINDOWS)
	TCHAR new_title[64]={0};
	for(size_t i=0; i<63 && i<strlen(title); i++)new_title[i]=title[i];
	if(!SetConsoleTitle(new_title)){
		__CBCurses_Fail("Failed to set window title.");
	}
#elif defined(__CB_POSIX)
	char buff[64]="\0";
	if(sprintf(buff, "\x1b]0;%s\x7", title)<0 || write(STDOUT_FILENO, buff, sizeof(buff))==-1){
		__CBCurses_Fail("Failed to set window title.");
	}
#else
#endif
}
void __CBCurses_GetWindowSize(size_t *rows, size_t *cols){
#if defined(__CB_WINDOWS)
    if(!GetConsoleScreenBufferInfo(hOut, &csbi)){
		__CBCurses_Fail("Failed to get window size.");
		return;
	}
	if(rows!=NULL){
		*rows=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
	}
	if(cols!=NULL)
	{
		*cols=csbi.srWindow.Right-csbi.srWindow.Left+1;
	}
#elif defined(__CB_POSIX)
	struct winsize ws;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)==-1 || ws.ws_col==0){
		if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12)!=12){
			__CBCurses_Fail("Failed to get window size.");
			return;
		}
//		get_cursor_position(rows, cols);
//		if(rows!=NULL)++(*rows);
//		if(cols!=NULL)++(*cols);
		if(rows!=NULL)*rows=ws.ws_row;
		if(cols!=NULL)*cols=ws.ws_col;
	}else{
		if(rows!=NULL)*rows=ws.ws_row;
		if(cols!=NULL)*cols=ws.ws_col;
    }
#else
#endif
}
void __CBCurses_SetColor(int color){
    if(color==__cbcurses_current_color)return;
    __cbcurses_current_color=color;
    fflush(stdout);
#if defined(__CB_WINDOWS)
    CONSOLE_SCREEN_BUFFER_INFO info;
	static WORD dft_wAttributes=0;
	WORD wAttributes=0;
	if(!dft_wAttributes){
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		dft_wAttributes=info.wAttributes;
	}
	if(Default==(color&FG_Mask)){
		wAttributes|=dft_wAttributes&(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
		wAttributes|=(color&Bright)?FOREGROUND_INTENSITY:0;
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);
#elif defined(__CB_POSIX)
    printf("\033[m");
	if (Default!=(color&FG_Mask)){
        printf("\033[%dm", 29+(color&FG_Mask)+((color&Bright)?60:0));
    } else {
        if(color&Bright){
            printf("\033[1m");
        }
    }
#else
#endif
}
int __CBCurses_GetColor(void){
    return __cbcurses_current_color;
}
void __CBCurses_Cls(void){
#if defined(__CB_WINDOWS)
	COORD coord={0, 0};
	DWORD cCharsWritten, dwConSize;
	GetConsoleScreenBufferInfo(hOut, &csbi);
	dwConSize=csbi.dwSize.X*csbi.dwSize.Y;
	if(!FillConsoleOutputCharacter(
        hOut,
        (TCHAR)' ',
        dwConSize,
        coord,
        &cCharsWritten)
     || !FillConsoleOutputAttribute(
        hOut,
        csbi.wAttributes,
        dwConSize,
        coord,
        &cCharsWritten)
     || !SetConsoleCursorPosition(
        hOut,
        coord))
	{
		__CBCurses_Fail("Failed to clear screen.");
	    system("cls");
	}
#elif defined(__CB_POSIX)
    if(write(STDOUT_FILENO, "\x1b[2J", 4)!=4 || write(STDOUT_FILENO, "\x1b[H", 3)!=3){
		__CBCurses_Fail("Failed to clear screen.");
	}
#else
#endif
}
void __CBCurses_HideCursor(void){
#if defined(__CB_WINDOWS)
	CONSOLE_CURSOR_INFO cursorInfo;
	if(!GetConsoleCursorInfo(hOut, &cursorInfo)){
		__CBCurses_Fail("Failed to hide cursor.");
		return;
	}
	cursorInfo.bVisible = 0;
	if(!SetConsoleCursorInfo(hOut, &cursorInfo))
		__CBCurses_Fail("Failed to hide cursor.");
#elif defined(__CB_POSIX)
	if(write(STDOUT_FILENO, "\x1b[?25l", 6)!=6){
		__CBCurses_Fail("Failed to hide cursor.");
	}
#else
#endif
}
void __CBCurses_ShowCursor(void){
#if defined(__CB_WINDOWS)
	CONSOLE_CURSOR_INFO cursorInfo;
	if(!GetConsoleCursorInfo(hOut, &cursorInfo)){
		__CBCurses_Fail("Failed to show cursor.");
		return;
	}
	cursorInfo.bVisible=1;
	if(!SetConsoleCursorInfo(hOut, &cursorInfo))
		__CBCurses_Fail("Failed to show cursor.");
#elif defined(__CB_POSIX)
	if(write(STDOUT_FILENO, "\x1b[?25h", 6)!=6){
		__CBCurses_Fail("Failed to show cursor.");
	}
#else
#endif
}
void __CBCurses_SetCursor(size_t row, size_t col){
#if defined(__CB_WINDOWS)
//	COORD coord;
//	coord.X=(SHORT)col;
//	coord.Y=(SHORT)row;
//	if(!SetConsoleCursorPosition(hOut, coord)){
//		__CBCurses_Fail("Failed to set cursor position");
//      return;
//	}
	GetConsoleScreenBufferInfo(hOut, &csbi);
	csbi.dwCursorPosition.Y=(SHORT)row+csbi.srWindow.Top;
	csbi.dwCursorPosition.X=(SHORT)col+csbi.srWindow.Left;
	SetConsoleCursorPosition(hOut, csbi.dwCursorPosition);
    if(!SetConsoleCursorPosition(hOut, csbi.dwCursorPosition)){
		__CBCurses_Fail("Failed to set cursor position.");
	}
#elif defined(__CB_POSIX)
	char buff[32]="\0";
	if(sprintf(buff, "\x1b[%zu;%zuH", row+1, col+1)<0 || write(STDOUT_FILENO, buff, sizeof(buff))==-1){
		__CBCurses_Fail("Failed to set cursor position.");
	}
#else
#endif
}
void __CBCurses_GetCursor(size_t *row, size_t *col){
#if defined(__CB_WINDOWS)
    CONSOLE_SCREEN_BUFFER_INFO inf;
	if(!GetConsoleScreenBufferInfo(hOut, &inf)){
        __CBCurses_Fail("Failed to get cursor position.");
	}
	*row=inf.dwCursorPosition.Y-inf.srWindow.Top;
	*col=inf.dwCursorPosition.X-inf.srWindow.Left;
#elif defined(__CB_POSIX)
	int i;
	char buf[32];
	printf("\e[6n");
	for(i=0; i<(char)sizeof(buf)-1;++i){
		buf[i]=(char)__CBCurses_Getch();
		if('R'== buf[i]){break;}
	}
	buf[i]='\0';
	int irow,icol;
	if(2!=sscanf(buf, "\e[%d;%dR", &irow, &icol)){
        __CBCurses_Fail("Failed to get cursor position.");
        return;
    }
    *row=irow;
    *col=icol;
	if(*row>0)(*row)--;
	if(*col>0)(*col)--;
#else
#endif
}
int __CBCurses_Getch(void){
#if defined(__CB_WINDOWS)
	fflush(stdout);
	#ifdef _MSC_VER
	return _getch();
	#else
	return getch();
	#endif
#elif defined(__CB_POSIX)
	char ch=0;
	struct termios old_term, cur_term;
	fflush(stdout);
	if(tcgetattr(STDIN_FILENO, &old_term)<0){perror("tcsetattr");}
	cur_term=old_term;
	cur_term.c_lflag&=~(ICANON|ECHO|ISIG); // echoing off, canonical off, no signal chars
	cur_term.c_cc[VMIN]=1;
	cur_term.c_cc[VTIME]=0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &cur_term)<0){perror("tcsetattr");}
	if(read(STDIN_FILENO, &ch, 1)<0){ /* perror("read()"); */ } // signal will interrupt
	if(tcsetattr(STDIN_FILENO, TCSADRAIN, &old_term)<0){perror("tcsetattr");}
	return ch;
#else
#endif
    return 0;
}


#ifdef __cplusplus
}
#endif
#endif
