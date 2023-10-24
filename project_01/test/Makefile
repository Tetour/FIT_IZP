FILE_IN  = test_main.cpp
FILE_OUT = ../build/keyfilter_unit_tests.out

ARGS_DEBUG = -g
ARGS       = -std=c++11

CC	 = g++
rm	 = rm

all:
	${CC} ${ARGS} ${FILE_IN} -o ${FILE_OUT}

debug:
	${CC} ${ARGS_DEBUG} ${ARGS} ${FILE_IN} -o ${FILE_OUT}

clean:
	${RM} ${FILE_OUT}