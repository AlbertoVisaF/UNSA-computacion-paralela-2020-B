#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <chrono>

using namespace std;
#define C_MAX  500
#define N_BLOQUE_MAX  2
#define A_COLS C_MAX
#define A_ROWS C_MAX
#define B_COLS C_MAX
#define B_ROWS A_COLS
#define C_COLS B_COLS
#define C_ROWS A_ROWS


#ifndef BLOCK_I
    #define BLOCK_I N_BLOQUE_MAX
#endif
#ifndef BLOCK_J
    #define BLOCK_J N_BLOQUE_MAX
#endif
#ifndef BLOCK_K
    #define BLOCK_K N_BLOQUE_MAX
#endif


//#define TEST_REP 5



void mult(int max){
    typedef long long ll;
    ll matrix1[max][max];
    ll matrix2[max][max];
    ll matrix_result[max][max];

    for (int i = 0; i < max; ++i){
        for (int j = 0; j < max; ++j){
            matrix1[i][j]=rand()%9;
            matrix2[i][j]=rand()%9;
        }
    }
    auto _start = chrono::system_clock::now();

    //multiplicacion
    for(int i=0;i<max; ++i){
        for(int j=0;j<max;++j){
            matrix_result[i][j]=0;
            for(int k=0;k<max;++k){
                matrix_result[i][j]+=matrix1[i][k]*matrix2[k][j];
            }
        }
    }
    auto _end = chrono::system_clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(_end - _start);
    cout<<"Tiempo de ejecucion: "<<elapsed.count()<<endl;
}

void mult_bloques(){
    double A[A_ROWS][A_COLS], B[B_ROWS][B_COLS], C[C_ROWS][C_COLS];
    int i, j, k, i_bl, j_bl, k_bl;
    for(i=0; i<A_ROWS; i++)
        for(j=0; j<A_COLS; j++)
            A[i][j] = exp(-fabs(i-j));
    
    for(i=0; i<B_ROWS; i++)
        for(j=0; j<B_COLS; j++)
            B[i][j] = exp(-fabs(i-j));
    
    
    for(i=0; i<C_ROWS; i++)
        for(j=0; j<C_COLS; j++)
            C[i][j] = 0;
    
    

    auto _start = chrono::system_clock::now();
    for(i=0; i<C_ROWS; i+= BLOCK_I)
        for(j=0; j<C_COLS; j+= BLOCK_J)
            for(k=0; k<A_COLS; k+= BLOCK_K)
                for(i_bl=i; i_bl<(i+BLOCK_I) && i_bl<C_ROWS; i_bl++)
                    for(j_bl=j; j_bl<(j+BLOCK_J) && j_bl<C_COLS; j_bl++)
                        for(k_bl=k; k_bl<(k+BLOCK_K) && k_bl<A_COLS; k_bl++)
                            C[i_bl][j_bl] += A[i_bl][k_bl] * B[k_bl][j_bl];

    auto _end = chrono::system_clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(_end - _start);
    cout<<"Tiempo de ejecucion: "<<elapsed.count()<<endl;

}




int main(void){
    //mult(100);    
    mult_bloques();
    return 0;
}