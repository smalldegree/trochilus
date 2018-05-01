CC = gcc
LD = ld
AR = ar
CFLAGS = -g3 -O0
LDFLAGS = -I. -L.
INCLUDES = -Isrc \
           -Isrc/include \
           -Isrc/core \
           -Isrc/event \
           -Isrc/module
SO_FLAGS = -shared -fPIC
STATIC_FLAGS = -static


libtrochilus: clean
	${CC} ${CFLAGS} \
    ${LDFLAGS} ${INCLUDES} ${SO_FLAGS} -o libtrochilus.so \
    src/core/trls_queue.c


clean:
	rm -rf *.so
