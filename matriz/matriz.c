//
// Created by bruno on 18/08/25.
//

double** multiplica_coluna(unsigned int N,float a[N][N], float b[N][N]){
  double Mult[N][N];
  unsigned int j;
  unsigned int k;
  double soma;
  for (unsigned int i=0;i<N;i++){
    for (j=0;j<N;j++) {
      soma = 0;
      for (k=0;k<N;k++) {
        soma += a[i][k]*b[k][j];
      }
      Mult[i][j] = soma;
    }
  }
  return Mult;
  }

double** multiplica_linha(unsigned int N,float a[N][N], float b[N][N]) {
  float Mult[N][N];
  unsigned int j;
  unsigned int k;
  double soma;
  for (unsigned int i=0;i<N;i++){
    for (k=0;k<N;k++) {
      soma = 0;
      for (j=0;j<N;j++) {
        soma += a[i][k]*b[k][j];
      }
      Mult[i][j] = soma;
    }
  }
  return Mult;
}
