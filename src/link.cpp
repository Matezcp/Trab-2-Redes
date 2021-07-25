#include "link.h"

void CamadaEnlaceDadosTransmissora(int quadro[]) {
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);

    //chama a proxima camada


}

void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]) {
    int tipoDeControleDeErro = 0; //alterar de acordo com o teste
    
    switch (tipoDeControleDeErro) {
        case 0: //bit de paridade par
            //codigo
            break;
        case 1: //bit de paridade impar
            //codigo
            break;
        case 2: //CRC
            //codigo

            //codigo
            break;
    }
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]) {
    //implementacao do algoritmo
}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(int quadro[]) {
    //implementacao do algoritmo
}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]) {
    //implementacao do algoritmo
    //usar polinomio CRC-32(IEEE 802)
}