CC = G++

mush: driver.o
	${CC} -g -o mush driver.o command.o tokenizer.o -lreadline
driver.o: driver.cpp command.o tokenizer.o
	${CC} -g -c driver.cpp -lreadline

command.o: command.cpp
	${CC} -g -c command.cpp

tokenizer.o: tokenizer.cpp
	${CC} -g -c tokenizer.cpp -lreadline
clean:
	rm *.o mush
