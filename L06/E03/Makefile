OBJS	= main.o Inventario.o InvList.o Pg.o pglist.o
SOURCE	= main.c Inventario.c InvList.c Pg.c pglist.c
HEADER	= Inventario.h InvList.h menu.h Pg.h pglist.h
OUT	= gdr.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

Inventario.o: Inventario.c
	$(CC) $(FLAGS) Inventario.c 

InvList.o: InvList.c
	$(CC) $(FLAGS) InvList.c 

Pg.o: Pg.c
	$(CC) $(FLAGS) Pg.c 

pglist.o: pglist.c
	$(CC) $(FLAGS) pglist.c 


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT) all
	./$(OUT)
