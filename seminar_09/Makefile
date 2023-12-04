FILE_IN  = fib.c
FILE_OUT = fib.out

ARGS_DEBUG = -g
ARGS       = -std=c11 -Wall -Wextra -pedantic

CC	 = gcc
rm	 = rm

all:
	${CC} ${ARGS} ${FILE_IN} -o ${FILE_OUT}

debug:
	${CC} ${ARGS_DEBUG} ${ARGS} ${FILE_IN} -o ${FILE_OUT}

clean:
	${RM} ${FILE_OUT}