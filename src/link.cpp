#include "link.h"
#include "physical.h"

void CamadaEnlaceDadosTransmissora(int quadro[]) {
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);

    //chama a proxima camada
    //MeioDeComunicacao(quadro);
}

int numOfOnes(int quadro[]){
    int count = 0;

    for(int i =0;quadro[i] != -1 && i < 256 ; ++i){
        if(quadro[i] == 1)
            count++;
    }

    return count;
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]) {
    //implementacao do algoritmo
    if(numOfOnes(quadro) % 2 == 0){ //Número par de 1's
        quadro[8*256] = 0;
    }
    else{                           //Número impar de 1's
        quadro[8*256] = 1;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]) {
    //implementacao do algoritmo
    if(numOfOnes(quadro) % 2 == 0){ //Número par de 1's
        quadro[8*256] = 1;
    }
    else{                           //Número impar de 1's
        quadro[8*256] = 0;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]) {
    //implementacao do algoritmo
    //usar polinomio CRC-32(IEEE 802)
}

void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]) {
    int tipoDeControleDeErro = 0; //alterar de acordo com o teste
    switch (tipoDeControleDeErro) {
        case 0: //bit de paridade par
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break;
        case 1: //bit de paridade impar
            CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
            break;
        case 2: //CRC
            //codigo
            CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            //codigo
            break;
    }
}