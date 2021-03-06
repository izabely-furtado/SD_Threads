/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threads.c
 * Author: IzabelyFurtado
 *
 * Created on 22 de Março de 2016, 20:49
 * 
 * Calcula a integral de f(x) em paralelo 
 * considerando o número de núcleos REAIS
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <math.h>


double integral = 0.0;
pthread_mutex_t lock;

//função que calcula a area de um trapézio
double AreaTrapezio(double dx, double h1, double h2){
    double area;
    area = dx * (h1+h2)/2;
    return area;
}

//função qualquer f(x)
double f(double x){
    return (4/1+x*x);
}

//criando limite
typedef struct limite
{
    double inferior;
    double superior;
    long n;
}Limite;

Limite *criaLim(double inferior, double superior, long n){
    Limite *l = (Limite *) malloc(sizeof(Limite));
    l->inferior = inferior;
    l->superior = superior;
    l->n = n;
    return l;
}

//calcula a area da integral da função f(x)
double CalculaArea(double a, double b, int N){
    int i;
    double area = 0.0, dx, x1, x2, f1, f2;
    for(i = 0; i<N; i++){
        x1 = a + dx * i;
        x2 = a + dx * (i + 1);
        f1 = f(x1);
        f2 = f(x2);
        area += AreaTrapezio(dx, f1, f2);
    }
    return area;
}

//ponteiro pra função ... 
//dividindo f(x) para ser calculada por partes... (estilo Jack)
void *funcaoX(Limite *lim){
    double area2 = CalculaArea(lim->inferior, lim->superior, lim->n);
    
    //controlando area que pode haver condição de corrida
    pthread_mutex_lock(&lock);
    integral += area2; 
    pthread_mutex_unlock(&lock);

    return NULL;
}

//criando threads
void CriaThread(){
    int nProc = get_nprocs();
    //criando vetor de threads
    pthread_t threads[nProc] = (pthread_t *) malloc(nProc*sizeof(pthread_t));
    
    int i, k;
    //dando a cada thread um objetivo
    for(i=0; i<nProc; i++) {
        Limite* l = criaLim((1/nProc)*i - (1/nProc), (1/nProc)*i)
        pthread_create(&(threads[i]), NULL, funcaoX, &l);
    }
    //mandando bala
    for(k=0; k<nProc; k++) {
        pthread_join(threads[k], NULL);
    }
    
}

/*
 * 
 */
int main(int argc, char** argv) {
    double a, b;
    int n;
    
    25000000
    
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    CriaThread();
    printf("A area da curva é \n%.12lf\n", integral);
    pthread_mutex_destroy(&lock);
    return (EXIT_SUCCESS);
}

