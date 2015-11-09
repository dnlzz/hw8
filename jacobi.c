/* 
   CS288 HOMEWORK 8
   Your program will take in two command-line parameters: n and error
   command: jacobi 5 0.0001
   command: jacobi 10 0.000001
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 100
#define MAX_ITER 10000

int jacobi();
void init();
int convergence();
void srand();
void print_vector();
void print_equation();

float a[N][N], b[N];
float x[N], buf[N], tmp[N];
int n;
float error;

int main(int argc, char **argv){
  int n_iter;			/* number of iterations */
  n = atoi(argv[1]);
  error = atof(argv[2]);

  init();		   /* initalize a, x0 and b - DO not change */

  a[0][0] = 5;
  a[0][1] = -2;
  a[0][2] = 3;
    a[1][0] = -3;
  a[1][1] = 9;
  a[1][2] = 1;
    a[2][0] = 2;
  a[2][1] = -1;
  a[2][2] = -7;

  b[0] = -1;
  b[1] = 2;
  b[2] = 3;

  x[0] = 0;
  x[1] = 0;
  x[2] = 0;

  print_equation();

  n_iter = jacobi();

  printf("Num iter: %d\n", n_iter);

  return 0;
}

int jacobi(){
  int i,j,k=0;
  float sum=0;
  // ...
  // ...
  // ...
  //for (k=0; k < 15; k++) {
  while (!(convergence())) {  //while   ax-b != 0
    for (i=0;i<n;i++) {
      for (j=0;j<n;j++) {
        if (i != j)
          sum += a[i][j] * x[j];
      }
      buf[i] = (b[i] - sum) / (a[i][i]);   //give us our x values
      //printf("Sum:  %f  b[%d]:  %f a[%d][%d]:  %f  buf[%d]:  %f\n", sum, i, b[i], i, i, a[i][i], i, buf[i]);
      sum=0;
    }

    for (i=0; i<n; i++) {
      
      x[i] = buf[i];
      printf("x[%d]: %f\n", i, x[i]);
    }

    k++;
    
  }
  
  return k;
}

// returns 1 if converged else 0
int convergence(){
  int i,j,k=0,flag=1;
  float sum=0;
  // ...
  // ...
  // ...

  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
	    sum+=(a[i][j] * x[k]);
	    k++;
    }

    //printf("Sum: %f\n", sum);
    tmp[i]=sum;
    //printf("Tmp[%d]:  %f\n", i, sum);
    sum=0;
    k=0;
  }
  
  for (k=0; k<n; k++) {
    printf("tmp[%d]: %f   b[%d]: %f\n", k, tmp[k], k, b[k]);
    if ( fabs(tmp[k] - b[k]) > error ) {
      printf("Error: %f\n", fabs(tmp[k]-b[k]));
      return 0;
    }
  }

  printf("\n");
  //if ( (tmp[k] - error) > b[k] )
  //return 0;
 
  return flag;
}

// Try not to change this. Use it as is.
void init(char **argv){
  int i,j,k,flag=0;
  float sum;
  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  seed = 31;
  srand(seed);
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++) {
      a[i][j] = rand() & 0x7;
      if (rand() & 0x1) a[i][j] = -a[i][j];
    }
    sum = 0;
    for (j=0;j<n;j++) if(i!=j) sum = sum + abs(a[i][j]);
    if (a[i][i] < sum) a[i][i] = sum + a[i][i];
  }

  for (i=0;i<n;i++) x[i]=1;

  srand(seed);
  for (i=0;i<n;i++){
    b[i]=rand() & 0x7;
    if (rand() & 0x1) b[i] = -b[i];
  }

  print_equation();

}

void print_equation(){
  int i,j;

  printf("A*x=b\n");
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++) printf("%2d ",(int)(a[i][j]));
    printf(" * x%d = %d\n",i,(int)(b[i]));
  }
  printf("\n");
}

void print_vector(float *l){
  int i;
  for (i=0; i<n; i++) printf("%.6f ",l[i]);
  printf("\n");
}

// end of file
