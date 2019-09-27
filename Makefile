CC=gcc
CFLAGS= -Wall -pthread -lpigpio

main: main.o ST7789/ST7789.o
	$(CC) -o main main.o ST7789/ST7789.o $(CFLAGS)
