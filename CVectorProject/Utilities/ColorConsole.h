
#ifndef COLORCONSOLE_H
#define  COLORCONSOLE_H

#include <cstdio>

#define C_GRAY     "\x1b[30m"
#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define C_WHITE    "\x1b[37m"
#define C_RESET   "\x1b[00m"

#define CB_BLACK    "\x1b[40m"
#define CB_RED     "\x1b[41m"
#define CB_GREEN   "\x1b[42m"
#define CB_YELLOW  "\x1b[43m"
#define CB_BLUE    "\x1b[44m"
#define CB_MAGENTA "\x1b[45m"
#define CB_CYAN    "\x1b[46m"
#define CB_WHITE   "\x1b[47m"

#define Color_end "\33[0m\0\0]"



// color manipulation macros
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))
#define setColor(x) printf(x)
#define setColors(x , y)  printf("%s%s",x,y)



#endif // !COLORCONSOLE_H


