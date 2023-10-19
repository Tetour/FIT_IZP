FILE_IN  = functions.c
FILE_OUT = functions.out

ARGS_DEBUG = -g
ARGS       = -std=c11 -Wall -Wextra

CC	 = gcc
rm	 = rm

all:
	${CC} ${ARGS} ${FILE_IN} -o ${FILE_OUT}

debug:
	${CC} ${ARGS_DEBUG} ${ARGS} ${FILE_IN} -o ${FILE_OUT}

clean:
	${RM} ${FILE_OUT}