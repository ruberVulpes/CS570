CC = gcc

main: thread_demo.o worker.o
	${CC} -o thread_demo  thread_demo.o worker.o

thread_demo.o: thread_demo.c
	${CC} -c thread_demo.c

worker.o: worker.c
	${CC} -o worker.c

clean:
	rm mush
