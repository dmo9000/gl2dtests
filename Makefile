CC=/usr/bin/x86_64-w64-mingw32-gcc-6.4.0.exe
#CC=/usr/bin/i686-pc-mingw32-gcc.exe

#CFLAGS=-I/usr/i686-w64-mingw32/sys-root/mingw/include/
#LDFLAGS=-L/usr/x86_64-w64-mingw32/sys-root/mingw/lib/ -lglut -lGL
#LDFLAGS=-L/usr/x86_64-w64-mingw32/sys-root/mingw/lib/ -lglut  -lglu -lopengl

##CFLAGS=-I/usr/i686-w64-mingw32/sys-root/mingw/include
LDFLAGS=-L/usr/x86_64-w64-mingw32/sys-root/mingw/lib/ -L/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ -lglu32 -lopengl32 -lglut



glhello:	glhello.o
	$(CC) -o glhello glhello.o /usr/x86_64-w64-mingw32/sys-root/mingw/lib/libglut.a -L/usr/x86_64-w64-mingw32/sys-root/mingw/lib/ -lglu32 -lopengl32 -lglut

clean:
	rm glhello *.o
