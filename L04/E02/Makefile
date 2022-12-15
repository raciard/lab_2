OBJS	= es02.o Item.o list.o
SOURCE	= es02.c Item.c list.c
HEADER	= Item.h list.h
OUT	= es02.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

es02.o: es02.c
	$(CC) $(FLAGS) es02.c 

Item.o: Item.c
	$(CC) $(FLAGS) Item.c 

list.o: list.c
	$(CC) $(FLAGS) list.c 


clean:
	rm -f $(OBJS) $(OUT)
