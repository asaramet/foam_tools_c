CC = gcc -Wall -g
LIBS = lib/get.c lib/run.c
FILES = test.c
OUT_EXE = foam.o

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) -Llib -loftools

libs: ${LIBS}
	${CC} -o strings.o -c lib/strings.c
	${CC} -o get.o -c lib/get.c
	${CC} -o run.o -c lib/run.c
	ar rcs lib/liboftools.a strings.o get.o run.o
	ranlib lib/liboftools.a
	rm -f get.o run.o

clean:
	-rm -f *.o lib/*.a

rebuild: clean libs build
