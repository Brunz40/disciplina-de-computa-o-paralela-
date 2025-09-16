//
// Created by bruno on 12/09/25.
//

#include "operação vetorial.h"
float* somar(float* v1, float* v2, unsigned int length){
    float soma[length];
    for(unsigned int i = 0; i < length; i++) {
        soma[i] = v1[i] + v2[i];
    }
    return soma;
}
float* produto(float* v1, float* v2, unsigned int length) {
    float produto[length];
    for(unsigned int i = 0; i < length; i++) {
        produto[i] = v1[i] * v2[i];
    }
    return produto;
}