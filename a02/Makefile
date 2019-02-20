CC = g++

mush: driver.o
	${CC} -g -o mush driver.o command.o tokenizer.o -lreadline
driver.o: driver.cpp command.o tokenizer.o
	${CC} -g -c driver.cpp

command.o: command.cpp command.h
	${CC} -g -c command.cpp

tokenizer.o: tokenizer.cpp tokenizer.h
	${CC} -g -c tokenizer.cpp
clean:
	rm *.o mush
