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

void *funcaoX(int n, double limInferior, double limSuperior){
    double area2 = CalculaArea(limInferior, limSuperior, 25000000);
    
    //controlando area que pode haver condição de corrida
    pthread_mutex_lock(&lock);
    integral += area2; 
    pthread_mutex_unlock(&lock);

    return NULL;
}

void *funcao1(int n){
    *funcaoX(1, 0.0, 0.25);
    return NULL;
}

void *funcao2(int n){
    *funcaoX(1, 0.25, 0.50);
    return NULL;
}

void *funcao3(int n){
    *funcaoX(1, 0.50, 0.75);
    return NULL;
}

void *funcao4(int n){
    *funcaoX(1, 0.75, 1.0);
    return NULL;
}

//criando threads
void CriaThread(){
    //criando uma thread para cada nucleo reais
    pthread_t t1, t2, t3, t4;
    //dando a cada uma um objetivo
    pthread_create($t1, NULL, funcao1, NULL);
    pthread_create($t2, NULL, funcao2, NULL);
    pthread_create($t3, NULL, funcao3, NULL);
    pthread_create($t4, NULL, funcao4, NULL);
    //mandando bala
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
}

/*
 * 
 */
int main(int argc, char** argv) {
    double a, b;
    int n;
    
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

