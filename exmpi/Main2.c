#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "operação vetorial.h"

int main(int argc, char **argv) {

    int N_tarefas, rank, N_envios, N_recebidos, cabeça=0;




    double inicio,fim;
    MPI_Init(&argc, &argv);
    inicio=MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &N_tarefas);
    unsigned int carga=N_tarefas*1000;
    float *buffer_origem_A;
    float *buffer_origem_B;
    N_envios=N_recebidos=carga/N_tarefas;
    if (rank == cabeça) {
        buffer_origem_A = malloc(sizeof(float) * carga);
        buffer_origem_B = malloc(sizeof(float) * carga);
        for (unsigned int i = 0; i < carga; i++) {
            buffer_origem_A[i] = (random()%10);
            buffer_origem_B[i] = (random()%10);
        }
    }
    float *buffer_destino_A = malloc(sizeof(float)*(carga/N_tarefas));
    float *buffer_destino_B = malloc(sizeof(float)*(carga/N_tarefas));



    MPI_Scatter(buffer_origem_A,N_envios,MPI_FLOAT,buffer_destino_A,N_recebidos,MPI_FLOAT,cabeça,MPI_COMM_WORLD);
    MPI_Scatter(buffer_origem_B,N_envios,MPI_FLOAT,buffer_destino_B,N_recebidos,MPI_FLOAT,cabeça,MPI_COMM_WORLD);

    float aux_soma_A[N_recebidos];
    float aux_produto_A[N_recebidos];
    for (unsigned int i = 0; i < N_recebidos; i++) {
        aux_soma_A[i] = buffer_destino_A[i]+buffer_destino_B[i];
        aux_produto_A[i] = buffer_destino_A[i]*buffer_destino_B[i];
    }

    MPI_Gather(aux_produto_A,N_recebidos,MPI_FLOAT,buffer_origem_A,N_envios,MPI_FLOAT,cabeça,MPI_COMM_WORLD);
    MPI_Gather(aux_soma_A,N_recebidos,MPI_FLOAT,buffer_origem_B,N_envios,MPI_FLOAT,cabeça,MPI_COMM_WORLD);
    fim=MPI_Wtime();
    free(buffer_destino_A);
    free(buffer_destino_B);
    if (rank==cabeça) {
        for(int i=0;i<16;i++) {
            printf("somas %f\n",buffer_origem_B[i]);
            printf("produtos %f\n",buffer_origem_A[i]);
        }
        printf("tempo decorrido foi:%lf",fim-inicio);
        free(buffer_origem_A);
        free(buffer_origem_B);
    }
    MPI_Finalize();
    return 0;
}
