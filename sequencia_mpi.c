#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#define N 100000

int sequencia[N],soma[N];
MPI_Status  status;

int main(int argc, char *argv[] )
{
	
	clock_t tempo;
	tempo = clock();
	
	int rank, p, i;
	int tag = 0;

	//iniciando	
	MPI_Init (&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);


	// preenchendo a sequência
	if(rank == 0){		
		for(i=0;i<N;i++){
			sequencia[i] = rand() % 100;
//			printf("Elemento %d: %d\n", i+1, sequencia[i]);
		}
	}

	// Distribuição do Dado	
		MPI_Bcast(&sequencia,N,MPI_INT,0,MPI_COMM_WORLD);


	//codigo
	for (i=0; i<((rank+1)*(N/p)); i++){
	         soma[i] = soma[i-1] + sequencia[i];
	}

	//coletando as informações
	MPI_Gather(&soma[rank*N/p],N/p,MPI_INT,&soma[rank*N/p],N/p,MPI_INT,0,MPI_COMM_WORLD);

	if(rank == 0){
		for (i=0;i<N;i++){
//         	printf("Soma %d: %d\n", i+1,soma[i]);
		}
		printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
	}

	MPI_Finalize();	

	return 0;
}
