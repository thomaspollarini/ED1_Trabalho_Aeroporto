/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bib.c
 * Author: alunos
 *
 * Created on 10 de Maio de 2022, 09:19
 */

#include "bib.h"



void cria(tipofila *fila){
        
    fila->prim=(tipoapontador)malloc(sizeof(tipocelula));
    fila->ult=fila->prim;
    fila->ult->prox=NULL;   //inicializa a fila, primeiro = célula cabeça
    fila->tam=0;            //tamanho = 0        
    return;
}

void entrada(tipofila *fa, tipofila *fd,int *idA, int *idD){
    
    int i,j,nA,nD,pos;
    
    nA=rand()%4;  //recebe número de aviões que vão aterrizar, de 0 a 3
    nD=rand()%4;  //recebe número de aviões que vão decolar, de 0 a 3
        
    for(i=0;i<nA;i++){       //laço com número de aviões que serão adicionados
        pos=menor_fila(fa);  //seleciona em qual fila o avião será colocado
        enfileira(&fa[pos],idA); //aloca novo avião na fila encontrada
    }
    
    for(i=0;i<nD;i++){          //laço com número de aviões que serão adicionados
        pos=menor_fila(fd);     //seleciona em qual fila o avião será colocado
        enfileira(&fd[pos],idD);//aloca novo avião na fila encontrada
    }
    
    return;
}

void enfileira(tipofila *fila, int *id){
    
    fila->ult->prox= (tipoapontador) malloc(sizeof(tipocelula));
    fila->ult=fila->ult->prox;      //cria nova celula
    
    if(fila->tipo==1){ //identifica tipo de fila (1-aterrissagem/2-decolagem)
        fila->ult->aviao.comb=rand()%20+1; //gera combustivel aleatório
        fila->ult->aviao.ID=*id;           //adiciona identificação ímpar     //armazena dados 
        fila->ult->aviao.tempo=0;          //inicializa tempo de espera
        
        *id+=2;//aumenta id para próximo avião
        fila->tam++;//aumenta contador de tamanho da fila
    }else{//dados decolagem
        fila->ult->aviao.comb=20; //combustivel fixo 20
        fila->ult->aviao.ID=*id;  //adiciona identificação par
        fila->ult->aviao.tempo=0; //inicializa tempo de espera
        
        *id+=2;//aumenta id para próximo avião
        fila->tam++;//aumenta contador de tamanho da fila
    }
    
    fila->ult->prox=NULL;
    
    
}

void desenfileira(tipoapontador aux, tipofila *fila){
    
    tipoapontador q;
    
    q=aux->prox; //retira célula da lista
    aux->prox=q->prox;
    
    if(aux->prox==NULL){
        fila->ult=aux;
    }
    
    free(q); //libera celula retirada
}

void cont_dados(tipofila *fa, tipofila *fd,int *queda){
    
    int i,j;
    tipoapontador aux;
    
    for(i=0;i<tA;i++){  //aviões para  aterrissar
        aux=fa[i].prim;
        
        while(aux->prox!=NULL){
            aux->prox->aviao.tempo++; //aumenta tempo de espera de cada avião
            aux->prox->aviao.comb--;  //diminui combustivel de aviões voando
            
            if(aux->prox->aviao.comb<=0){
                desenfileira(aux,&fa[i]);  //retira aviões sem combustivel da lista - queda
                *queda=*queda+1;          //aumenta contador de quedas
                fa[i].tam--;              //diminui contador de tamanho da lista
            }else{
                aux=aux->prox;
            }
        }
    }
    
    for(i=0;i<tD;i++){ //aviões para decolar
        aux=fd[i].prim->prox;
        
        while(aux!=NULL){
            aux->aviao.tempo++; //aumenta tempo de espera
            aux=aux->prox;
        }
    }
}    

void cont_pista(tipofila *fa, tipofila *fd,int *emer,float *tempoA, float *tempoD,int *contA, int *contD){
    
    int i,j,tam1,tam2,pos,cont=0;
    tipoapontador aux;
    
    for(i=0;i<tA;i++){              //controle de pouso de emergência
        if(fa[i].prim->prox!=NULL){
            if(fa[i].prim->prox->aviao.comb==1){    //verifica se aviões estão sem reserva
                cont++; //contador de ações (pouso/decolagem)
                if(cont<nPista){//pousa no máximo 3 aviões em emergência
                
                    *tempoA=*tempoA+fa[i].prim->prox->aviao.tempo;  //adiciona o tempo de espera desse avião ao tempo total
                    *contA=*contA+1;                                //adiciona esse avião ao número de aviões que aterrissaram
                        
                    desenfileira(fa[i].prim,&fa[i]);  //remove aviões pousados da lista
                    
                    fa[i].tam--; //diminui contador de tamanho
                    *emer=*emer+1;  //aumenta contador de pousos de emergência
                }
            }
        }
    }
    
    for(i=cont;i<nPista;i++){
        if(i==0){ //verifica se pista 3 não foi utilizada para pouso de emergência
            tam2=tamanho(fd);  //verifica se há aviões para decolar
            if(tam2>0){
                pos=maior_fila(fd); //seleciona fila de decolagem apropriada
            
                *tempoD=*tempoD+fd[pos].prim->prox->aviao.tempo; //adiciona o tempo de espera desse avião ao tempo total
                *contD=*contD+1;                                 //adiciona esse avião ao número de aviões que decolaram
            
                desenfileira(fd[pos].prim,&fd[pos]); //retira avião que decolou da fila
           
                fd[pos].tam--;//diminui contador de tamanho
            }    
        }else{
            tam1=tamanho(fa); //armazena número total de aviões que devem aterrissar
            tam2=tamanho(fd); //armazena número total de aviões que devem decolar
            
                            //verifica tam>0 para evitar problemas
            if(tam1>tam2 && tam1>0){ //seleciona se pista será usada para decolagem ou aterrissagem (definido por quem tem mais aviões)
                pos=maior_fila(fa); //seleciona fila de aterrissagem apropriada
                
                *tempoA=*tempoA+fa[pos].prim->prox->aviao.tempo;  //adiciona o tempo de espera desse avião ao tempo total
                *contA=*contA+1;                                //adiciona esse avião ao número de aviões que aterrissaram
                
                desenfileira(fa[pos].prim,&fa[pos]); //retira avião que aterrissou da fila
                
                fa[pos].tam--;//diminui contador de tamanho
            }else{
                if(tam2>0){
                    pos=maior_fila(fd);//seleciona fila de decolagem apropriada
                    
                    *tempoD=*tempoD+fd[pos].prim->prox->aviao.tempo; //adiciona o tempo de espera desse avião ao tempo total
                    *contD=*contD+1;                                 //adiciona esse avião ao número de aviões que decolaram
                    
                    desenfileira(fd[pos].prim,&fd[pos]);//retira avião que decolou da fila
                    
                    fd[pos].tam--; //diminui contador de tamanho
                }    
            }
        }
    }
}


void imprime(tipofila fila){
    
    int pos=1;
    tipoapontador aux;
    
    aux=fila.prim->prox;        //auxiliar passa pela fila e imprime seus dados
    
    while(aux!=NULL){
        
        printf("\nPosição: %d\nIdentificação: %d\nNível de combustivel: %d\nTempo de espera: %d\n"
                ,pos,aux->aviao.ID,aux->aviao.comb,aux->aviao.tempo);
        
        aux=aux->prox;
        pos++;
    }
    
    if(pos==1){// se contador de pos não mudar fila está vazia
        printf("Fila está vazia.\n");
    }
}

int maior_fila(tipofila *fila){
    
    int i,n,tam,pos=0;
    
    if(fila[0].tipo==1){ //verifica tipo de fila (aterrissagem/decolagem)
        n=tA;
    }else{
        n=tD;
    }
    
    tam=0;
    for(i=0;i<n;i++){                                                                   //fator importante para menos quedas de aviões
        if(fila[i].prim->prox!=NULL){     //seleciona fila com maior número de aviões - menor combustivel critério de desempate
            if(fila[i].tam>tam || (fila[i].tam==tam && fila[i].prim->prox->aviao.comb<fila[pos].prim->prox->aviao.comb)){
                tam=fila[i].tam;
                pos=i;
            }
        }
    }
    
    return pos; //retorna posição da fila no vetor
    
}

int menor_fila(tipofila *fila){
    
    int i,n,tam,pos;
    
    if(fila[0].tipo==1){ //verifica tipo de fila (aterrissagem/decolagem)
        n=tA;
    }else{
        n=tD;
    }
    
    for(i=0;i<n;i++){
        if(i==0){
            tam=fila[i].tam;
            pos=i;
        }else{                                                                      //fator importante para maior vazão de filas
            if(tam>0){                  //seleciona fila com menor número de aviões - maior tempo de espera critério de desempate
                if(fila[i].tam<tam || (fila[i].tam==tam && fila[i].prim->prox->aviao.tempo>fila[pos].prim->prox->aviao.tempo)){
                    tam=fila[i].tam;
                    pos=i;
                }
            } 
        }
    }
    
    return pos; //retorna posição da fila no vetor
}



int tamanho(tipofila *fila){
    
    int i,n,tam=0;
    
    if(fila[0].tipo==1){  //verifica tipo de fila (aterrissagem/decolagem)
        n=tA;
    }else{
        n=tD;
    }
    
    for(i=0;i<n;i++){
        tam+=fila[i].tam;  //somatório do tamanho das filas
    }
    
    return tam; //retorna tamanho total
}