CC = gcc
LD = ld
AS = as
AR = ar
CFLAGS = -g3 -O0
LDFLAGS = -L.
INC_FILES = -I.


TROCHILUS_PATH = ../../..

INC_FILES += -I${TROCHILUS_PATH}/src/trls_cunit_test/CUnit/Headers
INC_FILES += -I${TROCHILUS_PATH}/src
INC_FILES += -I${TROCHILUS_PATH}/src/include
INC_FILES += -I${TROCHILUS_PATH}/src/core
INC_FILES += -I${TROCHILUS_PATH}/src/event
INC_FILES += -I${TROCHILUS_PATH}/src/module


LDFLAGS += -L${TROCHILUS_PATH}
LDFLAGS += -L${TROCHILUS_PATH}/src/trls_cunit_test/CUnit/Sources/.libs


INC_LIBS = -lcunit
INC_LIBS += -ltrochilus


trls_cunit: clean
	${CC} ${CFLAGS} \
    ${INC_FILES} \
    ${LDFLAGS} \
    ${INC_LIBS} \
    -o trls_cunit \
    trls_cunit.c \
    cunit_trls_queue.c

	$(chmod 755 trls_cunit)

clean:
	rm -rf trls_cunit 

