#include "hotpotatofunct.h"

int main(int argc, char* argv[]){
	int myrank, nproc;
	int r, i;
	int token = get_token(argc, argv);
	

	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); //Cada proceso obtiene su rank
	MPI_Comm_size(MPI_COMM_WORLD, &nproc); // Cada proceso obtiene el # de procesos


	int metadata = 4; // token, cantidad de jugadores, turno
	int valores = nproc+metadata;
	int n_right, n_left;

	int *data = (int*)malloc(sizeof(int)*valores);
	for (i = 0; i < valores; i++)
	{
		data[i] = 1; //Todos los procesos juegan (0 en caso de que pierda alguno)
	}
	data[PLAYERS] = nproc; // Jugadores actuales: todos
	data[TURN] = 0; //Comienza el proceso 0
	data[START] = 0; //{0,1}; 0 indica que hay que generar un nuevo token
	data[TOKEN] = token;

	n_right = (myrank+1)%nproc;
	if (myrank == 0)
		n_left = nproc-1;
	else
		n_left = myrank-1;

	//MPI_Barrier(MPI_COMM_WORLD);
	while(data[PLAYERS] > 1){
		if(data[myrank] == 1){ //Revisar estoy jugando jugando
			if (myrank == data[TURN]) //Revisar si es mi turno
			{
				while(data[n_right] == 0){ //Revisar cual es mi jugador a la derecha
					n_right = (n_right+1)%nproc;
				}
				while(data[n_left] == 0){ //Revisar cual es mi jugador a la izquierda
					n_left = n_left -1;
					if (n_left == -1)
						n_left = nproc-1;
				}
				if (data[START]==0)
				{
					srand(time(NULL));
					r = rand() % token + 1;
					data[TOKEN] = token - r;
					data[START] = 1; //Nuevo token generado
					printf("Proceso %i tiene la papa con valor %i\n", myrank, data[TOKEN]);
				}
				else{
					srand(time(NULL));
					r = rand() % token + 1;
					data[TOKEN] = data[TOKEN] - r;
					printf("Proceso %i tiene la papa con valor %i", myrank, data[TOKEN]);
					if (data[TOKEN] < 0) //Revisar si el jugador perdió o sigue en juego
					{
						printf(" (proceso %i sale del juego)\n", myrank);
						data[myrank] = 0; //El proceso perdió
						data[START] = 0; //Aviso para generar nuevo token
						data[PLAYERS] = data[PLAYERS] - 1;
					}
					else
						printf("\n");
				}
				data[TURN] = n_right;
				MPI_Send(data, valores, MPI_INT, n_right, 0, MPI_COMM_WORLD);
			}
			else{
				//Si no es el turno del proceso, espera que llegue el mensaje
				MPI_Recv(data, valores, MPI_INT, n_left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}
		else{
			break;
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);

	if (data[myrank] == 1) //El proceso ganador indica la victoria
	{	
		printf("Proceso %i es el ganador\n", myrank);		
	}
	
	MPI_Finalize();
	return 0;
	 
}