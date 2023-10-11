FILE_IN  = cfilter.c
FILE_OUT = cfilter

ARGS_DEBUG = -g
ARGS       = -std=c11 -Wall -Wextra # -Werror

CC	 = gcc
rm	 = rm

all:
	${CC} ${ARGS} ${FILE_IN} -o ${FILE_OUT}

debug:
	${CC} ${ARGS_DEBUG} ${ARGS} ${FILE_IN} -o ${FILE_OUT}

clean:
	${RM} ${FILE_OUT}