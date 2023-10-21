/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: thomas
 *
 * Created on 19 de maio de 2022, 17:39
 */

#include "bib.h"

/*
 * 
 */

int main(int argc, char** argv) {
    
    srand(time(NULL));
    
    int i,x=0,UT=0,idA=1,idD=0,queda=0,emer=0,contA=0,contD=0;
    float mediaA,mediaD,tempoA=0,tempoD=0;
    tipofila fa[4],fd[3];
    
    for(i=0;i<tA;i++){ //inicia as filas de aterrissagem
        cria(&fa[i]);
        fa[i].tipo=1;   //tipo 1 sinaliza que é uma fila de aterrizagem
    }
    for(i=0;i<tD;i++){ //inicia as filas de decolagem
        cria(&fd[i]);
        fd[i].tipo=2;   // tipo 2 sinaliza que é uma fila de decolagem
    }
    
    while(x>-1){
        
        if(x==0){   //digite a quantidade de ciclos que vc qr q o programa rode
            printf("Digite o número de ciclos que serão rodados ou digite 0 para sair:  "); //pode ser digitado o número de ciclos
            scanf("%d",&x);                                                  //que passarão antes de printar informações
            system("clear");                                                 // 1 ciclo = 1 Unidade de tempo
        }
        
        if(x<=0){
            return 0;
        }
        
        entrada(fa,fd,&idA,&idD); //inicia entrada de dados
        
        cont_pista(fa,fd,&emer,&tempoA,&tempoD,&contA,&contD); //faz controle de decolagem e aterrissagem
        
        if(tempoA==0 || contA==0){
            mediaA=0;
        }else{
            mediaA=tempoA/contA;  //calcula média do tempo de aterrissagem - tempo total/numero de aterrissagem total
        }
        if(tempoD==0 || contD==0){
            mediaD=0;
        }else{
            mediaD=tempoD/contD;  //calcula média do tempo de decolagem - tempo total/numero de decolagem total
        }
        
        cont_dados(fa,fd,&queda); //faz controle de dados, combustivel/tempo/quedas
        
        UT++; //passa uma unidade de tempo
        
        x--; //diminui o contador de ciclos 
        
        if(x==0){
            
            printf("\n\nCICLO Nº %d:\n",UT);    //printa filas e informações utéis
            
            for(i=0;i<tA;i++){
                printf("\n\nFILA ATERRISSAGEM %d:\n",i+1);
                imprime(fa[i]);
            }
            for(i=0;i<tD;i++){
                printf("\n\nFILA DECOLAGEM %d:\n",i+1);
                imprime(fd[i]);
            }
            
            printf("\nTempo médio para decolagem: %f\nTempo médio para aterrissagem: %f\n"
                    "Número de aterrissagens sem reserva de combustivel: %d \nNúmero de quedas: %d\n",mediaD,mediaA,emer,queda);
            
            printf("Quantidade de aterrissagens: %d\nQuantidade de decolagens: %d\nPercentagem de quedas de aviões: %.2f%%\n\n",contA,contD,((100.0*queda)/(contA+queda)));
        }
        
    }
    
    return (EXIT_SUCCESS);
}