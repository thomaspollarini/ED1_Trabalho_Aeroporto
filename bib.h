/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bib.h
 * Author: alunos
 *
 * Created on 10 de Maio de 2022, 09:19
 */

#ifndef BIB_H
#define BIB_H

#ifdef __cplusplus
extern "C" {
#endif
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    #define tA 4
    #define tD 3    
    #define nPista 3 
    typedef struct{
        
        int ID,comb,tempo;
    
    }tipoitem;
    
    typedef struct tipocelula *tipoapontador;
    
    typedef struct tipocelula{
        
        tipoitem aviao;
        tipoapontador prox; 
        
    }tipocelula;
    
    typedef struct{
       
        int tam,tipo;
       tipoapontador prim,ult; 
        
    }tipofila;
    
    
    //função para entrada de novos aviões
    void entrada(tipofila *fa, tipofila *fd,int *idA, int *idD);
    
    //inicializa fila
    void cria(tipofila *fila);
    
    //armazena novo avião na fila
    void enfileira(tipofila *fila, int *id);
    
    //retira avião da fila
    void desenfileira(tipoapontador aux, tipofila *fila);
    
    //faz controles de dados - combustivel/tempo de espera/queda de aviões
    void cont_dados(tipofila *fa, tipofila *fd,int *queda);
    
    //faz controle de aterrissagens e decolagens
    void cont_pista(tipofila *fa, tipofila *fd,int *emer,float *tempoA, float *tempoD,int *contA, int *contD);
    
    //imprime fila decolagem/aterrissagem
    void imprime(tipofila fila);
    
    //encontra lista mais apropriada para retirar aviões que decolam ou aterrissam, retorna posição da fila no vetor de filas
    int maior_fila(tipofila *fila);
    
    //encontra fila mais apropriada para inserir novos aviões, retorna posição da fila no vetor de filas
    int menor_fila(tipofila *fila);
    
    //verifica quantidade total de aviões para aterrissar ou decolar, retorna valor total
    int tamanho(tipofila *fila);
    
    



#ifdef __cplusplus
}
#endif

#endif /* BIB_H */