
CC = gcc
CFLAGS = -Wall

SRC = main.c home.c multiplayer.c bot.c
TARGET = tictactoe.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	del $(TARGET)
	echo Clean complete.