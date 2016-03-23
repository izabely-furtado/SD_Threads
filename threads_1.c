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
 * SEM considerar o número de núcleos
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
    double area1 = CalculaArea(0.0, 0.5, 25000000);
    integral += area1; //pode haver condição de corrida
    return NULL;
}

void *funcao2(int n){
    double area2 = CalculaArea(0.5, 1.0, 25000000);
    integral += area2; //pode haver condição de corrida
    return NULL;
}



//criando threads
void CriaThread(){
    pthread_t t1, t2;
    pthread_create($t1, NULL, funcao1, NULL);
    pthread_create($t2, NULL, funcao2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
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

