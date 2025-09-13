//
// Created by bruno on 18/08/25.
//
#include <stdio.h>
#include <time.h>
#include "matriz.h"
int main() {
    unsigned int N=720;
    float A[N][N];
    float B[N][N];
    for(unsigned int i=0;i<N;i++) {
        for(unsigned int j=0;j<N;j++) {
            A[i][j]=i;
            B[i][j]=j-5;
        }
    }
    long int ini=clock();
    for(unsigned int i=0;i<5;i++) {
        multiplica_coluna(N,A,B);
    }
    long int fin=clock()-ini;
    printf("tempo decorrido ijk foi: %ld\n",fin/5);
    ini=clock();
    for(unsigned int i=0;i<5;i++) {
        multiplica_linha(N,A,B);
    }
    fin=clock()-ini;
    printf("tempo decorrido ikj foi: %ld",fin/5);
}