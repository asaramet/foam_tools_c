CC = gcc -Wall -g
LIBS = lib/get.c lib/run.c lib/strings.c
O_LIBS= get.o run.o strings.o
FILES = initials.c main.c test.c
O_FILES = initials.o main.o
OUT_EXE = foam.o

build: $(FILES)
	$(CC) -o atest.o test.c -Llib -loftools

	$(CC) -o initials.o initials.c -c
	$(CC) -o main.o main.c -c
	$(CC) -o $(OUT_EXE) $(O_FILES) -Llib -loftools
	rm -f ${O_FILES}

libs: ${LIBS}
	${CC} -o strings.o -c lib/strings.c
	${CC} -o get.o -c lib/get.c
	${CC} -o run.o -c lib/run.c
	ar rcs lib/liboftools.a ${O_LIBS}
	ranlib lib/liboftools.a
	rm -f ${O_LIBS}

clean:
	-rm -f *.o lib/*.a

rebuild: clean libs build
