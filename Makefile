# Uncomment for MINGW64

CC=/usr/bin/x86_64-w64-mingw32-gcc-6.4.0.exe
#LDFLAGS=-L/usr/x86_64-w64-mingw32/sys-root/mingw/lib/ -L/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ -lglu32 -lopengl32 -lglut


glhello:	glhello.o rawfont.o
	$(CC) -o glhello glhello.o rawfont.o -lglut -lGLU -lGL
	


glhello.exe:	glhello.o rawfont.o
	$(CC) -o glhello.exe glhello.o rawfont.o /usr/x86_64-w64-mingw32/sys-root/mingw/lib/libglut.a -L/usr/x86_64-w64-mingw32/sys-root/mingw/lib/ -lglu32 -lopengl32 -lglut

clean:
	rm -f glhello.exe glhello *.o
