CC = g++ -std=c++11

mizzo: driver.cpp driver.h args.h producer.o consumer.o
	${CC} -g -o mizzo driver.cpp producer.o consumer.o -lpthread -lrt

producer: producer.cpp producer.h args.h
	${CC} -c producer.cpp
consumer: consumer.cpp consumer.h args.h
	${CC} -c consumer.cpp

clean:
	rm  *.o mizzo
