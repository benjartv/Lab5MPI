
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*Compilacion: mpicc holamundo.c -o exe
Ejecucion: mpirun -np [NUMPROCESOS] ./exe args[]
*/

int main(int argc, char* argv[]){
	int myrank, size;
	int r;
	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); //Cada proceso obtiene su rank
	MPI_Comm_size(MPI_COMM_WORLD, &size); // Cada proceso obtiene su size
	
	/*
	MPI_Recv(&mensaje, 1, MPI_INT, de_que_rank, 0, MPI_COMM_WORLD)
	MPI_Send(&mensaje, 1, MPI_INT, de_que_rank, 0, MPI_COMM_WORLD)
		*/

	/* Anillo: Primer proceso pasa su "myrank" y luego empiezan a sumar cada uno
	de sus myrank y pasarlo a los siguientes procesos
	*/
	int number;
	if(myrank != 0){
		//Recibo los valores del proceso anterior
		MPI_Recv(&number, 1, MPI_INT, myrank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//Aumento el contador, sumando myrank actual para pasarlo al proximo
		srand(time(NULL));
		r = rand() % 10;
		number = number - r;
		printf("Proceso %i tiene la papa con valor %i\n", myrank, number);
		//Envio el nuevo valor al proceso de la derecha, con tal que sea circular (myrank+1)%size
		MPI_Send(&number, 1, MPI_INT, (myrank+1)%size, 0, MPI_COMM_WORLD);
	}	
	else{
		//Si soy el proceso 0, obtengo my rank y lo envio. 	
		srand(time(NULL));
		r = rand() % 10;
		number = 10 - r;
		printf("Proceso %i tiene la papa con valor %i\n", myrank, number);
		MPI_Send(&number, 1, MPI_INT, (myrank+1)%size, 0, MPI_COMM_WORLD);
		//Recibo el valor final desde el proceso a mi izquierda, que sería el último. 
		MPI_Recv(&number, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	MPI_Finalize();
	return 0;
	 
}
