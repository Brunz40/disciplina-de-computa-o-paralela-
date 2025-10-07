#include <math.h>
#include <mpi.h>
#include <stdio.h>
//
// Created by bruno on 07/10/2025.
//
int main(int argc, char *argv[]) {
    //variáveis globais
    int N_cores;
    //variáveis do comunicador cartesiano
    int N_dims=2,N_linhas,N_colunas;
    int dims[N_dims], coords[N_dims],periódico[N_dims];
    MPI_Comm Comunicador_2d;
    //Variáveis locais
    int rank,rank_cartesiano;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &N_cores);

    N_linhas=N_colunas=(int)sqrt(N_cores);
    dims[0]=dims[1]=periódico[0]=periódico[1]=0;

    MPI_Dims_create(N_cores,N_dims,dims);
    MPI_Cart_create(MPI_COMM_WORLD,N_dims,dims,periódico,0,&Comunicador_2d);
    MPI_Cart_coords(Comunicador_2d,rank,N_dims,coords);
    MPI_Cart_rank(Comunicador_2d,coords,&rank_cartesiano);

    printf("%d:Rank cartesiano é %d, coordenadas (%d,%d)\n",rank,rank_cartesiano,coords[0],coords[1]);

    MPI_Comm_free(&Comunicador_2d);
    MPI_Finalize();
}