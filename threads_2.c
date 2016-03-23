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
 * considerando o número de núcleos VIRTUAIS
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double integral = 0.0;

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

void *funcao1(int n){
    double area1 = CalculaArea(0.0, 0.125, 25000000);
    integral += area1; //pode haver condição de corrida
    return NULL;
}

void *funcao2(int n){
    double area2 = CalculaArea(0.125, 0.25, 25000000);
    integral += area2; //pode haver condição de corrida
    return NULL;
}

void *funcao3(int n){
    double area2 = CalculaArea(0.25, 0.375, 25000000);
    integral += area2; //pode haver condição de corrida
    return NULL;
}

void *funcao4(int n){
    double area2 = CalculaArea(0.375, 0.5, 25000000);
    integral += area2; //pode haver condição de corrida
    return NULL;
}

void *funcao5(int n){
    double area2 = CalculaArea(0.5, 0.625, 25000000);
    integral += area2; //pode haver condição de corrida
    return NULL;
}

void *funcao6(int n){
    double area2 = CalculaArea(0.625, 0.75, 25000000);
    integral += area2; //pode haver condição de corrida
    return NULL;
}

void *funcao7(int n){
    double area2 = CalculaArea(0.75, 0.875, 25000000);
    integral += area2; //pode haver condição de corrida
    return NULL;
}

void *funcao8(int n){
    double area2 = CalculaArea(0.875, 1.0, 25000000);
    integral += area2; //pode haver condição de corrida
    return NULL;
}


//criando threads
void CriaThread(){
    //criando uma thread para cada nucleo virtual
    pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
    //dando a cada uma um objetivo
    pthread_create($t1, NULL, funcao1, NULL);
    pthread_create($t2, NULL, funcao2, NULL);
    pthread_create($t3, NULL, funcao3, NULL);
    pthread_create($t4, NULL, funcao4, NULL);
    pthread_create($t5, NULL, funcao5, NULL);
    pthread_create($t6, NULL, funcao6, NULL);
    pthread_create($t7, NULL, funcao7, NULL);
    pthread_create($t8, NULL, funcao8, NULL);
    //mandando bala
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    pthread_join(t8, NULL);
}

/*
 * 
 */
int main(int argc, char** argv) {
    double a, b;
    int n;
    CriaThread();
    printf("A area da curva é \n%.12lf\n", integral);
    return (EXIT_SUCCESS);
}

