CC = gcc -Wall -g

LIBSRC = lib/get.c lib/run.c lib/strings.c
LIBOBJ= ${LIBSRC:%.c=%.o}

SRC = src/initials.c src/main.c
OBJ = ${SRC:%.c=%.o}

TESTSRC = test/alltests.c
TESTEXE = alltests

EXE = foamTools
ALLOBJ = ${OBJ} ${LIBOBJ}

build: $(SRC)
	$(foreach src,${SRC},${CC} -o $(src:%.c=%.o) $(src) -c;)
	$(CC) -o $(EXE) $(OBJ) -Llib -loftools
	rm -f ${OBJ}

libs: ${LIBSRC}
	$(foreach lib,${LIBSRC},${CC} -o $(lib:%.c=%.o) -c $(lib);)
	ar rcs lib/liboftools.a ${LIBOBJ}
	ranlib lib/liboftools.a
	rm -f ${LIBOBJ}

unittests:
	$(CC) -o ${TESTEXE} ${TESTSRC} -Llib -loftools

clean:
	-rm -f ${ALLOBJ} ${EXE} ${TESTEXE} lib/*.a

tests: clean libs unittests

rebuild: clean libs build
