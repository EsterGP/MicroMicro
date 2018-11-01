#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define NUM_THREADS 4
#define N 100000

void main(){
	clock_t tempo;
	tempo = clock();

	int i, np, resultado[N], sequencia[N], soma[N];

	for(i=0;i<N;i++){
		sequencia[i] = rand() % 100;
//		printf("Elemento %d: %d\n", i+1, sequencia[i]);
	}

	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel private(i,soma,np) shared(sequencia,resultado)
	{
		np = omp_get_thread_num();
		soma[0] = sequencia[0];
//		printf("Thread %d:\n", np);
		for (i=1; i<(np+1)*N/NUM_THREADS; i++){
        	soma[i] = soma[i-1] + sequencia[i];
		}

		#pragma omp for
			for(i=0;i<N;i++){
				resultado[i] = soma[i];
//				printf("Soma %d: %d\n", i+1,resultado[i]);
			}
	}

//	printf("\nSOMA\n");
	
	for (i=0;i<N;i++){
//         	printf("Soma %d: %d\n", i+1,resultado[i]);
	}
	printf("Tempo:%f \n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
}
