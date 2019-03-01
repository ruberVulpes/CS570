CC = gcc

thread_demo: thread_demo.c worker.c
	${CC} -pthread -o thread_demo  thread_demo.c worker.c
clean:
	rm thread_demo
