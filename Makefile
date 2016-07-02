INC = -I./include
CFLAGS = -Wall
CC = mpicc

main: ./build/hotpotato.o ./build/hotpotatofunct.o
	@ $(CC) -o ./bin/hotpotato ./build/hotpotato.o ./build/hotpotatofunct.o $(CFLAGS)
	@ echo "The compilation has been completed successfully"

build/hotpotato.o: ./src/hotpotato.c
	@ echo "src/hotpotato.c"
	@ $(CC) -c ./src/hotpotato.c $(INC) -o ./build/hotpotato.o $(CFLAGS)

build/hotpotatofunct.o: ./src/hotpotatofunct.c
	@ echo "src/hotpotatofunct.c"
	@ $(CC) -c ./src/hotpotatofunct.c $(INC) -o ./build/hotpotatofunct.o $(CFLAGS)

clean:
	@ clear
	@ echo "Cleaning folders.."
	@ rm -rf build/*
	@ rm -rf bin/*
	@ rm -rf output/*

run:
	@ clear
	@ echo "Hot Potato MPI"
	@ mpirun -np 6 ./bin/hotpotato -t 10
