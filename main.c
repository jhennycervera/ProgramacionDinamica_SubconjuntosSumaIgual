/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: jhenn
 * Dado un arreglo de números enteros, partir el conjunto de números en
    dos subconjuntos tal que la suma de elementos en ambos subconjunto es
    la misma.
 *  * Created on 15 de diciembre de 2020, 01:21 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * ESTRATEGIAS:
 * -Si la suma de todo el arr es impar entonces no hay dos subconjuntos con la misma suma
 * -si la suma de todo el arr es par se debe verificar si algun subconjunto tiene la suma/2, ya que el otro conjunto tmb lo tendrá
 *          -Si lo tiene -> hay dos subconjuntos con la misma suma
 *          -Si no lo tiene -> no hay dos subconjuntos con la misma suma
 * Para verificar si hay algun subconjunto que tenga suma/2 se hará con progmacion dinamica 
 */

int suma_arreglo(int arr[], int n){
    int suma=0;
    for(int i=0; i<n; i++){
        suma+=arr[i];
    }
    return suma;
}

int ordenar_arreglo(int arr[], int n){
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i]>arr[j]){
                int aux= arr[i];
                arr[i]=arr[j];
                arr[j]=aux;
            }
        }
    }
}

int buscaSuma_subconjuntos(int arr[], int n, int suma){
    
    //ordenando arr de forma ascendente
    ordenar_arreglo(arr, n);
    
    int matriz_suma[n+1][suma+1];
    //llenar de 0s la fila 0 (representa que con el subconjunto vacio no se puede dar como resultado la suma de  1,2,3...suma)
    for(int i=0; i< suma+1; i++){
        matriz_suma[0][i]= 0;
    }
    //llenar de 1s la columna 0(representa que si es posible encontrar un subconjunto que sume 0, ya que se considera el cjt vacio)
    for(int i=0 ; i<n+1; i++){
        matriz_suma[i][0]= 1;
    }
    //llenando el resto de la matriz
    for(int i=1; i<=n ; i++){
        for(int j=1; j<=suma; j++){
            if(matriz_suma[i-1][j]==1){
                matriz_suma[i][j]= 1;
            }
            else{
                matriz_suma[i][j]= 0;
                if( j- arr[i-1] >=0){
                    matriz_suma[i][j]=matriz_suma[i-1][j- arr[i-1]];
                }
            }
            printf("%d ", matriz_suma[i][j]);
        }
        printf("\n");
    }
    
    //la ultima columna me dice si hay un subconjunto con ese suma
    for(int i=1; i<=n; i++){
        if(matriz_suma[i][suma]==1){
            return 1;
        }
    }
    return 0;
}


int Hay_DosSubconjuntos_ConLaMismaSuma(int arr[], int n){
    
    int suma_total =suma_arreglo(arr, n);
    if(suma_total%2!=0) return 0; //suma impar
    //la suma es par
    
    if(buscaSuma_subconjuntos(arr, n, suma_total/2)) return 1;
    else return 0;
}

int main(int argc, char** argv) {
    int n=7;
    int arr[7]= {1,2,2,5,3,1,2};
    
    if(Hay_DosSubconjuntos_ConLaMismaSuma(arr, n)){
        printf("Verdadero\n");
    }
    else printf("Falso\n");
    
    return (EXIT_SUCCESS);
}

