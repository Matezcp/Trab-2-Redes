#include "physical.h"

void MeioDeComunicacao(int fluxoBrutoDeBits[]) {
    //OBS: trabalhar com BITS e nao com BYTES!!!
    int erro, porcentagemDeErros;
    int fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];

    porcentagemDeErros = 0; //10%, 20%, 30%, 40%, ..., 100%
    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    while (fluxoBrutoDeBitsPontoB.length != fluxoBrutoDeBitsPontoA) {
        if ((rand() % 100) == ...) //fazer a probabilidade do erro
            fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA; //BITS!!!
        else
            (fluxoBrutoDeBitsPontoB == 0) ?
            fluxoBrutoDeBitsPontoA = fluxoBrutoDeBitsPontoB++ :
            fluxoBrutoDeBitsPontoA = fluxoBrutoDeBitsPontoB--;
    }
}