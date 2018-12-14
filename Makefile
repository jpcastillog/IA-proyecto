all = killersudoku
killersudoku: main.o instance.o forwardchecking.o
	g++ main.o instance.o forwardchecking.o -o killersudoku -I.

main.o: main.cpp 
	g++ -c main.cpp -Wall -I.

instance.o: instance.cpp instance.h
	g++ -c instance.cpp -Wall -I.

forwardcheking.o: forwardchecking.cpp forwardchecking.h
	g++ -c forwardchecking.cpp -Wall -I.

clean: 
	rm main.o instance.o forwardchecking.o

run:
	./killersudoku
