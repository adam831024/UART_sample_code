objects = rs232-win.o uart.o main.o
CC = gcc

app: main.o uart.o rs232-win.o
	$(CC) -o app main.o uart.o rs232-win.o -lpthread

main.o: main.c uart.h rs232.h
	$(CC) -c main.c -lpthread

uart.o: uart.c rs232.h
	$(CC) -c uart.c -lpthread

rs232-win.o: rs232.h
	$(CC) -c rs232-win.c

clean: 
	del -f $(objects)