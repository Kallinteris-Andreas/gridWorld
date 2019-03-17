CC = clang++

BASICFLAGS= 

FLAGS= -Wall $(BASICFLAGS)

OPTFLAG= 

program: grid.o main.o
	$(CC) $(FLAGS) main.o -o program

main.o: main.cc main.h
	$(CC) -c main.cc

grid.o: grid.cc grid.h
	$(CC) -c grid.cc

clean:
	rm *.o program

#compile and run
cr:
	make
	./program
