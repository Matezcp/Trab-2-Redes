#include "physical.h"
#include "application.h"

#define MAX_LENGHT 2049

void MeioDeComunicacao(int fluxoBrutoDeBits[]) {
    //OBS: trabalhar com BITS e nao com BYTES!!!
    int erro, porcentagemDeErros;
    int fluxoBrutoDeBitsPontoA[MAX_LENGHT], fluxoBrutoDeBitsPontoB[MAX_LENGHT];

    memset(fluxoBrutoDeBitsPontoB,0,sizeof fluxoBrutoDeBitsPontoB);

    porcentagemDeErros = 0; //10%, 20%, 30%, 40%, ..., 100%
    for(int i=0;i<MAX_LENGHT;i++){
        fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBits[i];
    }

    for(int i=0;i<MAX_LENGHT;i++){
        if ((rand() % 100) <= porcentagemDeErros) //fazer a probabilidade do erro
            fluxoBrutoDeBitsPontoB[i] += fluxoBrutoDeBitsPontoA[i] ; //BITS!!!
        else
            (fluxoBrutoDeBitsPontoB[i]  == 0) ?
            fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBitsPontoB[i]++:
            fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBitsPontoB[i]--;
    }

    /*while (fluxoBrutoDeBitsPontoB.length != fluxoBrutoDeBitsPontoA) {
        if ((rand() % 100) <= porcentagemDeErros) //fazer a probabilidade do erro
            fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA; //BITS!!!
        else
            (fluxoBrutoDeBitsPontoB == 0) ?
            fluxoBrutoDeBitsPontoA = fluxoBrutoDeBitsPontoB++ :
            fluxoBrutoDeBitsPontoA = fluxoBrutoDeBitsPontoB--;
    }*/

    //Atualiza o fluxo
    for(int i=0;i<MAX_LENGHT;i++){
         fluxoBrutoDeBits[i] = fluxoBrutoDeBitsPontoA[i];
    }

    CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}