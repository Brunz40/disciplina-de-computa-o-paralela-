//
// Created by bruno on 06/10/2025.
//
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 int main (int argc, char *argv[]) {
    //variáveis globais
     int N_cores, soma;

     //variáveis locais
     int rank, rank_comunicador_1, rank_comunicador_2, erro=0,teste=0;


     //variáveis de grupo
    MPI_Group grupo_mundo_1, grupo_mundo_2, grupo_comunicador_1, grupo_comunicador_2;
     MPI_Comm comunicador_1 , comunicador_2;
  int* processos_comunicadror1;
     int* processos_comunicador_2;

     MPI_Init(&argc, &argv);
     MPI_Comm_size(MPI_COMM_WORLD, &N_cores);
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
     MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

     processos_comunicadror1 = malloc(N_cores/2*sizeof(int));
     processos_comunicador_2 = malloc(N_cores/2*sizeof(int));
     for (int proc=0; proc<N_cores/2; proc++) {
         processos_comunicadror1[proc] = proc;
         processos_comunicador_2[proc] = proc+(N_cores/2);
     }

     MPI_Comm_group(MPI_COMM_WORLD, &grupo_mundo_1);
     MPI_Group_incl(grupo_mundo_1,N_cores/2,processos_comunicadror1,&grupo_comunicador_1);
     MPI_Comm_create(MPI_COMM_WORLD,grupo_comunicador_1,&comunicador_1);
     erro=MPI_Comm_rank(comunicador_1,&rank_comunicador_1);
     if (erro != MPI_SUCCESS) {
         printf("%d não pertence ao comunicador 1\n",rank);
     }else {
         printf("%d pertence ao comunicador 1\n",rank);
         teste=1;
     }
     MPI_Reduce(&teste,&soma,1,MPI_INT,MPI_SUM,0,comunicador_1);

    MPI_Comm_group(MPI_COMM_WORLD,&grupo_mundo_2);
     MPI_Group_incl(grupo_mundo_2,N_cores/2,processos_comunicador_2,&grupo_comunicador_2);
     MPI_Comm_create(MPI_COMM_WORLD,grupo_comunicador_2,&comunicador_2);
     erro=MPI_Comm_rank(comunicador_2,&rank_comunicador_2);
     if (erro != MPI_SUCCESS) {
         printf("%d não pertence ao comunicador 2\n", rank_comunicador_2);
     }else {
         printf("%d pertence ao comunicador 2\n",rank_comunicador_2);
         teste=2;
     }
     MPI_Reduce(&teste,&soma,1,MPI_INT,MPI_SUM,0,comunicador_2);
    printf("soma=%d\n",soma);
     MPI_Finalize();
}