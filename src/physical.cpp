#include "physical.h"
#include "link.h"
#include "application.h"
#include <iostream>

using namespace std;

void MeioDeComunicacao(int fluxoBrutoDeBits[]) {
    //OBS: trabalhar com BITS e nao com BYTES!!!
    int erro, porcentagemDeErros;
    int fluxoBrutoDeBitsPontoA[MAX_FRAME_LEN], fluxoBrutoDeBitsPontoB[MAX_FRAME_LEN];
    memset(fluxoBrutoDeBitsPontoB,0,sizeof fluxoBrutoDeBitsPontoB);

    porcentagemDeErros = 0; //10%, 20%, 30%, 40%, ..., 100%
    for(int i=0;i<MAX_FRAME_LEN;i++){
        fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBits[i];
    }

    for(int i=0;i<MAX_FRAME_LEN;i++){
        if (((rand() % 100)+1) >= porcentagemDeErros) //fazer a probabilidade do erro
            fluxoBrutoDeBitsPontoB[i] += fluxoBrutoDeBitsPontoA[i]; //BITS!!!
        else
            (fluxoBrutoDeBitsPontoB[i]  == 0) ?
            fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBitsPontoB[i]++:
            fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBitsPontoB[i]--;
    }

    //Atualiza o fluxo
    for(int i=0;i<MAX_FRAME_LEN;i++){
         fluxoBrutoDeBits[i] = fluxoBrutoDeBitsPontoA[i];
    }

    CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}