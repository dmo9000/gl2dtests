#CFLAGS=-I/usr/i686-w64-mingw32/sys-root/mingw/include/
CFLAGS = -c 

glhello:	glhello.o
	gcc -o glhello glhello.o -lglut -lGL
	

