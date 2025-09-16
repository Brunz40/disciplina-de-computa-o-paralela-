#include <mpi.h>
#include <stdio.h>

#include "operação vetorial.h"
#define Ncores 8
int main(int argc, char **argv) {
    int N_tarefas, rank, N_envios, N_recebidos, cabeça=1;
    float buffer_origem_A[16]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};
    float buffer_origem_B[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    float buffer_destino_A[16/Ncores];
    float buffer_destino_B[16/Ncores];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &N_tarefas);

    N_envios=N_recebidos=16/N_tarefas;

    MPI_Scatter(buffer_origem_A,N_envios,MPI_FLOAT,buffer_destino_A,N_recebidos,MPI_FLOAT,cabeça,MPI_COMM_WORLD);
    MPI_Scatter(buffer_origem_B,N_envios,MPI_FLOAT,buffer_destino_B,N_recebidos,MPI_FLOAT,cabeça,MPI_COMM_WORLD);
    //buffer_origem_A=somar(buffer_origem_A,buffer_origem_B); todo consertar acesso de memória da função soma e produt0
    MPI_Gather(buffer_destino_A,N_recebidos,MPI_FLOAT,buffer_origem_A,N_envios,MPI_FLOAT,cabeça,MPI_COMM_WORLD);
    //MPI_Gather(buffer_destino_B,N_recebidos,MPI_FLOAT,buffer_origem_B,N_envios,MPI_FLOAT,cabeça,MPI_COMM_WORLD);
    if (rank==1) {
        for(int i=0;i<16;i++) {
            printf("Result %f\n",buffer_origem_B[i]);
        }
    }
    MPI_Finalize();

    return 0;
}
