#include "keisoku.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 2000
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))
#define MM(OP,A,B,C,N)\
 do{\
   FILE *fp;\
   fp = fopen("result.txt","a");\
   if(N==100)fprintf(fp,"Mult" #OP"\n");	\
   fprintf(fp,"%5d\t",N);	    \
   fclose(fp);\
   ClearM(C,size);\
   StartClock();\
   Mult ##OP(A,B,C,N);				\
   StopClock();\
   PrintClockSpan(pow(N,3));			\
  }while(0)

 int CompM(int X[][SIZE],int Y[][SIZE])
 {
   for (int i = 0;i<SIZE;i++)
     for(int j=0;j<SIZE;j++)
       if(X[i][j] != Y[i][j])return 0;
   return 1;
 }


void Multkij(int A[][SIZE],int B[][SIZE],int C[][SIZE],int N)
{
  for(int k=0;k<N;k++){
    for(int i=0;i<N;i++){
      int da=A[i][k];
      for(int j=0;j<N;j++)
	C[i][j] += da * B[k][j];
    }
  }
}
void Multkji(int A[][SIZE],int B[][SIZE],int C[][SIZE],int N)
{
  for(int k=0;k<N;k++){
    for(int j=0;j<N;j++){
      int db=B[k][j];
      for(int i=0;i<N;i++)
	C[i][j] += A[i][k] * db;
    }
  }
}
void Multjki(int A[][SIZE],int B[][SIZE],int C[][SIZE],int N)
{
  for(int j=0;j<N;j++){
    for(int k=0;k<N;k++){
      int db=B[k][j];
      for(int i=0;i<N;i++)
	C[i][j] += A[i][k] * db;
    }
  }
}
void Multjik(int A[][SIZE],int B[][SIZE],int C[][SIZE],int N)
{
  for(int j=0;j<N;j++){
    for(int i=0;i<N;i++){
      int db=0;
      for(int k=0;k<N;k++)
	db += A[i][k] * B[k][j];
	C[i][j] += db;
    }
  }
}

void Multijk(int A[][SIZE],int B[][SIZE],int C[][SIZE],int N)
{
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      int dc=0;
      for(int k=0;k<N;k++)
	dc = dc + A[i][k] * B[k][j];
      C[i][j] = dc;
    }
  }
}

void Multikj(int A[][SIZE],int B[][SIZE],int C[][SIZE],int N)
{
  for(int i=0;i<N;i++){
    for(int k=0;k<N;k++){
      int db=A[i][k];
      for(int j=0;j<N;j++)
	C[i][j] += B[k][j] * db;
    }
  }
}

void Multbikj(int A[][SIZE],int B[][SIZE],int C[][SIZE], int n, int bsize) {
  int i, j, k, kk, jj;
  double db;
  int en = bsize * (n/bsize); /* Amount that fits evenly into blocks */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      C[i][j] = 0.0;
  for (jj = 0; jj < en; jj += bsize) {
    for (kk = 0; kk < en; kk += bsize) {
      for (i = 0; i < n; i++) {
	for (k = kk; k < kk + bsize; k++) {
	     db = A[i][k];
	  for (j = jj; j < jj + bsize; j++) {
	      C[i][j] += B[k][j] * db;
	  }
	  }
        }
      }
    }
  }


void Multbijk(int A[][SIZE],int B[][SIZE],int C[][SIZE], int n, int bsize) {
  int i, j, k, kk, jj;
  double sum;
  int en = bsize * (n/bsize); /* Amount that fits evenly into blocks */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      C[i][j] = 0.0;
  for (kk = 0; kk < en; kk += bsize) {
    for (jj = 0; jj < en; jj += bsize) {
      for (i = 0; i < n; i++) {
	for (j = jj; j < jj + bsize; j++) {
	     sum = C[i][j];
	  for (k = kk; k < kk + bsize; k++) {
	      sum += A[i][k]*B[k][j];
	  }
	    C[i][j] = sum;
	  }
        }
      }
    }
  }


void PrintM(int M[],int size)
{
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++)
      printf("%2d\t",M[i*size+j]);
	printf("\n");
  }
  printf("\n");
}
//PrintM2D etc..

void PrintMPTR(int M[],int size)
{
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++)
      printf("%2d\t",*M++);
  printf("\n");
  }
  printf("\n");
}

void InitM(int M[],int size)
{
  for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
      M[i*size+j] = rand() % 100;
}
void ClearM(int M[],int size)
{
  for(int i=0;i<size;i++)
    for(int j=0;j<size;j++)
      M[i*size+j] = 0;
}
	  

int main(void){
  static int A[SIZE][SIZE],B[SIZE][SIZE],C[SIZE][SIZE],D[SIZE][SIZE];
  int size = COUNTOF(C);
  srand(0);

  InitM(A,size);
  InitM(B,size);
  /*
  MM(kij,A,B,C,SIZE);
  MM(ijk,A,B,D,SIZE);
  if(!CompM(C,D))printf("Error\n");
  MM(jki,A,B,D,SIZE);
  if(!CompM(C,D))printf("Error\n");
  */
  
  for(int n=100;n<=size;n+=100)
    MM(jki,A,B,D,n);
  for(int n=100;n<=size;n+=100)
    MM(kji,A,B,D,n);
  for(int n=100;n<=size;n+=100)
    MM(ijk,A,B,D,n);
  for(int n=100;n<=size;n+=100)
    MM(jik,A,B,D,n);
  for(int n=100;n<=size;n+=100)
    MM(kij,A,B,D,n);
  for(int n=100;n<=size;n+=100)
    MM(ikj,A,B,D,n);
  
  //for(int n=100;n<=size;n+=100)
  //MM(bijk,A,B,D,n);
    //for(int n=100;n<=size;n+=100)
    //MM(bikj,A,B,D,n);
  return 0;
}
