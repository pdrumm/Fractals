all: fractals gallery

fractals: fractals.o gfx3.o
	gcc fractals.o gfx3.o -lm -lX11 -o fractals

gallery: gallery.o gfx3.o
	gcc gallery.o gfx3.o -lm -lX11 -o gallery

fractals.o: fractals.c gfx3.h
	gcc -c fractals.c

gallery.o: gallery.c gfx3.h
	gcc -c gallery.c

gfx3.o: gfx3.h
	gcc -c gfx3.c

clean:
	rm *.o fractals gallery
