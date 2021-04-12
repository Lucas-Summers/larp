# larp - lisp interpreter written in c
# See LICENSE file for copyright and license details

NAME=larp
VERSION = 0.1
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
CC = gcc
LDFLAGS =
CFLAGS = -std=c99 -Wall
TARGET=${NAME}.out
SRC = $(wildcard src/*.c)
OBJ = $(subst src/test.o,,${SRC:.c=.o})
TEST_OBJ= $(subst src/main.o,src/test.o,${OBJ})
PROJ_FILES = src examples Makefile README LICENSE ${NAME}-${VERSION}

all: options clean ${TARGET}

options:
	@echo ${NAME} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

%.o: %.c
	${CC} -o $@ -c ${CFLAGS} $<

${TARGET}: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

${TARGET}.test: ${TEST_OBJ}
	${CC} -o $@ ${TEST_OBJ} ${LDFLAGS}

test: options clean ${TARGET}.test
	./${TARGET}.test

dist: clean
	mkdir -p ${NAME}-${VERSION}
	cp -R ${PROJ_FILES}
	tar -cf ${NAME}-${VERSION}.tar ${NAME}-${VERSION}
	gzip ${NAME}-${VERSION}.tar
	rm -rf ${NAME}-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${NAME} ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/${NAME}
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < ${NAME}.1 > ${DESTDIR}${MANPREFIX}/man1/${NAME}.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/${NAME}.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/${NAME}\
		${DESTDIR}${MANPREFIX}/man1/${NAME}.1
clean:
	rm -f ${NAME}.* src/*.o source/*.a ${NAME}-${VERSION}.tar.gz

.PHONY: all options clean test dist install uninstall
